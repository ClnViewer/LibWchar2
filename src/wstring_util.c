
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
#include <string.h>
#include <stdlib.h>
#include "libwchar.h"

const unsigned char c_strip[0x100] = {
    1,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

int wstring_isempty(const wchar_t *s, int sz)
{
    const wchar_t *c = s;
    sz = ((sz < 0) ? 0 : sz);

    while(sz--)
    {
        if ((*c > 0x100) || ((*c < 0x100) && (!c_strip[*c]))) { return 1; }
        c++;
    }
    return 0;
}

string_ws wstring_trunc(const wchar_t *ws, int sz)
{
    int            osz = 0;
    const wchar_t *c   = ws,
                  *cc  = (ws + (sz - 1));
    do
    {
        while(osz < sz)
        {
            if ((*c < 0x100) && (!c_strip[*c])) { break; }
            c++; osz++;
        }
        sz -= osz; osz = 0;

        if (!sz) { break; }

        while(osz < sz)
        {
            if ((*cc < 0x100) && (!c_strip[*cc])) { break; }
            cc--; osz++;
        }
        sz -= osz;

    } while (0);

    string_ws ss = { (wchar_t*)c, sz };
    return    ss;
}

char * wstring_wstocs_alloc(const wchar_t *src)
{
    char __AUTO *p = NULL;
    char  *dst;
    size_t ssz;

    if (
        (!src)                                            ||
        ((ssz = _wcstombs(NULL, src, 0)) == 0)            ||
        ((p   = calloc(sizeof(wchar_t), (ssz + 2))) == 0) ||
        ((ssz = _wcstombs(p, src, (ssz + sizeof(char)))) == 0)
       ) { return NULL; }

    // p[ssz] = '\0';
    dst = p; p = NULL;
    return dst;
}

char * wstring_swstocs_alloc(const string_ws *src)
{
    if (!src) { return 0; }
    return wstring_wstocs_alloc(src->str);
}

wchar_t * wstring_cstows_alloc(const char *src)
{
    wchar_t __AUTO *p = NULL;
    wchar_t *dst;
    size_t   ssz;

    if (
        (!src)                                            ||
        ((ssz = _mbstowcs(NULL, src, 0)) == 0)            ||
        ((p   = calloc(sizeof(wchar_t), (ssz + 4))) == 0) ||
        ((ssz = _mbstowcs(p, src, (ssz + sizeof(wchar_t)))) == 0)
       ) { return NULL; }

    // p[ssz] = L'\0';
    dst = p; p = NULL;
    return dst;
}

size_t wstring_wstocs(char dst[], size_t dsz, const string_ws *src)
{
    size_t ssz = src->sz;
    ssz = ((!ssz) ? _wcslen(src->str) : ssz);
    dsz = ((ssz >= dsz) ? (dsz - 1) : ssz);
    if ((dsz = _wcstombs(dst, src->str, dsz)) == 0) { return 0; }
    dst[dsz] = '\0';
    return dsz;
}

size_t wstring_cstows(wchar_t dst[], size_t dsz, const char *src)
{
    size_t ssz = strlen(src);
    dsz = ((ssz >= dsz) ? (dsz - 1) : ssz);
    if ((dsz = _mbstowcs(dst, src, dsz)) == 0) { return 0; }
    dst[dsz] = L'\0';
    return dsz;
}

size_t wstring_alloc(string_ws *dst, size_t sz)
{
    if (!dst) { return 0; }
    dst->str = ((dst->str == NULL) ?
        calloc(sizeof(wchar_t), (sz + 1)) :
        realloc(dst->str, ((dst->sz + sz + 1) * sizeof(wchar_t)))
    );
    if (dst->str == NULL) { return 0; }
    return (dst->sz + sz);
}

size_t wstring_append(string_ws *dst, const wchar_t *s, size_t sz)
{
    if (
        (!s)                               ||
        (!dst)                             ||
        ((!sz) && (!(sz = _wcslen(s))))    ||
        (!wstring_alloc(dst, sz))          ||
        (!_wmemcpy((void*)(dst->str + dst->sz), (const void*)s, sz))
       ) { return 0; }

    dst->sz          += sz;
    dst->str[dst->sz] = L'\0';
    return dst->sz;
}

size_t wstring_append_cvt(string_ws *dst, const char *c, size_t sz)
{
    sz = ((!sz) ? strlen(c) : sz);
    {
        wchar_t s[(sz + 1)];
        if ((sz = wstring_cstows(s, (sz + 1), c)) <= 0) { return 0; }
        return wstring_append(dst, s, sz);
    }
}

size_t wstring_format(string_ws *dst, const wchar_t *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    size_t  ret = 0;

    do
    {
        ssize_t sz;

        if (
            (!fmt)                                       ||
            (!dst)                                       ||
            ((sz = _vswprintf(NULL, 0, fmt, ap)) <= 0)   ||
            (!wstring_alloc(dst, sz))                    ||
            (_vswprintf((void*)(dst->str + dst->sz), (sz + 1), fmt, ap) <= 0)
           ) { break; }

        dst->sz += (size_t)sz;
        ret      = dst->sz;

    } while (0);

    va_end(ap);
    return ret;
}

void wstring_free(string_ws *dst)
{
    if (
        (!dst)    ||
        (dst->str == NULL)
       ) { return; }

    free(dst->str);
    dst->str = NULL;
    dst->sz  = 0;
}
