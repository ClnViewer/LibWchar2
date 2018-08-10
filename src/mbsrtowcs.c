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
 * This code was written by Rich Felker in 2010; no copyright is claimed.
 * This code is in the public domain. Attribution is appreciated but
 * unnecessary.
 */

#include "libwchar.h"

size_t _mbsrtowcs(wchar_t *restrict ws, const char **restrict src, size_t wn, mbstate_t *restrict st)
{
    const unsigned char *s = (const void *)*src;
    size_t wn0 = wn;
    unsigned c = 0;

    if (st && (c = *(unsigned *)st))
    {
        if (ws)
        {
            *(unsigned *)st = 0;
            goto resume;
        }
        else
        {
            goto resume0;
        }
    }

    if (!ws)
    {
        for (;;)
        {
            if (((*s - 1U) < 0x7f) && (((uintptr_t)s % 2) == 0))
            {
                unsigned short w;
                memcpy(&w, s, sizeof(unsigned short));
                while (!((w | (w - 0x01010101U)) & (0x80808080U)))
                {
                    s += 2;
                    wn -= 2;
                    memcpy(&w, s, sizeof(unsigned short));
                }
            }
            if (*s-1u < 0x7f)
            {
                s++;
                wn--;
                continue;
            }
            if (*s - __SA > __SB - __SA)
                break;
            c = bittab[*s++ - __SA];
resume0:
            if (__OOB(c,*s))
            {
                s--;
                break;
            }
            s++;
            if (c&(1U<<25))
            {
                if (*s-0x80u >= 0x40)
                {
                    s-=2;
                    break;
                }
                s++;
                if (c&(1U<<19))
                {
                    if (*s-0x80u >= 0x40)
                    {
                        s-=3;
                        break;
                    }
                    s++;
                }
            }
            wn--;
            c = 0;
        }
    }
    else
    {
        for (;;)
        {
            if (!wn)
            {
                return wn0;
            }
            if (((*s - 1U) < 0x7f) && (((uintptr_t)s % 2) == 0))
            {
                unsigned short w;
                memcpy(&w, s, sizeof(unsigned short));
                while ((wn >= 2) && !((w | (w - 0x01010101U)) & (0x80808080U)))
                {
                    *ws++ = *s++;
                    *ws++ = *s++;
                    wn -= 2;
                    memcpy(&w, s, sizeof(unsigned short));
                }
            }
            if (*s - 1U < 0x7f)
            {
                *ws++ = *s++;
                wn--;
                continue;
            }
            if (*s - __SA > __SB - __SA)
                break;
            c = bittab[*s++ - __SA];
resume:
            if (__OOB(c,*s))
            {
                s--;
                break;
            }
            c = ((c << 6) | (*s++ - 0x80U));
            if (c&(1U<<31))
            {
                if (*s-0x80U >= 0x40)
                {
                    s-=2;
                    break;
                }
                c = ((c << 6) | (*s++ - 0x80U));
                if (c&(1U<<31))
                {
                    if (*s-0x80U >= 0x40)
                    {
                        s-=3;
                        break;
                    }
                    c = ((c << 6) | (*s++ - 0x80U));
                }
            }
            *ws++ = (wchar_t)c;
            wn--;
            c = 0;
        }
    }

    if (!c && !*s)
    {
        if (ws)
        {
            *ws = 0;
            *src = 0;
        }
        return (wn0 - wn);
    }
    errno = EILSEQ;
    if (ws)
        *src = (const void *)s;
    return (size_t)-1;
}
