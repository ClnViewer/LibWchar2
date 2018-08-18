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

#else
#   include "libwchar.h"

#endif

int wcstocscmp(const char *c, wchar_t *w, size_t wsz)
{
    size_t         cnt  = 0;
    const wchar_t *wchr = w;
    const char    *cchr = c;

    mbstate_t state;
    memset((void*)&state, 0, sizeof(mbstate_t));

    while(*cchr)
    {
        size_t   len;
        wchar_t  wc;

        if (cnt == wsz)
        {
            return 0;
        }
        errno = 0;
        len = _mbsrtowcs(&wc, &cchr, 1U, (void*)&state);
        if ((len == (size_t)-1) || (len == (size_t)-2) || (errno == EILSEQ))
        {
            return -1;
        }
        else if (!len)
        {
            return 0;
        }
#       if !defined(OS_WIN)
        cchr += (int)len;
#       endif
        if (wchr[cnt++] != wc)
        {
            return 1;
        }
    }
    return 0;
}
