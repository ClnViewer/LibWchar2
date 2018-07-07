
/*
  Copyright (c) 2018 PS

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
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

#define __MAX(a,b) ((a) > (b) ? (a) : (b))
#define __MIN(a,b) ((a) < (b) ? (a) : (b))

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

#if !defined(__WCHAR_INTERNAL_LIB)
extern const uint32_t bittab[];
#endif

#include "../include/wchar2.h"

#endif
