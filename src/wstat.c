
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libwchar.h"

int u8wstat(const wchar_t *wc, struct stat *st)
{
    int  ret       = -1;
    char __AUTO *b = NULL;

    do
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL) ||
            (wcstou8s(b, wc) <= 0)
           ) { break; }

        ret = stat(b, st);

    } while(0);

    return ret;
}

int _wstat(const wchar_t *ws, struct stat *st)
{
    wstocscvt(b, ws, -1);
    return stat(b, st);
}

int _wstat_s(const wchar_t *ws, size_t sz, struct stat *st)
{
    wstocsncvt(b, ws, sz, -1);
    return stat(b, st);
}

int _wstat_ws(const string_ws *ws, struct stat *st)
{
    wstrtocscvt(b, ws, -1);
    return stat(b, st);
}

int _wstat_selector(int sel, const void *w, size_t sz, const void *s)
{
    struct stat  sst,
                *st  = ((s == NULL) ? (struct stat*)&sst : (struct stat*)s);

    switch (sel)
    {
        case 1: {
            return _wstat((const wchar_t*)w, st);
        }
        case 2: {
            return _wstat_ws((const string_ws*)w, st);
        }
        case 3: {
            return stat((const char*)w, st);
        }
        case 4: {
            return _wstat_s((const wchar_t*)w, sz, st);
        }
        default: {
            errno = EFAULT;
            return -1;
        }
    }
}
