
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

#include <sys/stat.h>
#include <stdlib.h>
#include "libwchar.h"

static int __mkdirp(const char *s, mode_t m)
{
    char __AUTO *p = NULL;

    if (mkdir(s, m) == -1)
    {
        switch (errno)
        {
            case EEXIST: { return  0; }
            case ENOENT: { break; }
            default: { return -1; }
        }
        do
        {
            if ((p = (char*) _wbasedir_selector(3, (const void*)s, 0)) == NULL) { break; }
            if (__mkdirp(p, m) == 0) return mkdir(s, m);

        } while (0);

        errno = ENOENT;
        return -1;
    }
    errno = 0;
    return errno;
}

int u8wmkdir(const wchar_t *wc, mode_t m)
{
    int   ret = -1;
    char *b   = NULL;

    do
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL) ||
            (wcstou8s(b, wc) <= 0)
           ) { break; }

        ret = __mkdirp(b, m);

    } while(0);

    if (b != NULL) free(b);
    return ret;
}

int _wmkdir(const wchar_t *ws, mode_t m)
{
    wstocscvt(b, ws, -1);
    return __mkdirp(b, m);
}

int _wmkdir_s(const wchar_t *ws, size_t sz, mode_t m)
{
    wstocsncvt(b, ws, sz, -1);
    return __mkdirp(b, m);
}

int _wmkdir_ws(const string_ws *ws, mode_t m)
{
    wstrtocscvt(b, ws, -1);
    return __mkdirp(b, m);
}

int _wmkdir_selector(int sel, const void *w, size_t sz, mode_t m)
{
    switch(sel)
    {
        case 1: {
            return _wmkdir((const wchar_t*)w, m);
        }
        case 2: {
            return _wmkdir_ws((const string_ws*)w, m);
        }
        case 3: {
            return __mkdirp((const char*)w, m);
        }
        case 4: {
            return _wmkdir_s((const wchar_t*)w, sz, m);
        }
        default: {
            return -1;
        }
    }
}
