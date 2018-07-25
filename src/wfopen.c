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
#   include <stdio.h>
#   include "libwcharext.h"

#else
#   include <stdio.h>
#   include <stdlib.h>
#   include "libwchar.h"

#endif

#if defined(OS_WIN)

#if defined(OS_WIN_FOPEN_MIXED_CHAR)

static FILE * __wfopen(const wchar_t *w, const char *c, const char *m)
{
    FILE   *fp         = NULL;

#   if defined(_MSC_VER)
    wchar_t bmode[(256 + 1)] = {0};
#   elif defined(BUILD_MINGW)
    char fpath[(256 + 1 * sizeof(wchar_t))] = {0};
#   endif
    errno = 0;

#   if defined(_MSC_VER)
    __try
    {
#   endif

        if (
            ((w == NULL) && (c == NULL))       ||
            (
#           if defined(_MSC_VER)
                ((c != NULL) && (fopen_s(&fp, c, m) != 0)) ||
#           elif defined(BUILD_MINGW)
                ((c != NULL) && (!(fp = fopen(c, m)))) ||
#           endif
                ((w != NULL) &&
                 (
#                if defined(_MSC_VER)
                     (!wstring_cstows(bmode, wsizeof(bmode), m, 0)) ||
                     (_wfopen_s(&fp, w, (const wchar_t*)&bmode) != 0)
#                elif defined(BUILD_MINGW)
                     (!wstring_wstocs(fpath, sizeof(fpath), w, 0)) ||
                     (!(fp = fopen(fpath, m)))
#                endif
                 )
                )
            )
        )
        {
            return NULL;
        }

        return fp;

#   if defined(_MSC_VER)
    }
    __except(__seh_except())
    {
        errno = EFAULT;
        return NULL;
    }
#   endif

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
    char __AUTO *b = NULL;

#   if defined(_MSC_VER)
    __try
    {
#   endif
        if (
            ((b = calloc(1, wcstou8s(NULL, w) + 1)) == NULL) ||
            (wcstou8s(b, w) <= 0)
        )
        {
            return NULL;
        }

        return __wfopen(NULL, b, m);

#   if defined(_MSC_VER)
    }
    __finally
    {
        if (b != NULL)
            free(b);
    }
#   endif
}

#else /* is NOT OS_WIN_FOPEN_MIXED_CHAR */

FILE * u8wfopen(const wchar_t *w, const wchar_t *m)
{
    char __AUTO *b = NULL;
    char         t[256] = {0};

#   if defined(_MSC_VER)
    __try
    {
#   endif
        if (
            (!wstring_wstocs(t, sizeof(t), m, 0))            ||
            ((b = calloc(1, wcstou8s(NULL, w) + 1)) == NULL) ||
            (wcstou8s(b, w) <= 0)
        )
        {
            return NULL;
        }

    return fopen(b, t);

#   if defined(_MSC_VER)
    }
    __finally
    {
        if (b != NULL)
            free(b);
    }
#   endif
}

FILE * _wfopen_s_(const wchar_t *w, size_t sz, const wchar_t *m)
{
    (void) sz;
    return _wfopen(w, m);
}

FILE * _wfopen_ws(const string_ws *ws, const wchar_t *m)
{
    return _wfopen(ws->str, m);
}

#endif /* OS_WIN_FOPEN_MIXED_CHAR */

#else

/** non WINxx realization */

FILE * u8wfopen(const wchar_t *w, const wchar_t *m)
{
    char __AUTO *b = NULL;
    char         t[256] = {0};

    if (
        (!wstring_wstocs(t, sizeof(t), m, 0))            ||
        ((b = calloc(1, wcstou8s(NULL, w) + 1)) == NULL) ||
        (wcstou8s(b, w) <= 0)
    )
    {
        return NULL;
    }

    return fopen(b, t);
}

FILE * _wfopen(const wchar_t *w, const wchar_t *m)
{
    wstocscvt(b, w, NULL);
    wstocscvt(t, m, NULL);
    return fopen(b, t);
}

FILE * _wfopen_s(const wchar_t *w, size_t sz, const wchar_t *m)
{
    wstocsncvt(b, w, sz, NULL);
    wstocscvt(t, m, NULL);
    return fopen(b, t);
}

FILE * _wfopen_ws(const string_ws *ws, const wchar_t *m)
{
    wstrtocscvt(b, ws, NULL);
    wstocscvt(t, m, NULL);
    return fopen(b, t);
}

FILE * _wfopen_selector(int sel, const void *w, size_t sz, const void *m)
{
    switch(sel)
    {
    case 1:
    {
        return _wfopen((const wchar_t*)w, (const wchar_t*)m);
    }
    case 2:
    {
        return _wfopen_ws((const string_ws*)w, (const wchar_t*)m);
    }
    case 3:
    {
        return fopen((const char*)w, (const char*)m);
    }
    case 4:
    {
        return _wfopen_s((const wchar_t*)w, sz, (const wchar_t*)m);
    }
    default:
    {
        errno = EFAULT;
        return NULL;
    }
    }
}
#endif


