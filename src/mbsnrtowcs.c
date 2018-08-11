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

size_t _mbsnrtowcs(wchar_t *restrict wcs, const char **restrict src, size_t n, size_t wn, mbstate_t *restrict st)
{
    size_t l, cnt=0, n2;
    wchar_t *ws, wbuf[256];
    const char *s = *src;

    if (!wcs)
        ws = wbuf, wn = sizeof wbuf / sizeof *wbuf;
    else
        ws = wcs;

    /* making sure output buffer size is at most n/4 will ensure
     * that mbsrtowcs never reads more than n input bytes. thus
     * we can use mbsrtowcs as long as it's practical.. */

    while ( s && wn && ( ((n2=n/4) >= wn) || (n2 > 32) ) )
    {
        if (n2>=wn)
            n2=wn;
        n -= n2;
        l = _mbsrtowcs(ws, &s, n2, st);
        if (!(l+1))
        {
            cnt = l;
            wn = 0;
            break;
        }
        if (ws != wbuf)
        {
            ws += l;
            wn -= l;
        }
        cnt += l;
    }
    if (s)
        while (wn && n)
        {
            l = _mbrtowc(ws, s, n, st);
            if (l+2<=2)
            {
                if (!(l+1))
                {
                    cnt = l;
                    break;
                }
                if (!l)
                {
                    s = 0;
                    break;
                }
                /* have to roll back partial character */
                *(unsigned *)st = 0;
                break;
            }
            s += l;
            n -= l;
            /* safe - this loop runs fewer than sizeof(wbuf)/8 times */
            ws++;
            wn--;
            cnt++;
        }
    if (wcs)
        *src = s;
    return cnt;
}
