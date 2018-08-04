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

#ifndef WCHAR2_INT_LIBC_H
#define WCHAR2_INT_LIBC_H

#if !defined(_GNU_SOURCE)
#   define _GNU_SOURCE
#endif

#if defined(HAVE_CONFIG_H)
#   include "../config.h"
#endif

#if !defined(HAVE_WCHAR_H)
#   error "<wchar.h> not defined, run ./configure again, abort.."
#endif

#if !defined(HAVE_WCTYPE_H)
#   error "<wctype.h> not defined, run ./configure again, abort.."
#endif

#include <inttypes.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>

/* Some useful macros */

#define __NELE(a) (sizeof(a) / sizeof(a[0]))

#define __MAX(a,b) ((a) > (b) ? (a) : (b))
#define __MIN(a,b) ((a) < (b) ? (a) : (b))

#define __BITBOOL(x) (!(!(x)))
#define __BITSET(arg,mask) ((arg) | (1L << (mask)))
#define __BITCLR(arg,mask) ((arg) & ~(1L << (mask)))
#define __BITTST(arg,mask) __BITBOOL((arg) & (1L << (mask)))
#define __BITFLP(arg,mask) ((arg) ^ (1L << (mask)))

#define __OOP(x) (((unsigned)(x) - 'A') > ('z' - 'A'))
#define __OOB(c,b) (((((b)>>3)-0x10)|(((b)>>3)+((int32_t)(c)>>26))) & ~7)
#define R_(a,b) ((uint32_t)(((a == 0x80) ? (0x40U - b) : -a) << 23))
#define R(a,b) R_(__WEV(a,U),__WEV(b,U))

#define __SA 0xc2u
#define __SB 0xf4u
#define __ARGMAX 127

/* Convenient bit representation for modifier flags, which all fall
 * within 31 codepoints of the space character.
 * vfprintf vfwprintf
 */

#define __ALT_FORM   (1U << ('#' - ' '))
#define __ZERO_PAD   (1U << ('0' - ' '))
#define __LEFT_ADJ   (1U << ('-' - ' '))
#define __PAD_POS    (1U << (' ' - ' '))
#define __MARK_POS   (1U << ('+' - ' '))
#define __GROUPED    (1U << ('\'' - ' '))

#define __FLAGMASK (__ALT_FORM | __ZERO_PAD | __LEFT_ADJ | __PAD_POS | __MARK_POS | __GROUPED)

#if (UINT_MAX == ULONG_MAX)
#define __LONG_IS_INT
#endif

#if ((SIZE_MAX != ULONG_MAX) || (UINTMAX_MAX != ULLONG_MAX))
#define __ODD_TYPES
#endif

#if (defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(__MINGW32__))
#   define __PSEP '\\'
#else
#   define __PSEP '/'
#endif

#if !defined(__WCHAR_INTERNAL_LIB)
extern const uint32_t bittab[];
#endif

#define __AUTO __attribute__((cleanup(__wsfree)))

#include "../include/wchar2.h"

#endif
