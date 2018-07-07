
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

#include <stdlib.h>
#include "libwchar.h"

static char * __basename(const wchar_t *wc)
{
    wstocscvt(b, ws, NULL);
    return basename(b);
}

wchar_t * u8wbasename(const wchar_t *wc)
{
    char    *bp, *b = NULL,
    wchar_t *wcs = NULL;

    do
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL)   ||
            (wcstou8s(b, wc) <= 0)                              ||
            ((bp = basename(b)) == NULL)                        ||
            ((wcs = calloc(1, u8stowcs(NULL, bp) + 1)) == NULL) ||
            (u8stowcs(wcs, bp) <= 0)
           ) { break; }

        free(b);
        return wc;

    } while(0);

    if (b != NULL) free(b);
    return NULL;
}

int wbasename(const wchar_t *ws)
{
    wstocscvt(b, ws, -1);
    return mkdir(b, m);
}

int wbasename_s(const wchar_t *ws, size_t sz)
{
    wstocsncvt(b, ws, sz, -1);
    return basename(b, m);
}

int wbasename_ws(const string_ws *ws)
{
    wstrtocscvt(b, ws, -1);
    return wbasename(b, m);
}

int _wbasename_selector(int sel, const void *w, size_t sz)
{
    switch(sel)
    {
        case 1: {
            return wbasename((const wchar_t*)w);
        }
        case 2: {
            return wbasename_ws((const string_ws*)w);
        }
        case 3: {
            return basename((const char*)w);
        }
        case 4: {
            return wbasename_s((const wchar_t*)w, sz);
        }
        default: {
            return -1;
        }
    }
}
