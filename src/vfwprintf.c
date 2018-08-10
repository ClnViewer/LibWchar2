/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sub license, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */

/* Original code:
   Copyright (C) 2005-2012 Rich Felker

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sub license, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  Modified in 2013 for the Android Open Source Project.
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include "libwchar.h"

// A wrapper around either a FILE* or a string buffer, used to output
// the result of formatted expansion.

typedef struct
{
    FILE*    file;
    wchar_t* buffer;
    size_t   buffer_pos;
    size_t   buffer_size;
} FOut;

static void out_init_file(FOut* out, FILE* f)
{
    memset(out, 0, sizeof(*out));
    out->file = f;
}

static void out_init_buffer(FOut* out, wchar_t* buffer, size_t buffer_size)
{
    memset(out, 0, sizeof(*out));
    out->buffer      = buffer;
    out->buffer_pos  = 0;
    out->buffer_size = buffer_size;
}

static void out(FOut* _out, const wchar_t* text, size_t length)
{
    if (!length)
    {
        return;
    }
    if (_out->file != NULL)
    {
        wchar_t const *w = text;
        while (length--)
        {
            _fputwc(*w++, _out->file);
        }
    }
    else
    {
        // Write into a bounded buffer.
        size_t avail = _out->buffer_size - _out->buffer_pos;
        if (length > avail)
        {
            length = avail;
        }
        memcpy((char*)(_out->buffer + _out->buffer_pos),
               (const char*)text,
               (length * sizeof(wchar_t))
              );
        _out->buffer_pos += length;
    }
}

static void out_putwc(wchar_t wc, FOut* _out)
{
    if (_out->file)
    {
        _fputwc(wc, _out->file);
    }
    else if (_out->buffer_pos < _out->buffer_size)
    {
        _out->buffer[_out->buffer_pos++] = wc;
    }
}

static int out_printf(FOut* _out, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    if (_out->file)
    {
        int ret = vfprintf(_out->file, format, args);
        va_end(args);
        return ret;
    }
    else
    {
        // TODO(digit): Make this faster.
        // First, generate formatted byte output.
        size_t   mb_len,
                 wide_len;
        char*    mb_buffer;
        wchar_t* wide_buffer;

        if (
            (!(mb_len    = (size_t) _vsnprintf(NULL, 0, format, args))) ||
            ((mb_buffer = malloc((mb_len + 1))) == NULL)
        )
        {
            va_end(args);
            return 0;
        }

        (void) _vsnprintf(mb_buffer, (mb_len + 1), format, args);

        // Then convert to wchar_t buffer.
        wide_len = _mbstowcs(NULL, mb_buffer, mb_len);

        if (
            (wide_len == 0) || (wide_len == (size_t)-1) ||
            ((wide_buffer = malloc((wide_len + 1) * sizeof(wchar_t))) == NULL)
        )
        {
            va_end(args);
            free(mb_buffer);
            return 0;
        }

        (void) _mbstowcs(wide_buffer, mb_buffer, mb_len);

        // Add to buffer.
        out(_out, wide_buffer, wide_len);
        // finished
        free(wide_buffer);
        free(mb_buffer);
        va_end(args);

        return (int) wide_len;
    }
    va_end(args);
}

static int out_error(FOut* _out)
{
    if (_out->file != NULL)
    {
        return ferror(_out->file);
    }
    return 0;
}

static int out_overflow(FOut* _out)
{
    if (_out->file != NULL)
    {
        return feof(_out->file);
    }
    return (_out->buffer_pos >= _out->buffer_size);
}

#include "vfxprint.h"
#include "vfxprint.c"

static int getint(wchar_t **s)
{
    int i;
    for (i=0; iswdigit(**s); (*s)++)
        i = 10*i + (**s-'0');
    return i;
}

static const char sizeprefix['y'-'a'] =
{
    ['a'-'a']='L', ['e'-'a']='L', ['f'-'a']='L', ['g'-'a']='L',
    ['d'-'a']='j', ['i'-'a']='j', ['o'-'a']='j', ['u'-'a']='j', ['x'-'a']='j',
    ['p'-'a']='j'
};

static int wprintf_core(FOut *f, const wchar_t *fmt, va_list *ap, union arg *nl_arg, int *nl_type)
{
    wchar_t *s = (wchar_t*)fmt;
    unsigned int l10n = 0;
    int w, p;
    union arg arg;
    int argpos;
    unsigned st, ps;
    int cnt = 0, l = 0;
    int i;
    int t;
    char *bs;
    char charfmt[16];
    wchar_t wc;

    for (;;)
    {
        wchar_t *a, *z;
        unsigned int litpct, fl;
        /* Update output count, end loop when fmt is exhausted */
        if (cnt >= 0)
        {
            if (l > INT_MAX - cnt)
            {
                if (!out_error(f))
                    errno = EOVERFLOW;
                cnt = -1;
            }
            else
                cnt += l;
        }
        if (!*s)
            break;

        /* Handle literal text and %% format specifiers */
        for (a=s; *s && *s!='%'; s++);
        litpct = (unsigned int) (_wcsspn(s, L"%")/2); /* Optimize %%%% runs */
        z  = s + litpct;
        s += 2 * litpct;
        l = (int)(z - a);
        if (f)
            out(f, a, (size_t)l);
        if (l)
            continue;

        if (iswdigit(s[1]) && (s[2] == '$'))
        {
            l10n = 1;
            argpos = (s[1] - '0');
            s += 3;
        }
        else
        {
            argpos = -1;
            s++;
        }

        /* Read modifier flags */
        for (fl = 0; ((((unsigned)*s - ' ') < 32) && (__U_FLAGMASK &(1U << (*s - ' ')))); s++)
            fl |= (1U << (*s - ' '));

        /* Read field width */
        if (*s == '*')
        {
            if (iswdigit(s[1]) && s[2]=='$')
            {
                l10n=1;
                nl_type[s[1]-'0'] = INT;
                w = (int)nl_arg[s[1]-'0'].i;
                s+=3;
            }
            else if (!l10n)
            {
                w = f ? va_arg(*ap, int) : 0;
                s++;
            }
            else
                return -1;
            if (w < 0)
                fl |= __U_LEFT_ADJ, w =-w;
        }
        else if ((w = getint(&s))<0)
            return -1;

        /* Read precision */
        if (*s == '.' && s[1]=='*')
        {
            if (isdigit(s[2]) && s[3]=='$')
            {
                nl_type[s[2]-'0'] = INT;
                p = (int)nl_arg[s[2]-'0'].i;
                s+=4;
            }
            else if (!l10n)
            {
                p = f ? va_arg(*ap, int) : 0;
                s+=2;
            }
            else
                return -1;
        }
        else if (*s=='.')
        {
            s++;
            p = getint(&s);
        }
        else
            p = -1;

        /* Format specifier state machine */
        st = 0;
        do
        {
            if (__OOP(*s))
                return -1;
            ps=st;
            st=states[st]S(*s++);
        }
        while ((st - 1) < STOP);
        if (!st)
            return -1;

        /* Check validity of argument type (nl/normal) */
        if (st==NOARG)
        {
            if (argpos>=0)
                return -1;
            else if (!f)
                continue;
        }
        else
        {
            if (argpos >= 0)
            {
                nl_type[argpos] = (int)st;
                arg = nl_arg[argpos];
            }
            else if (f)
                pop_arg(&arg, (int)st, ap);
            else
                return 0;
        }

        if (!f)
            continue;
        t = s[-1];
        if (ps && (t&15)==3)
            t&=~32;

        switch (t)
        {
        case 'n':
            switch(ps)
            {
            case BARE:
                *(int*)arg.p = (int)cnt;
                break;
            case LPRE:
                *(long*)arg.p = (long)cnt;
                break;
            case LLPRE:
                *(long long*)arg.p = (long long)cnt;
                break;
            case HPRE:
                *(unsigned short*)arg.p = (unsigned short)cnt;
                break;
            case HHPRE:
                *(unsigned char*)arg.p = (unsigned char)cnt;
                break;
            case ZTPRE:
                *(size_t*)arg.p = (size_t)cnt;
                break;
            case JPRE:
                *(uintmax_t*)arg.p = (uintmax_t)cnt;
                break;
            default:
                *(uintmax_t*)arg.p = (uintmax_t)0;
                break;
            }
            continue;
        case 'c':
            out_putwc(_btowc((int)arg.i), f);
            l = 1;
            continue;
        case 'C':
            out_putwc((wchar_t)arg.i, f);
            l = 1;
            continue;
        case 'S':
            a = arg.p;
            z = _wmemchr(a, 0, (size_t)p);
            if (!z)
                z = a + p;
            else
                p = (int)(z - a);
            if (w < p)
                w = p;
            if (!(fl & __U_LEFT_ADJ))
                out_printf(f, "%.*s", (w - p), "");
            out(f, a, (size_t)p);
            if ((fl & __U_LEFT_ADJ))
                out_printf(f, "%.*s", (w - p), "");
            l = w;
            continue;
        case 's':
            bs = arg.p;
            if (p < 0)
                p = INT_MAX;
            for (i = l = 0; ((l < p) && ((i = _mbtowc(&wc, bs, MB_LEN_MAX)) > 0)); bs += i, l++);
            if (i < 0)
                return -1;
            p = l;
            if (w < p)
                w=p;
            if (!(fl & __U_LEFT_ADJ))
                out_printf(f, "%.*s", w-p, "");
            bs = arg.p;
            while (l--)
            {
                i = _mbtowc(&wc, bs, MB_LEN_MAX);
                bs+=i;
                out_putwc(wc, f);
            }
            if ((fl & __U_LEFT_ADJ))
                out_printf(f, "%.*s", w-p, "");
            l=w;
            continue;
        default:
            break;
        }

        snprintf(charfmt, sizeof charfmt, "%%%s%s%s%s%s*.*%c%c",
                 ((!(fl & __U_ALT_FORM)) ? "" : "#"),
                 ((!(fl & __U_MARK_POS)) ? "" : "+"),
                 ((!(fl & __U_LEFT_ADJ)) ? "" : "-"),
                 ((!(fl & __U_PAD_POS))  ? "" : " "),
                 ((!(fl & __U_ZERO_PAD)) ? "" : "0"),
                 sizeprefix[(t|32)-'a'], t);

        switch (t|32)
        {
        case 'a':
        case 'e':
        case 'f':
        case 'g':
            l = out_printf(f, charfmt, w, p, arg.f);
            break;
        case 'd':
        case 'i':
        case 'o':
        case 'u':
        case 'x':
        case 'p':
            l = out_printf(f, charfmt, w, p, arg.i);
            break;
        default:
            break;
        }
    }

    if (f)
        return cnt;
    if (!l10n)
        return 0;

    for (i = 1; i <= __ARGMAX && nl_type[i]; i++)
        pop_arg(nl_arg+i, nl_type[i], ap);
    for (; i <= __ARGMAX && !nl_type[i]; i++);
    if (i <= __ARGMAX)
        return -1;
    return 1;
}

