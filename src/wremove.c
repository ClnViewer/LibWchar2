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
#   include <stdio.h>
#   include <stdlib.h>
#   include "libwchar.h"

#endif

int u8wremove(const wchar_t *wc)
{
    char __AUTO(__autofree) *b = NULL;

#   if defined(_MSC_VER)
    __try
    {
#   endif
        if (
            ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL) ||
            (wcstou8s(b, wc) <= 0)
        )
        {
            return -1;
        }

        return remove(b);

#   if defined(_MSC_VER)
    }
    __finally
    {
        if (b != NULL)
            free(b);
    }
#   endif
}

#if defined(OS_WIN)

int _wremove_s(const wchar_t *ws, size_t sz)
{
    (void) sz;
    return _wremove(ws);
}

int _wremove_ws(const string_ws *ws)
{
    return _wremove(ws->str);
}

#else

int _wremove(const wchar_t *ws)
{
    wstocscvt(b, ws, -1);
    return remove(b);
}

int _wremove_s(const wchar_t *ws, size_t sz)
{
    wstocsncvt(b, ws, sz, -1);
    return remove(b);
}

int _wremove_ws(const string_ws *ws)
{
    wstrtocscvt(b, ws, -1);
    return remove(b);
}

int _wremove_selector(int sel, const void *w, size_t sz)
{
    switch(sel)
    {
    case 1:
    {
        return _wremove((const wchar_t*)w);
    }
    case 2:
    {
        return _wremove_ws((const string_ws*)w);
    }
    case 3:
    {
        return remove((const char*)w);
    }
    case 4:
    {
        return _wremove_s((const wchar_t*)w, sz);
    }
    default:
    {
        errno = EFAULT;
        return -1;
    }
    }
}

#endif

