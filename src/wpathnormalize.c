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

wchar_t * _wpathnormalize(const wchar_t *ws, size_t sz)
{
    size_t i, n;
    wchar_t *p;
    sz = ((sz > 0) ? sz : _wcslen(ws));
    errno = 0;

    if (
        (sz <= 0)  ||
        ((p = calloc(sizeof(wchar_t), sz)) == NULL)
    )
    {
        return NULL;
    }

    _wmemcpy(p, ws, sz);

    for (i = n = 0; ((i < sz) && (n < sz)); i++, n++)
    {
        p[n] = ((p[n] == p[i]) ? p[n] : p[i]);
        if (p[i] == __WEV(L,__PSEP))
        {
            while ((i < sz) && (p[i] == __WEV(L,__PSEP)))
            {
                i++;
            }
            if (i) { --i; }
        }
    }

    p[n] = L'\0';
    return p;
}

wchar_t * _wpathnormalize_ws(const string_ws *ws)
{
    return _wpathnormalize(ws->str, ws->sz);
}

char * u8wpathnormalize(const wchar_t *ws)
{
    char *ob  = NULL;
    wchar_t __AUTO *wo = NULL;

#   if defined(_MSC_VER)
    __try
    {
#   endif

        do
        {
            if (
                ((wo = _wpathnormalize(ws, 0U)) == NULL)            ||
                ((ob = calloc(1, wcstou8s(NULL, wo) + 1)) == NULL) ||
                (wcstou8s(ob, wo) <= 0)
            )
            {
                break;
            }

            return ob;

        }
        while (0);

        if (ob != NULL)
            free(ob);
        return NULL;

#   if defined(_MSC_VER)
    }
    __finally
    {
        if (wo != NULL)
            free(wo);
    }
#   endif
}

