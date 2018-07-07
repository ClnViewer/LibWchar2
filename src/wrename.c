
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

#include <stdio.h>
#include <stdlib.h>
#include "libwchar.h"

int u8wrename(const wchar_t *o, const wchar_t *n)
{
    int   ret = -1;
    char *ob  = NULL,
         *nb  = NULL;
    do
    {
        if (
            ((ob = calloc(1, wcstou8s(NULL, o) + 1)) == NULL) ||
            (wcstou8s(ob, o) <= 0)                            ||
            ((nb = calloc(1, wcstou8s(NULL, n) + 1)) == NULL) ||
            (wcstou8s(nb, n) <= 0)
           ) { break; }

        ret = rename(ob, nb);

    } while(0);

    if (ob != NULL) free(ob);
    if (nb != NULL) free(nb);
    return ret;
}

int _wrename(const wchar_t *o, const wchar_t *n)
{
    wstocscvt(ob, o, -1);
    wstocscvt(nb, n, -1);
    return rename(ob, nb);
}

int _wrename_s(const wchar_t *o, size_t osz, const wchar_t *n, size_t nsz)
{
    wstocsncvt(ob, o, osz, -1);
    wstocsncvt(nb, n, nsz, -1);
    return rename(ob, nb);
}

int _wrename_ws(const string_ws *o, const string_ws *n)
{
    wstrtocscvt(ob, o, -1);
    wstrtocscvt(nb, n, -1);
    return rename(ob, nb);
}

int _wrename_selector(int sel, const void *w, size_t osz, const void *s, size_t nsz)
{
    switch(sel)
    {
        case 1: {
            return _wrename((const wchar_t*)w, (const wchar_t*)s);
        }
        case 2: {
            return _wrename_ws((const string_ws*)w, (const string_ws*)s);
        }
        case 3: {
            return rename((const char*)w, (const char*)s);
        }
        case 4: {
            return _wrename_s((const wchar_t*)w, osz, (const wchar_t*)s, nsz);
        }
        default: {
            return -1;
        }
    }
}