int _vfwprintf(FILE *restrict f, const wchar_t *restrict fmt, va_list ap)
{
    va_list ap2;
    int ret, nl_type[__ARGMAX] = {0};
    union arg nl_arg[__ARGMAX];
    FOut _out[1];
    out_init_file(_out, f);
    va_copy(ap2, ap);

    // Check for error in format string before writing anything to file.
    if (wprintf_core(0, fmt, &ap2, nl_arg, nl_type) < 0)
    {
        va_end(ap2);
        return -1;
    }
    ret = wprintf_core(_out, fmt, &ap2, nl_arg, nl_type);
    va_end(ap2);
    return ret;
}

int _fwprintf(FILE *restrict f, const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = _vfwprintf(f, fmt, ap);
    va_end(ap);
    return ret;
}

int _wprintf(const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = _vfwprintf(stdout, fmt, ap);
    va_end(ap);
    return ret;
}

int _vswprintf(wchar_t *restrict s, size_t l, const wchar_t *restrict fmt, va_list ap)
{
    va_list ap2;
    int ret, nl_type[__ARGMAX] = {0};
    union arg nl_arg[__ARGMAX];
    FOut _out[1];

    va_copy(ap2, ap);

    if ((!s) || (!l))
    {
        ret = wprintf_core(0, fmt, &ap2, nl_arg, nl_type);
        va_end(ap2);
        return ret;
    }
    out_init_buffer(_out, s, l);
    ret = wprintf_core(_out, fmt, &ap2, nl_arg, nl_type);
    va_end(ap2);

    if (out_overflow(_out))
        return -1;
    return ret;
}

int _swprintf(wchar_t *restrict s, size_t l, const wchar_t *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = _vswprintf(s, l, fmt, ap);
    va_end(ap);
    return ret;
}
