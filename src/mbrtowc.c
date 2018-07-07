
/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
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

size_t _mbrtowc(wchar_t *restrict wc, const char *restrict src, size_t n, mbstate_t *restrict st)
{
    static unsigned is = 0U;
    unsigned int c;
    const unsigned char *s = (const void*)src;
    const unsigned int N = n;

    if (!st)
    {
        st = (void*)&is;
    }
    c = *(unsigned*)st;

    if (!s)
    {
        if (c) goto ilseq;
        return 0;
    }
    else if (!wc)
    {
        wc = (void*)&wc;
    }
    if (!n)
    {
        return -2;
    }
    if (!c)
    {
        if (*s < 0x80)
        {
            return !!(*wc = *s);
        }
        if ((*s - __SA) > (__SB - __SA))
        {
            goto ilseq;
        }
        c = bittab[(*s++ - __SA)];
        n--;
    }
    if (n) {
        if (__OOB(c,*s)) goto ilseq;
loop:
        c = ((c << 6) | (*s++ - 0x80)); n--;
        if (!(c & (1U << 31))) {
            *(unsigned*)st = 0;
            *wc = c;
            return N-n;
        }
        if (n) {
            if ((*s - 0x80U) >= 0x40) goto ilseq;
            goto loop;
        }
    }

    *(unsigned*)st = c;
    return -2;
ilseq:
    errno = EILSEQ;
    *(unsigned*)st = 0;
    return -1;
}
