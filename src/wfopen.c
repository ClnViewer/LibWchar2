
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

#if defined(OS_WIN32) || defined(OS_WIN64) || defined(_MSC_VER)
#   include <stdio.h>
#   include "libwcharext.h"

#else
#   include <stdio.h>
#   include <stdlib.h>
#   include "libwchar.h"

#endif

#if defined(_MSC_VER)

static FILE * __wfopen(const wchar_t *w, const char *c, const char *m)
{
    FILE   *fp         = NULL;
    wchar_t bmode[256] = {0};

    if (
        ((!w) && (!c))                     ||
        (
            ((c) && (!fopen_s(&fp, c, m))) ||
            ((w) &&
                (
                    (!wstring_cstows(bmode, sizeof(bmode), m)) ||
                    (!_wfopen_s(&fp, w, bmode))
                )
            )
        )
       ) { return NULL; }

    return fp;
}

FILE * _wfopen_s_(const wchar_t *w, size_t sz, const char *m)
{
    (void) sz;
    return __wfopen(w, NULL, m);
}

FILE * _wfopen_ws(const string_ws *ws, const char *m)
{
    return __wfopen(ws->str, NULL, m);
}

FILE * u8wfopen(const wchar_t *w, const char *m)
{
    char *b = NULL;

    __try
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, w) + 1)) == NULL) ||
            (wcstou8s(b, w) <= 0)
           ) { return NULL; }

        return __wfopen(NULL, b, m);
    }
    __finally {
        if (b != NULL) free(b);
    }
}

#else

FILE * u8wfopen(const wchar_t *w, const char *m)
{
    char __AUTO *b = NULL;

    if (
        ((b = calloc(1, wcstou8s(NULL, w) + 1)) == NULL) ||
        (wcstou8s(b, w) <= 0)
       ) { return NULL; }

    return fopen(b, m);
}

FILE * _wfopen(const wchar_t *wc, const char *m)
{
    wstocscvt(b, wc, NULL);
    return fopen(b, m);
}

FILE * _wfopen_s(const wchar_t *wc, size_t sz, const char *m)
{
    wstocsncvt(b, wc, sz, NULL);
    return fopen(b, m);
}

FILE * _wfopen_ws(const string_ws *ws, const char *m)
{
    wstrtocscvt(b, ws, NULL);
    return fopen(b, m);
}

FILE * _wfopen_selector(int sel, const void *w, size_t sz, const void *m)
{
    switch(sel)
    {
        case 1: {
            return _wfopen((const wchar_t*)w, (const char*)m);
        }
        case 2: {
            return _wfopen_ws((const string_ws*)w, (const char*)m);
        }
        case 3: {
            return fopen((const char*)w, (const char*)m);
        }
        case 4: {
            return _wfopen_s((const wchar_t*)w, sz, (const char*)m);
        }
        default: {
            errno = EFAULT;
            return NULL;
        }
    }
}
#endif
