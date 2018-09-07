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

#ifndef WCHAR2EXT_LOCAL_H
#define WCHAR2EXT_LOCAL_H

#if defined(WCHAR2_LIBC_H) || defined(WCHAR2EXT_LIBC_H)
#   error "Only one header include, wchar2.h or wchar2ext.h"
#endif

#include "libbuild.h"

#if ((!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L)) && \
      !defined(__STDC_C99) && !defined(__C99_RESTRICT))
#   if !defined(restrict)
#      if defined(__GNUC__) || defined(__clang__)
#         define restrict __restrict
#      elif defined(_MSC_VER)
#         define restrict
#      elif defined(__SUNPRO_C)
#         define restrict _Restrict
#      else
#         define restrict
#      endif
#   endif
#   if !defined(inline)
#      if defined(__GNUC__) || defined(__clang__)
#         define inline inline __attribute__((always_inline))
#      elif defined(_MSC_VER)
#         define inline __forceinline
#      else
#         define inline
#      endif
#   endif
#endif

#if !defined(__STDC_ISO_10646__)
#   define __STDC_ISO_10646__ 201103L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <wchar.h>

#if defined(OS_WIN)

#include <stdlib.h>
#include <stdio.h>

#   define _wmemcpy wmemcpy
#   define _wcslen wcslen
#   define _wcsrchr wcsrchr
#   define _vswprintf vswprintf
#   define _wcsftime wcsftime
#   define _wcscmp wcscmp
#   define _wctomb wctomb

#   if defined(_MSC_VER)
#      define _wcstombs __wcstombs_s
#      define _mbstowcs __mbstowcs_s
#      define _mbsrtowcs __mbsrtowcs_s

#      pragma warning(disable : 4127)
#      pragma warning(disable : 4706)
#      define __AUTO(x)
#      define __attribute__(x)

#   else
#      define _wcstombs wcstombs
#      define _mbstowcs mbstowcs
#      define _wcscmp wcscmp
#      define _mbsrtowcs mbsrtowcs

#      if (defined(BUILD_MINGW32) && !defined(__CROSS_COMPILE_TIME__))
int vswprintf(wchar_t*, const wchar_t*, va_list);
#      endif

#      if defined(BUILD_MINGW)
#         define __AUTO(x) __attribute__((cleanup(x)))
#      else
#         define __AUTO(x)
#      endif

#   endif


#elif defined(__GNUC__) || defined(__clang__)

#   define _wmemcpy wmemcpy
#   define _wcslen wcslen
#   define _vswprintf vswprintf
#   define _wcstombs wcstombs
#   define _mbstowcs mbstowcs
#   define _wcsrchr wcsrchr
#   define __AUTO(x) __attribute__((cleanup(x)))

#endif

#if (defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__MINGW32__))
#   define __PSEP '\\'
#else
#   define __PSEP '/'
#endif

#define __NELE(a) (sizeof(a) / sizeof(a[0]))

#define __BITBOOL(x) (!(!(x)))
#define __BITSET(arg,mask) ((arg) | (1L << (mask)))
#define __BITCLR(arg,mask) ((arg) & ~(1L << (mask)))
#define __BITTST(arg,mask) __BITBOOL((arg) & (1L << (mask)))
#define __BITFLP(arg,mask) ((arg) ^ (1L << (mask)))

#define __ARGMAX 127
#define WCHAR2EXT_MSVC_ORIGIN 1

#include "../include/wchar2ext.h"

#if defined(OS_WIN)
#   if defined(_MSC_VER)
#      include <windows.h>
#      define __seh_except() __seh_except_(GetExceptionCode(), __LINE__, __FILE__, __FUNCTION__)
int    __seh_except_(unsigned int, unsigned int, const char*, const char*);
#   endif
#endif

#if defined(BUILD_MSVC32) || defined(BUILD_MSVC64)

static inline size_t __wcstombs_s(char *out, const wchar_t *src, size_t sz)
{
    size_t  ret;
    if (wcstombs_s(&ret, out, sz, src, (sz - 1)) != 0)
        return 0U;
    return ret;
}
static inline size_t __mbstowcs_s(wchar_t *out, const char *src, size_t sz)
{
    size_t  ret;
    if (mbstowcs_s(&ret, out, sz, src, (sz - 1)) != 0)
        return 0U;
    return ret;
}
static inline size_t __mbsrtowcs_s(wchar_t *out, const char **src, size_t sz, mbstate_t *ps)
{
    size_t  ret;
    if (mbsrtowcs_s(&ret, out, sz, src, (sz - 1), ps) != 0)
        return 0U;
    return ret;
}

#endif

#endif  /* WCHAR2EXT_LOCAL_H */
