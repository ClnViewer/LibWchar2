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
#   include <stdlib.h>
#   include "libwchar.h"

#endif

#define __PATH_SPLIT(_N,_T,_F,_P,_E)                            \
    static _T * __WEV(__dirname_,_N)(_T *ws, int issep) {       \
        int i, n, off;                                          \
        _T *p;                                                  \
        if (                                                    \
            (!(p = _F(ws, _P))) ||                              \
            ((off = (int)(p - ws)) <= 0)                        \
           ) { return (_T *)ws; }                               \
        off += ((issep > 0) ? 1 : 0);                           \
        p = (_T *)ws;                                           \
        for (i = n = 0; ((i < off) && (n < off)); i++, n++) {   \
            p[n] = ((p[n] == p[i]) ? p[n] : p[i]);              \
            if (p[i] == _P) {                                   \
                while ((i < off) && (p[i] == _P)) { i++; } --i; \
            }                                                   \
        }                                                       \
        if ((!issep) && (p[(n - 1)] == _P)) --n;                \
        p[n] = _E;                                              \
        return p;                                               \
    }

#define __PATH_BASE(_N,_T,_F)                                   \
    static _T * __WEV(__basepart_,_N)(const _T *ws, _T wc) {    \
        _T *p;                                                  \
        if (!(p = _F(ws, wc))) { return NULL; }                 \
        return (p + 1);                                         \
    }

__PATH_SPLIT(w, wchar_t, _wcsrchr, __WEV(L,__PSEP), L'\0')
__PATH_BASE(w, wchar_t, _wcsrchr)

#if !defined(_MSC_VER)
__PATH_SPLIT(c, char, strrchr, __PSEP, '\0')
__PATH_BASE(c, char, strrchr)
#endif


wchar_t * _wbasename(const wchar_t *ws)
{
    return __basepart_w(ws, __WEV(L,__PSEP));
}

wchar_t * _wbasename_ws(const string_ws *ws)
{
    return __basepart_w(ws->str, __WEV(L,__PSEP));
}

wchar_t * _wbaseext(const wchar_t *ws)
{
    return __basepart_w(ws, L'.');
}

wchar_t * _wbaseext_ws(const string_ws *ws)
{
    return __basepart_w(ws->str, L'.');
}

wchar_t * _wbasedir(const wchar_t *ws, int issep)
{
    wchar_t *p  = NULL;
    size_t   sz = _wcslen(ws);

    if (
        (!sz)  ||
        ((p = calloc(sizeof(wchar_t), sz)) == NULL)
    )
    {
        return NULL;
    }

    (void) _wmemcpy((void*)p, (void*)ws, sz);
    return __dirname_w(p, issep);
}

wchar_t * _wbasedir_ws(const string_ws *ws, int issep)
{
    wchar_t *p  = NULL;
    size_t   sz = ws->sz;
    sz = ((!sz) ? _wcslen(ws->str) : sz);

    if (
        (!sz)  ||
        ((p = calloc(sizeof(wchar_t), sz)) == NULL)
    )
    {
        return NULL;
    }

    (void) _wmemcpy((void*)p, (void*)ws->str, sz);
    return __dirname_w(p, issep);
}

#if !defined(_MSC_VER)

void * _wbasedir_selector(int sel, const void *w, int issep)
{
    size_t      sz  = 0,
                esz = 0;
    void       *p   = NULL;
    const void *pp  = NULL;

    switch(sel)
    {
    case 1:
    case 4:
    {
        esz = sizeof(wchar_t);
        sz  = _wcslen((const wchar_t*)w);
        pp  = w;
        break;
    }
    case 2:
    {
        esz = sizeof(wchar_t);
        sz  = ((const string_ws*)w)->sz;
        sz  = ((!sz) ? _wcslen(((const string_ws*)w)->str) : sz);
        pp  = (const void*)((const string_ws*)w)->str;
        break;
    }
    case 3:
    {
        esz = sizeof(char);
        sz  = strlen((char*)w);
        pp  = w;
        break;
    }
    default:
    {
        errno = EFAULT;
        return NULL;
    }
    }

    if (
        (!sz)  ||
        (!pp)      ||
        ((p = calloc(esz, sz)) == NULL)
    )
    {
        return NULL;
    }

    switch(sel)
    {
    case 1:
    case 2:
    case 4:
    {
        _wmemcpy(p, pp, sz);
        break;
    }
    case 3:
    {
        memcpy(p, pp, sz);
        break;
    }
    default:
    {
        break;
    }
    }

    if (!p)
    {
        return NULL;
    }

    switch(sel)
    {
    case 1:
    case 2:
    case 4:
    {
        return (void*) __dirname_w((wchar_t*)p, issep);
    }
    case 3:
    {
        return (void*) __dirname_c((char*)p, issep);
    }
    default:
    {
        errno = EFAULT;
        return NULL;
    }
    }
}

void * _wbaseext_selector(int sel, const void *w)
{
    switch(sel)
    {
    case 1:
    case 4:
    {
        return (void*) _wbaseext((const wchar_t*)w);
    }
    case 2:
    {
        return (void*) _wbaseext_ws((const string_ws*)w);
    }
    case 3:
    {
        return (void*) __basepart_c((char*)w, '.');
    }
    default:
    {
        return NULL;
    }
    }
}

void * _wbasename_selector(int sel, const void *w)
{
    switch(sel)
    {
    case 1:
    case 4:
    {
        return (void*) _wbasename((const wchar_t*)w);
    }
    case 2:
    {
        return (void*) _wbasename_ws((const string_ws*)w);
    }
    case 3:
    {
        return (void*) __basepart_c((char*)w, __PSEP);
    }
    default:
    {
        return NULL;
    }
    }
}
#endif
