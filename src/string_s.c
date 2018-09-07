/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
    Compatible 'char*' interface

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
const char * _strptime(const char*, const char*, struct tm*);
//#   include "strptime_w32.c"
#   define strptime _strptime

#else
#   define _XOPEN_SOURCE
#   include <stdio.h>
#   include <stdlib.h>
#   include "libwchar.h"

#endif

#include "../include/string_s.h"
#include <time.h>

const unsigned char c_strip[0x100] =
{
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

int string_isempty(const char *s, int sz)
{
    const char *c = s;
    sz = ((sz < 0) ? 0 : sz);

    if (!s)
    {
        errno = EINVAL;
        return 0;
    }

    while(sz--)
    {
        if (!c_strip[(unsigned char)*c])
        {
            return 1;
        }
        c++;
    }
    return 0;
}

string_s string_trunc(const char *s, int sz)
{
    int            osz = 0;
    const char     *c   = s,
                    *cc  = NULL;
    string_s ss = { NULL, 0U };

    do
    {
        if ((!s) || (sz <= 0))
        {
            errno = EINVAL;
            break;
        }

        cc = (s + (sz - 1));

        while(osz < sz)
        {
            if (!c_strip[(unsigned char)*c])
            {
                break;
            }
            c++;
            osz++;
        }
        sz -= osz;
        osz = 0;

        if (!sz)
        {
            break;
        }

        while(osz < sz)
        {
            if (!c_strip[(unsigned char)*cc])
            {
                break;
            }
            cc--;
            osz++;
        }
        sz -= osz;

    }
    while (0);

    ss.str = (char*)c;
    ss.sz  = (size_t)sz;
    return    ss;
}

size_t string_trunc_alloc(string_s *dst, const char *s, int sz)
{
#   if !defined(_MSC_VER)
    char __AUTO(__autofree) *p = NULL;
#   endif

    if ((!dst) || (!s))
    {
        errno = EINVAL;
        return 0U;
    }
#   if !defined(_MSC_VER)
    p = dst->str;
#   endif

    do
    {
        string_s ss = string_trunc(s, sz);
        if (
            (!ss.sz)                    ||
            (!string_alloc(dst, ss.sz)) ||
            (!memcpy((void*)(dst->str + dst->sz), (const void*)ss.str, ss.sz))
        )
        {
            break;
        }

#   if !defined(_MSC_VER)
        p = NULL;
#   endif
        return dst->sz;
    }
    while (0);

    return 0U;
}

size_t string_alloc(string_s *dst, size_t sz)
{
    char *p = NULL;

    if (!dst)
    {
        errno = EINVAL;
        return 0U;
    }
    p = ((dst->str == NULL) ?
         calloc(sizeof(char), (sz + 1U)) :
         realloc(dst->str, (dst->sz + sz + 1U))
        );
    if ((p == NULL) && (dst->str == NULL))
    {
        return 0U;
    }
    else if (p == NULL)
    {
        string_free(dst);
        return 0U;
    }
    dst->str = p;
    return (dst->sz + sz);
}

size_t string_append(string_s *dst, const char *s, size_t sz)
{
    if ((!dst) || (!s))
    {
        errno = EINVAL;
        return 0U;
    }

    if (
        ((!sz) && (!(sz = strlen(s))))    ||
        (!string_alloc(dst, sz))         ||
        (!memcpy((void*)(dst->str + dst->sz), (const void*)s, sz))
    )
    {
        return 0U;
    }

    dst->sz          += sz;
    dst->str[dst->sz] = '\0';
    return sz;
}

size_t string_appends_(string_s *dst, ...)
{
    size_t   i, sz  = 0U, cnt = 0U;
    char *s;
#   if defined(_MSC_VER)
    va_list ap;
#   else
    va_list ap, ap2;
#   endif

    if (!dst)
    {
        errno = EINVAL;
        return 0U;
    }

    do
    {
#       if defined(_MSC_VER)
        string_s sarr[__ARGMAX] = {0};
        va_start(ap, dst);
#       else
        va_start(ap, dst);
        va_copy(ap2, ap);

        while ((s = va_arg(ap2, char*)) != NULL)
        {
            cnt++;
        }
        va_end(ap2);

        if (!cnt)
        {
            va_end(ap);
            return 0U;
        }

        string_s sarr[cnt];
        cnt = 0U;
#       endif

        while ((s = va_arg(ap, char*)) != NULL)
        {
            sarr[cnt].str = s;
            sarr[cnt].sz  = strlen(s);
            sz += sarr[cnt++].sz;
        }
        va_end(ap);

        if (
            (!sz)                  ||
            (!string_alloc(dst, sz))
        )
        {
            break;
        }

#       if defined(_MSC_VER)
        for (i = 0U; i < cnt; i++)
#       else
        for (i = 0U; i < __NELE(sarr); i++)
#       endif
        {
            if (sarr[i].str == NULL)
                break;
            (void) memcpy((void*)(dst->str + dst->sz), (const void*)sarr[i].str, sarr[i].sz);
            dst->sz += sarr[i].sz;
        }

        dst->str[dst->sz] = '\0';
        return sz;

    }
    while (0);

    string_free(dst);
    return 0U;
}

size_t string_format(string_s *dst, const char *fmt, ...)
{
    size_t ret = 0U;
    va_list ap;

    if ((!dst) || (!fmt))
    {
        errno = EINVAL;
        return 0U;
    }

    va_start(ap, fmt);

    do
    {
        int sz;
        dst->sz  = 0U;

        if (dst->str)
        {
            free(dst->str);
        }
        if (
#           if defined(_MSC_VER)
            // cppcheck-suppress nullPointer
            ((sz = vsnprintf_s(NULL, 0U, 0U, fmt, ap)) <= 0)  ||
#           else
            // cppcheck-suppress nullPointer
            ((sz = vsnprintf(NULL, 0U, fmt, ap)) <= 0)  ||
#           endif
            (!string_alloc(dst, (size_t)sz))            ||
#           if defined(_MSC_VER)
            ((sz = vsnprintf_s(dst->str, (size_t)(sz + 1), sz, fmt, ap)) <= 0)
#           else
            ((sz = vsnprintf(dst->str, (size_t)(sz + 1), fmt, ap)) <= 0)
#           endif
        )
        {
            break;
        }

        dst->sz  = (size_t)sz;
        ret = dst->sz;
    }
    while (0);

    va_end(ap);
    return ret;
}

char * string_timeformat(const char *src, size_t sz, const char *fmtin, const char *fmtout)
{
#   define __TMF_OUT_SIZE 250

    char __AUTO(__autofree) *p = NULL, *s = NULL;

    if (
        (!src)    ||
        (!fmtin)  ||
        (!fmtout) ||
        (!(sz = ((!sz) ? strlen(src) : sz)))
    )
    {
        errno = EINVAL;
        return NULL;
    }

    do
    {
#       if defined(_MSC_VER)
        __try
        {
#       endif
            size_t  osz;
            char   *out;
            struct  tm tms;

            if (
                ((p = calloc(sizeof(char), __TMF_OUT_SIZE)) == NULL) ||
                ((s = calloc(sizeof(char), (sz + 1))) == NULL)       ||
                (memcpy(s, src, sz) == NULL)
            )
            {
                break;
            }

            s[sz] = '\0';

            if (
                (strptime(s, fmtin, &tms) != NULL) ||
                (!(osz = strftime(p, __TMF_OUT_SIZE, fmtout, &tms)))
            )
            {
                break;
            }

            if (!(out = realloc(p, (osz + 1U))))
            {
                break;
            }

            out[osz] = '\0';
            p = NULL;

            return out;

#       if defined(_MSC_VER)
        }
        __finally
        {
            if (s != NULL)
            {
                free(s);
                s = NULL;
            }
        }
#       endif

    }
    while (0);

#   if defined(_MSC_VER)
    if (p != NULL)
        free(p);
#   endif
    return NULL;
}

char * string_timeformat_s(const string_s *src, const char *fmtin, const char *fmtout)
{
    if (!src)
    {
        errno = EINVAL;
        return NULL;
    }
    return string_timeformat(src->str, src->sz, fmtin, fmtout);
}

long string_split_cb(const string_s *src, char s, csplit_cb fun, void *data)
{
    long ret = 0L;
    char   *c, *cc;
    size_t  i, n, ssz;

    if (
        (!fun)       ||
        (!src)       ||
        (!src->str)  ||
        (!(ssz = ((!src->sz) ? strlen(src->str) : src->sz)))
    )
    {
        errno = EINVAL;
        return ret;
    }

    for (i = 0, n = 0, cc = (char*)src->str; i < ssz; i++)
    {
        if (cc[i] == s)
        {
            size_t sz;
            if (!n)
            {
                sz  = i;
                c   = (char*)src->str;
                n   = (i + 1);
            }
            else
            {
                sz  = (i - n);
                c   = ((char*)src->str + n);
                n   = (i + 1);
            }
            fun(c, sz, ++ret, data);
        }
    }
    if (n < i)
        fun((cc + n), (ssz - n), ++ret, data);

    return ret;
}

void string_free(string_s *dst)
{
    if (!dst)
    {
        return;
    }
    if (dst->str != NULL)
    {
        free(dst->str);
    }

    dst->str = NULL;
    dst->sz  = 0UL;
}
