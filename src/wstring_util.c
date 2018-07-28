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

#include "libbuild.h"

#if defined(OS_WIN)
#   include "libwcharext.h"
#   define _wcsftime wcsftime

#else
#   include <stdio.h>
#   include <stdlib.h>
#   include "libwchar.h"

#endif

#include <time.h>

const unsigned char c_strip[0x100] =
{
    1,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

int wstring_isempty(const wchar_t *s, int sz)
{
    const wchar_t *c = s;
    sz = ((sz < 0) ? 0 : sz);

    if (!s)
    {
        errno = EINVAL;
        return 0;
    }

    while(sz--)
    {
        if ((*c > 0x100) || ((*c < 0x100) && (!c_strip[*c])))
        {
            return 1;
        }
        c++;
    }
    return 0;
}

string_ws wstring_trunc(const wchar_t *ws, int sz)
{
    int            osz = 0;
    const wchar_t *c   = ws,
                   *cc  = NULL;
    string_ws ss = { NULL, 0U };

    do
    {
        if ((!ws) || (sz <= 0))
        {
            errno = EINVAL;
            break;
        }

        cc = (ws + (sz - 1));

        while(osz < sz)
        {
            if ((*c < 0x100) && (!c_strip[*c]))
            {
                break;
            }
            c++;
            osz++;
        }
        sz -= osz;
        osz = 0;

        if (!sz)
        {
            break;
        }

        while(osz < sz)
        {
            if ((*cc < 0x100) && (!c_strip[*cc]))
            {
                break;
            }
            cc--;
            osz++;
        }
        sz -= osz;

    }
    while (0);

    ss.str = (wchar_t*)c;
    ss.sz  = (size_t)sz;
    return    ss;
}

size_t wstring_trunc_alloc(string_ws *dst, const wchar_t *ws, int sz)
{
#   if !defined(_MSC_VER)
    wchar_t __AUTO *p = dst->str;
#   endif

    if ((!dst) || (!ws))
    {
        errno = EINVAL;
        return 0U;
    }

    do
    {
        string_ws wss = wstring_trunc(ws, sz);
        if (
            (!wss.sz)                     ||
            (!wstring_alloc(dst, wss.sz)) ||
            (!_wmemcpy((void*)(dst->str + dst->sz), (const void*)wss.str, wss.sz))
        )
        {
            break;
        }

#   if !defined(_MSC_VER)
        p = NULL;
#   endif
        return dst->sz;
    }
    while (0);

    return 0U;
}


size_t wstring_alloc(string_ws *dst, size_t sz)
{
    if (!dst)
    {
        errno = EINVAL;
        return 0U;
    }
    dst->str = ((dst->str == NULL) ?
                calloc(sizeof(wchar_t), (sz + 1)) :
                realloc(dst->str, ((dst->sz + sz + 1) * sizeof(wchar_t)))
               );
    if (dst->str == NULL)
    {
        return 0U;
    }
    return (dst->sz + sz);
}

char * wstring_wstocs_alloc(const wchar_t *src)
{
    char __AUTO *p = NULL;
    char  *dst;
    size_t ssz;

    if (!src)
    {
        errno = EINVAL;
        return NULL;
    }

    if (
        ((ssz = _wcstombs(NULL, src, 0)) == 0)                          ||
        ((p   = calloc(sizeof(wchar_t), (ssz + sizeof(wchar_t)))) == 0) ||
        ((ssz = _wcstombs(p, src, (ssz + sizeof(char)))) == 0)
    )
    {
        return NULL;
    }

    p[ssz] = '\0';
    dst = p;
    p = NULL;
    return dst;
}

char * wstring_swstocs_alloc(const string_ws *src)
{
    if (!src)
    {
        errno = EINVAL;
        return NULL;
    }
    return wstring_wstocs_alloc(src->str);
}

size_t wstring_cstows_ws_alloc(string_ws *ws, const char *src)
{
#   if !defined(_MSC_VER)
    wchar_t __AUTO *p = NULL;
#   endif

    if ((!ws) || (!src))
    {
        errno = EINVAL;
        return 0U;
    }
    wstring_free(ws);

#   if !defined(_MSC_VER)
    p = ws->str;
#   endif

    if (
        (!src)                                                   ||
        ((ws->sz   = _mbstowcs(NULL, src, 0)) == 0)              ||
        ((ws->str  = calloc(sizeof(wchar_t), (ws->sz + (sizeof(wchar_t) * 2)))) == 0) ||
        ((ws->sz   = _mbstowcs(ws->str, src, (ws->sz + sizeof(wchar_t)))) == 0)
    )
    {
        ws->str = NULL;
        return 0U;
    }

    ws->str[ws->sz] = L'\0';
#   if !defined(_MSC_VER)
    p = NULL;
#   endif

    return ws->sz;
}

wchar_t * wstring_cstows_alloc(const char *src)
{
    string_ws ws = { NULL, 0U };

    if (!src)
    {
        errno = EINVAL;
        return 0U;
    }

    if (!wstring_cstows_ws_alloc(&ws, src))
    {
        return NULL;
    }
    return ws.str;
}

size_t wstring_wstocs(char dst[], size_t dsz, const wchar_t *src, size_t ssz)
{
    if (!src)
    {
        errno = EINVAL;
        return 0U;
    }

    ssz = ((!ssz) ? _wcslen(src) : ssz);
    dsz = ((ssz >= dsz) ? (dsz - 1) : dsz);
    if ((dsz = _wcstombs(dst, src, dsz)) == 0)
    {
        return 0U;
    }
    dst[dsz] = '\0';
    return dsz;
}

size_t wstring_wstocs_ws(char dst[], size_t dsz, const string_ws *src)
{
    return wstring_wstocs(dst, dsz, src->str, src->sz);
}

size_t wstring_cstows(wchar_t dst[], size_t dsz, const char *src, size_t ssz)
{
    if (!src)
    {
        errno = EINVAL;
        return 0U;
    }

    ssz = ((!ssz) ? strlen(src) : ssz);
    dsz = ((ssz >= dsz) ? (dsz - 1) : dsz);
    if ((dsz = _mbstowcs(dst, src, dsz)) == 0)
    {
        return 0U;
    }
    dst[dsz] = L'\0';
    return dsz;
}

size_t wstring_append(string_ws *dst, const wchar_t *s, size_t sz)
{
    if ((!dst) || (!s))
    {
        errno = EINVAL;
        return 0U;
    }

    if (
        ((!sz) && (!(sz = _wcslen(s))))    ||
        (!wstring_alloc(dst, sz))          ||
        (!_wmemcpy((void*)(dst->str + dst->sz), (const void*)s, sz))
    )
    {
        return 0U;
    }

    dst->sz          += sz;
    dst->str[dst->sz] = L'\0';
    return dst->sz;
}

size_t wstring_appends_(string_ws *dst, ...)
{
    size_t   i, sz  = 0U, cnt = 0U;
    wchar_t *ws;
#   if defined(_MSC_VER)
    va_list ap;
#   else
    va_list ap, ap2;
#   endif

    if (!dst)
    {
        errno = EINVAL;
        return 0U;
    }

    do
    {
#       if defined(_MSC_VER)
        string_ws wsarr[__ARGMAX] = {0};
        va_start(ap, dst);
#       else
        va_start(ap, dst);
        va_copy(ap2, ap);

        while ((ws = va_arg(ap2, wchar_t*)) != NULL)
        {
            cnt++;
        }
        va_end(ap2);

        if (!cnt)
        {
            va_end(ap);
            return 0U;
        }

        string_ws wsarr[cnt];
        cnt = 0U;
#       endif

        while ((ws = va_arg(ap, wchar_t*)) != NULL)
        {
            wsarr[cnt].str = ws;
            wsarr[cnt].sz  = wcslen(ws);
            sz += wsarr[cnt++].sz;
        }
        va_end(ap);

        if (
            (!sz)                  ||
            (!wstring_alloc(dst, sz))
        )
        {
            break;
        }

#       if defined(_MSC_VER)
        for (i = 0U; i < cnt; i++)
#       else
        for (i = 0U; i < __NELE(wsarr); i++)
#       endif
        {
            if (wsarr[i].str == NULL)
                break;
            (void) _wmemcpy((void*)(dst->str + dst->sz), (const void*)wsarr[i].str, wsarr[i].sz);
            dst->sz += wsarr[i].sz;
        }

        dst->str[dst->sz] = L'\0';
        return dst->sz;

    }
    while (0);

    wstring_free(dst);
    return 0U;
}

size_t wstring_append_cvt(string_ws *dst, const char *c, size_t sz)
{
#   if defined(_MSC_VER)
    wchar_t *s = NULL;
#   endif

    if ((!dst) || (!c))
    {
        errno = EINVAL;
        return 0U;
    }

    sz = ((!sz) ? strlen(c) : sz);

#   if defined(_MSC_VER)
    __try
    {
        if (!(s = calloc(sizeof(wchar_t),(sz + 1))))
        {
            return 0U;
        }
#   else
    {
        wchar_t s[(sz + 1)];
#   endif

        if ((sz = wstring_cstows(s, (sz + 1), c, sz)) <= 0)
        {
            return 0U;
        }
        return wstring_append(dst, s, sz);

#   if defined(_MSC_VER)
    }
    __finally
    {
        if (s)
            free(s);
#   endif
    }
}

size_t wstring_format(string_ws *dst, const wchar_t *fmt, ...)
{
    size_t  ret = 0U;
#   if !defined(_MSC_VER)
    wchar_t __AUTO *p = NULL;
#   endif
    va_list ap;

    if ((!dst) || (!fmt))
    {
        errno = EINVAL;
        return ret;
    }

    va_start(ap, fmt);

    do
    {
#       if (defined(_MSC_VER) || defined(BUILD_MINGW64))
        int sz = 0;
#       else
        /** TODO (ClnViewer#1#24.07.2018): *nix -> make _vswprintf -> wprintf_core size output */
        /** \atention For MinGW32 always fixing output buffer size 8192 byte.
            https://sourceforge.net/p/mingw/bugs/1728/#4a30/036a
            http://vsokovikov.narod.ru/New_MSDN_API/Add_func_runtime_C/fn_vsprintf.htm
         */
        int sz = 8192;
#       endif
#       if !defined(_MSC_VER)
        p = dst->str;
#       endif

        if (
#           if (defined(_MSC_VER) || defined(BUILD_MINGW64))
            ((sz = _vswprintf(NULL, 0, fmt, ap)) <= 0)   ||
#           endif
            (!wstring_alloc(dst, sz))                    ||
#           if defined(BUILD_MINGW32)
            (_vswprintf((wchar_t*)(dst->str + dst->sz), fmt, ap) <= 0)
#           else
            (_vswprintf((void*)(dst->str + dst->sz), (sz + 1), fmt, ap) <= 0)
#           endif
        )
        {
            break;
        }

        dst->sz  = (size_t) _wcslen(dst->str);
#       if (!defined(_MSC_VER) && !defined(BUILD_MINGW))
        if (!(dst->str = realloc(dst->str, ((dst->sz + 1) * sizeof(wchar_t)))))
        {
            dst->sz = 0U;
            break;
        }
#       endif
#       if !defined(_MSC_VER)
        p = NULL;
#       endif
        ret = dst->sz;
    }
    while (0);

    va_end(ap);
    return ret;
}

wchar_t * wstring_timeformat(const wchar_t *src, size_t sz, const wchar_t *fmtin, const wchar_t *fmtout)
{
#   define __TMF_OUT_SIZE 250

    wchar_t __AUTO *p = NULL, *s = NULL;
    sz = ((!sz) ? _wcslen(src) : sz);

    if ((!src) || (!sz) || (!fmtin) || (!fmtout))
    {
        errno = EINVAL;
        return NULL;
    }

    do
    {
        size_t   osz;
        wchar_t *out;
        struct tm tms = {0};

#       if defined(_MSC_VER)
        __try
        {
#       endif

            if (
                ((p = calloc(sizeof(wchar_t), __TMF_OUT_SIZE)) == NULL) ||
                ((s = calloc(sizeof(wchar_t), (sz + 1))) == NULL)       ||
                (_wmemcpy(s, src, sz) == NULL)
            )
            {
                break;
            }

            s[sz] = L'\0';

            if (
                (_wcsptime(s, fmtin, &tms) != NULL) ||
                (!(osz = _wcsftime(p, (__TMF_OUT_SIZE * sizeof(wchar_t)), fmtout, &tms)))
            )
            {
                break;
            }

            if (!(p = realloc(p, ((osz + 1) * sizeof(wchar_t)))))
            {
                break;
            }

            p[osz] = L'\0';
            out = p;
            p = NULL;

            return out;

#       if defined(_MSC_VER)
        }
        __finally
        {
            if (s != NULL)
            {
                free(s);
                s = NULL;
            }
        }
#       endif

    }
    while (0);

#   if defined(_MSC_VER)
    if (p != NULL)
        free(p);
#   endif
    return NULL;
}

wchar_t * wstring_timeformat_ws(const string_ws *src, const wchar_t *fmtin, const wchar_t *fmtout)
{
    if (!src)
    {
        errno = EINVAL;
        return NULL;
    }
    return wstring_timeformat(src->str, src->sz, fmtin, fmtout);
}

void wstring_free(string_ws *dst)
{
    if (!dst)
    {
        return;
    }
    if (dst->str != NULL)
    {
        free(dst->str);
    }

    dst->str = NULL;
    dst->sz  = 0;
}
