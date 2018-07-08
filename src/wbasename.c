
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

static wchar_t * __basepart(const wchar_t *ws, wchar_t wc)
{
    wchar_t *p;
    if (!(p = _wcsrchr(ws, wc))) { return NULL; }
    return (p + 1);
}

wchar_t * _wbasename(const wchar_t *ws)
{
    return __basepart(ws, L'/');
}

wchar_t * _wbasename_s(const wchar_t *ws, size_t sz)
{
    (void) sz;
    return __basepart(ws, L'/');
}

wchar_t * _wbasename_ws(const string_ws *ws)
{
    return __basepart(ws->str, L'/');
}

wchar_t * _wbasename_selector(int sel, const void *w, size_t sz)
{
    switch(sel)
    {
        case 1: {
            return _wbasename((const wchar_t*)w);
        }
        case 2: {
            return _wbasename_ws((const string_ws*)w);
        }
        case 3: {
            return NULL;
        }
        case 4: {
            return _wbasename_s((const wchar_t*)w, sz);
        }
        default: {
            return NULL;
        }
    }
}

wchar_t * _wbaseext(const wchar_t *ws)
{
    return __basepart(ws, L'.');
}

wchar_t * _wbaseext_s(const wchar_t *ws, size_t sz)
{
    (void) sz;
    return __basepart(ws, L'.');
}

wchar_t * _wbaseext_ws(const string_ws *ws)
{
    return __basepart(ws->str, L'.');
}

wchar_t * _wbaseext_selector(int sel, const void *w, size_t sz)
{
    switch(sel)
    {
        case 1: {
            return _wbaseext((const wchar_t*)w);
        }
        case 2: {
            return _wbaseext_ws((const string_ws*)w);
        }
        case 3: {
            return NULL;
        }
        case 4: {
            return _wbaseext_s((const wchar_t*)w, sz);
        }
        default: {
            return NULL;
        }
    }
}
