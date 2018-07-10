
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

#if (defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__MINGW32__))
#   define __PSEP '\\'
#else
#   define __PSEP '/'
#endif

#define __PATH_SPLIT(_N,_T,_F,_P,_E)                            \
    static _T * __WEV(__dirname_,_N)(_T *ws, int issep) {       \
        int i, n, off;                                          \
        _T *p;                                                  \
        if (                                                    \
            (!(p = _F(ws, _P))) ||                              \
            ((off = (p - ws)) <= 0)                             \
           ) { return (_T *)ws; }                               \
        off += ((issep > 0) ? 1 : 0);                           \
        p = (_T *)ws;                                           \
        for (i = n = 0; i < off; i++, n++) {                    \
            p[n] = ((p[n] == p[i]) ? p[n] : p[i]);              \
            if (p[i] == _P) {                                   \
                while ((p[i] == _P) && (i < off)) { i++; } --i; \
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
__PATH_SPLIT(c, char, strrchr, __PSEP, '\0')

__PATH_BASE(w, wchar_t, _wcsrchr)
__PATH_BASE(c, char, strrchr)


wchar_t * _wpathnormalize(const wchar_t *ws, int sz)
{
    int i, n;
    wchar_t *p;
    sz = ((sz > 0) ? sz : (int) _wcslen(ws));

    if (
        (sz <= 0)  ||
        ((p = calloc(sizeof(wchar_t), sz)) == NULL)
       ) { return NULL; }

    _wmemcpy(p, ws, sz);

    for (i = n = 0; i < sz; i++, n++)
    {
        p[n] = ((p[n] == p[i]) ? p[n] : p[i]);
        if (p[i] == __WEV(L,__PSEP))
        {
            while ((p[i] == __WEV(L,__PSEP)) && (i < sz)) {  i++; } --i;
        }
    }

    p[n] = L'\0';
    return p;
}

wchar_t * _wpathnormalize_ws(const string_ws *ws)
{
    return _wpathnormalize(ws->str, ws->sz);
}

wchar_t * _wbasename(const wchar_t *ws)
{
    return __basepart_w(ws, __WEV(L,__PSEP));
}

wchar_t * _wbasename_ws(const string_ws *ws)
{
    return __basepart_w(ws->str, __WEV(L,__PSEP));
}

void * _wbasename_selector(int sel, const void *w)
{
    switch(sel)
    {
        case 1:
        case 4: {
            return (void*) _wbasename((const wchar_t*)w);
        }
        case 2: {
            return (void*) _wbasename_ws((const string_ws*)w);
        }
        case 3: {
            return (void*) __basepart_c((char*)w, __PSEP);
        }
        default: {
            return NULL;
        }
    }
}

wchar_t * _wbaseext(const wchar_t *ws)
{
    return __basepart_w(ws, L'.');
}

wchar_t * _wbaseext_ws(const string_ws *ws)
{
    return __basepart_w(ws->str, L'.');
}

void * _wbaseext_selector(int sel, const void *w)
{
    switch(sel)
    {
        case 1:
        case 4: {
            return (void*) _wbaseext((const wchar_t*)w);
        }
        case 2: {
            return (void*) _wbaseext_ws((const string_ws*)w);
        }
        case 3: {
            return (void*) __basepart_c((char*)w, '.');
        }
        default: {
            return NULL;
        }
    }
}

wchar_t * _wbasedir(const wchar_t *ws, int issep)
{
    wchar_t *p  = NULL;
    int      sz = (int) _wcslen(ws);

    if (
        (sz <= 0)  ||
        ((p = calloc(sizeof(wchar_t), sz)) == NULL)
       ) { return NULL; }

    _wmemcpy((void*)p, (void*)ws, sz);
    return __dirname_w(p, issep);
}

wchar_t * _wbasedir_ws(const string_ws *ws, int issep)
{
    wchar_t *p  = NULL;
    int      sz = ws->sz;
             sz = ((!sz) ? (int) _wcslen(ws->str) : sz);

    if (
        (sz <= 0)  ||
        ((p = calloc(sizeof(wchar_t), sz)) == NULL)
       ) { return NULL; }

    _wmemcpy((void*)p, (void*)ws->str, sz);
    return __dirname_w(p, issep);
}

void * _wbasedir_selector(int sel, const void *w, int issep)
{
    int         sz  = 0,
                esz = 0;
    void       *p   = NULL;
    const void *pp  = NULL;

    switch(sel)
    {
        case 1:
        case 4: {
            esz = sizeof(wchar_t);
            sz  = (int) _wcslen((const wchar_t*)w);
            pp  = w;
            break;
        }
        case 2: {
            esz = sizeof(wchar_t);
            sz  = ((const string_ws*)w)->sz;
            sz  = ((!sz) ? (int) _wcslen(((const string_ws*)w)->str) : sz);
            pp  = (const void*)((const string_ws*)w)->str;
            break;
        }
        case 3: {
            esz = sizeof(char);
            sz  = strlen((char*)w);
            pp  = w;
            break;
        }
        default: {
            return NULL;
        }
    }

    if (
        (sz <= 0)  ||
        (!pp)      ||
        ((p = calloc(esz, sz)) == NULL)
       ) { return NULL; }

    switch(sel)
    {
        case 1:
        case 2:
        case 4: {
            _wmemcpy(p, pp, sz);
            break;
        }
        case 3: {
            memcpy(p, pp, sz);
            break;
        }
        default: {
            break;
        }
    }

    if (!p) { return NULL; }

    switch(sel)
    {
        case 1:
        case 2:
        case 4: {
            return (void*) __dirname_w((wchar_t*)p, issep);
        }
        case 3: {
            return (void*) __dirname_c((char*)p, issep);
        }
        default: {
            return NULL;
        }
    }
}
