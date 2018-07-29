
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

#include <stdlib.h>

#if defined(_MSC_VER)

#   define __MACRO_WCHAR_TRY                                                     \
    char *b = NULL;                                                              \
    __try                                                                        \
    {                                                                            \
        if ((b = calloc(1, ((ssz + 2) * sizeof(wchar_t)))) == NULL)              \
            break;

#   define __MACRO_WCHAR_FIN                                                     \
    }                                                                            \
    __finally                                                                    \
    {                                                                            \
        if (b != NULL)                                                           \
            free(b);                                                             \
    }

#else

#   define __MACRO_WCHAR_TRY                                                     \
    char    b[((ssz + 2) * sizeof(wchar_t))];

#   define __MACRO_WCHAR_FIN

#endif

#   define __MACRO_WCHAR_BEGIN                                                   \
        char *cret = NULL;                                                       \
        size_t ssz, rsz;                                                         \
        errno = 0;                                                               \
                                                                                 \
        if (                                                                     \
            (!ws) ||                                                             \
            (!(ssz = _wcslen(ws)))                                               \
           )                                                                     \
        {                                                                        \
            errno = EINVAL;                                                      \
            return out;                                                          \
        }


#   define __MACRO_WCHAR_CVT                                                     \
        if (!wstring_wstocs(b, ((ssz + 1) * sizeof(wchar_t)), ws, ssz))          \
           { break; }                                                            \


#   define __MACRO_WCHAR_END                                                     \
        if (                                                                     \
            (wo)           &&                                                    \
            (cret != NULL) &&                                                    \
            ((rsz = strlen(cret)))                                               \
           )                                                                     \
        {                                                                        \
            *wo  = (wchar_t*)ws;                                                 \
            *wo += (ssz - rsz);                                                  \
        }                                                                        \
        else if (wo)                                                             \
        {                                                                        \
            *wo = NULL;                                                          \
        }


#define __MACRO_WCHAR_TO_NUM2(_T,_N)                                             \
    _T __WEV(_wcsto,_N)(const wchar_t *ws, wchar_t **wo)                         \
    {                                                                            \
        _T out = 0;                                                              \
        __MACRO_WCHAR_BEGIN                                                      \
        do                                                                       \
        {                                                                        \
            __MACRO_WCHAR_TRY                                                    \
            __MACRO_WCHAR_CVT                                                    \
            out = __WEV(strto,_N)(b, &cret);                                     \
            __MACRO_WCHAR_END                                                    \
            return out;                                                          \
            __MACRO_WCHAR_FIN                                                    \
        }                                                                        \
        while (0);                                                               \
        return (_T)0;                                                            \
    }

#define __MACRO_WCHAR_TO_NUM3(_T,_N)                                             \
    _T __WEV(_wcsto,_N)(const wchar_t *ws, wchar_t **wo, int bs)                 \
    {                                                                            \
        _T out = 0;                                                              \
        __MACRO_WCHAR_BEGIN                                                      \
        do                                                                       \
        {                                                                        \
            __MACRO_WCHAR_TRY                                                    \
            __MACRO_WCHAR_CVT                                                    \
            out = __WEV(strto,_N)(b, &cret, bs);                                 \
            __MACRO_WCHAR_END                                                    \
            return out;                                                          \
            __MACRO_WCHAR_FIN                                                    \
        }                                                                        \
        while (0);                                                               \
        return (_T)0;                                                            \
    }

__MACRO_WCHAR_TO_NUM2(double, d)
__MACRO_WCHAR_TO_NUM2(float, f)
__MACRO_WCHAR_TO_NUM2(long double, ld)

__MACRO_WCHAR_TO_NUM3(long int, l)
__MACRO_WCHAR_TO_NUM3(long long int, ll)
__MACRO_WCHAR_TO_NUM3(unsigned long int, ul)
__MACRO_WCHAR_TO_NUM3(unsigned long long int, ull)
__MACRO_WCHAR_TO_NUM3(intmax_t, imax)
__MACRO_WCHAR_TO_NUM3(uintmax_t, umax)

