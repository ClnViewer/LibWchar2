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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <wchar.h>

#if defined(OS_WIN32) || defined(OS_WIN64) || defined(_MSC_VER)
#   define _wmemcpy wmemcpy
#   define _wcslen wcslen
#   define _wcsrchr wcsrchr
#   define _vswprintf vswprintf
#   define __AUTO

#   if defined(BUILD_MSVC32) || defined(BUILD_MSVC64)
#      define _wcstombs __wcstombs_s
#      define _mbstowcs __mbstowcs_s
#      pragma warning(disable : 4127)
#      pragma warning(disable : 4706)
#   else
#      define _wcstombs wcstombs
#      define _mbstowcs mbstowcs
#   endif

#elif defined(__GNUC__) || defined(__clang__)
#   define _wmemcpy wmemcpy
#   define _wcslen wcslen
#   define _vswprintf vswprintf
#   define _wcstombs wcstombs
#   define _mbstowcs mbstowcs
#   define _wcsrchr wcsrchr
#   define __AUTO __attribute__((cleanup(__wsfree)))
#endif

#if (defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__MINGW32__))
#   define __PSEP '\\'
#else
#   define __PSEP '/'
#endif

#define __ARGMAX 127
#define WCHAR2EXT_MSVC_ORIGIN 1

#include "../include/wchar2ext.h"

#if defined(BUILD_MSVC32) || defined(BUILD_MSVC64)

static inline size_t __wcstombs_s(char *out, const wchar_t *src, size_t sz) {
    size_t  ssz;
    if (wcstombs_s(&ssz,out,sz,src,sz) != 0) return 0U;
    return ssz;
}
static inline size_t __mbstowcs_s(wchar_t *out, const char *src, size_t sz) {
    size_t  ssz;
    if (mbstowcs_s(&ssz,out,sz,src,sz) != 0) return 0U;
    return ssz;
}

#elif defined(__GNUC__) || defined(__clang__)

static inline void __attribute__((always_inline)) __wsfree(void *v) {
    if (v) { void *x = *(void**)v; if (x) { free(x); x = ((void*)0); }}
}

#endif

#endif  /* WCHAR2EXT_LOCAL_H */
