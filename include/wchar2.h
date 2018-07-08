
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


/**
  * @file wchar2.h
  * @mainpage LibWchar2
  * @brief This library design to use wchar_t == 2, Windows software compatible.
  *
  * Compile this library and you programm use:
  *  - gcc as key:   -fshort-wchar
  *  - clang as key: -fwchar-type=short -fno-signed-wchar
  *
  * @copyright  MIT 2018 (c) PS
  */

  /*
    Missing curent, TODO ?:
        wcscoll  Locale-specific wide-character string compare
        wcscpy   Copy wide-character string
        wcscspn  Count wide characters not in string
        wcsftime Convert date and time to a formatted wide-character string
        wcsxfrm  Locale-specific wide-character string transformation
   */

#ifndef WCHAR2_LIBC_H
#define WCHAR2_LIBC_H

#include <wctype.h>
#include <wchar.h>

#if !defined(__SIZEOF_WCHAR_T__)
#  error "'__SIZEOF_WCHAR_T__' NOT defined, system not supported"
#endif

#if defined(__SIZEOF_WCHAR_T__) && (__SIZEOF_WCHAR_T__ != 2)
#  error "size of 'wchar_t' != '2'; Use gcc key: '-fshort-wchar', or clang key: '-fwchar-type=short' '-fno-signed-wchar'"
#endif

/**
 * \htmlonly
 */

#define __WEV_(A,B) A ## B
#define __WEV(A,B)  __WEV_(A,B)
#define __WEVFA_(_11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N
#define __WEVFA(...) __WEVFA_(__VA_ARGS__, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define __WS_(x) L##x
#define __WS(x) __WS_(x)

#define __WSTR wchar_t
#define __WSTR_FMT  "ls"
#define __WCHAR_FMT "lc"

#define __WCSZ(x) (x->sz * sizeof(wchar_t) + 1)

#if ((!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L)) && \
      !defined(__STDC_C99) && !defined(__C99_RESTRICT))
#   if !defined(restrict)
#      if defined(__GNUC__) || defined(__clang__) || defined(_MSC_VER)
#         define restrict __restrict
#      elif defined(__SUNPRO_C)
#         define restrict _Restrict
#      else
#         define restrict
#      endif
#   endif
#endif

/**
 * \endhtmlonly
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Base wide string structure */
typedef struct __wchar_string_ws_ {
    wchar_t *str; /** wide string pointer */
    size_t   sz;  /** size wide string */

} string_ws;

          /** @brief Translate wide characters to uppercase */
wchar_t   _towupper(wchar_t);
          /** @brief Translate wide characters to lowercase */
wchar_t   _towlower(wchar_t);
          /** @brief Extensible wide-character translation */
wchar_t   _towctrans(wchar_t, wctrans_t);
          /** @brief Compute wide-character test type */
wctype_t  _wctype(const char*);
          /** @brief Compute wide-character translation type */
wctrans_t _wctrans(const char*);

          /** @brief Number of column positions of a wide-character code */
int       _wcwidth(wchar_t);
          /** @brief Number of column positions of a wide-character string */
int       _wcswidth(const wchar_t*, size_t);
          /** @brief Extensible wide-character test */
int       _iswctype(wchar_t, wctype_t);
          /** @brief Hexadecimal digit wide character predicate */
int       _iswxdigit(wchar_t);
          /** @brief Uppercase wide character predicate */
int       _iswupper(wchar_t);
          /** @brief Whitespace wide character predicate */
int       _iswspace(wchar_t);
          /** @brief Punctuation wide character predicate */
int       _iswpunct(wchar_t);
          /** @brief Printable wide character predicate */
int       _iswprint(wchar_t);
          /** @brief Lowercase wide character predicate */
int       _iswlower(wchar_t);
          /** @brief Graphic wide character predicate */
int       _iswgraph(wchar_t);
          /** @brief Decimal digit wide character predicate */
int       _iswdigit(wchar_t);
          /** @brief Control wide character predicate */
int       _iswcntrl(wchar_t);
          /** @brief Blank wide character predicate */
int       _iswblank(wchar_t);
          /** @brief Alphabetic wide character predicate */
int       _iswalpha(wchar_t);
          /** @brief Alphanumeric wide character predicate */
int       _iswalnum(wchar_t);

          /** @brief Minimal wide string to multibyte string converter */
size_t    _wcstombs(char *restrict, const wchar_t *restrict, size_t);
          /** @brief Minimal wide string to multibyte string converter + double size out buffer */
size_t    _wcstombs_s(char *restrict, const wchar_t *restrict, size_t);
          /** @brief Convert a wide-character string to a character string */
size_t    _wcsrtombs(char *restrict, const wchar_t **restrict, size_t, mbstate_t *restrict);
          /** @brief Convert wide character to multibyte sequence */
size_t    _wcrtomb(char *restrict, wchar_t, mbstate_t *restrict);
          /** @brief Minimal multibyte string to wide string converter */
size_t    _mbstowcs(wchar_t *restrict, const char *restrict, size_t);
          /** @brief Convert a character string to a wide-character string */
size_t    _mbsrtowcs(wchar_t *restrict, const char **restrict, size_t, mbstate_t *restrict);
          /** @brief Convert a wide-character string to a character string */
size_t    _wcsnrtombs(char *restrict, const wchar_t **restrict, size_t, size_t, mbstate_t *restrict);
          /** @brief Convert a character string to a wide-character string */
size_t    _mbsnrtowcs(wchar_t *restrict, const char **restrict, size_t, size_t, mbstate_t *restrict);
          /** @brief Converts a narrow multibyte character to a wide character */
size_t    _mbrtowc(wchar_t *restrict, const char *restrict src, size_t, mbstate_t *restrict);
          /** @brief Get length of multibyte character */
size_t    _mbrlen(const char *restrict, size_t, mbstate_t *restrict);
          /** @brief Determines the size, in bytes, of the multibyte character whose first byte is pointed */
int       _mblen(const char*, size_t);
          /** @brief Check if initial conversion state */
int       _mbsinit(const mbstate_t*);
          /** @brief Minimal multibyte to wide char converter */
int       _mbtowc(wchar_t *restrict, const char *restrict, size_t);
          /** @brief Minimal wide char to multibyte converter */
int       _wctomb(char*, wchar_t);
          /** @brief Convert wide character to single byte */
int       _wctob(wchar_t);
          /** @brief Convert single byte character to wide character */
wchar_t   _btowc(int);

/** Other non standart function */

 /**
  * @brief wchar_t* print
  * Test variably only!
  * Instead use _vfprintf, _vfwprintf, _fprintf, _fwprintf
  *
  */
void       wcprint(wchar_t*);

 /**
  * @brief compare char* <->  wchar_t*
  * ASCII only!
  * size_t   - wchar_t* size
  *
  */
int        wcstocscmp(const char*, wchar_t*, size_t); // ASCII mode only

 /**
  *    Original name: aov-rx - Angel Ortega's regular expression library
  *    Copyright (C) 2011/2012 Angel Ortega <angel@triptico.com>
  *    https://github.com/angelortega/aov-rx or http://triptico.com
  *
  * @brief wcsregexp - Matches a regular expression
  * @rx: the regular expression
  * @tx: the text to be matched
  * @size: a pointer to integer where the matching lenght is stored
  *
  * Matches the string @tx for the regular expression in @rx.
  * On output, the integer pointer by @size will contain the number
  * of matched characters (with 0 meaning that no matching was
  * possible). If the end of string mark ($) is used in the regular
  * expression and a match is effective, the ending zero is included
  * in the match.
  *
  * Returns the address of the match.
  */
wchar_t *  wcsregexp(wchar_t *restrict, wchar_t *restrict, int*);

 /**
  *  @brief Covert utf-8 char* to wchar_t*
  *  wchar_t*          - output
  *  const char*       - input
  *  return size_t     - size
  */
size_t     u8stowcs(wchar_t*, const char*);

 /**
  *  @brief Convert wchar_t* to utf-8 char*
  *  char*             - output
  *  const wchar_t*    - input
  *  return size_t     - size
  */
size_t     wcstou8s(char*, const wchar_t*);

 /**
  *  @brief Verify char* to utf-8 valid string
  *  const char* - input
  *  int (bool)  - output
  */
int        u8sverify(const char*);

          /** @brief Copy a wide-character string returning a pointer to its end */
wchar_t * _wcpcpy(wchar_t*, const wchar_t*);
          /** @brief Copy part of a wide-character string returning a pointer to its end */
wchar_t * _wcpncpy(wchar_t*, const wchar_t*, size_t);
          /** @brief Concatenate wide-character strings */
wchar_t * _wcscat(wchar_t*, const wchar_t*);
          /** @brief Concatenate wide-character strings */
wchar_t * _wcsncat(wchar_t*, const wchar_t*, size_t);
          /** @brief Counted copy wide-character string */
wchar_t * _wcsncpy(wchar_t*, const wchar_t*, size_t);
          /** @brief Find wide characters in string */
wchar_t * _wcspbrk(const wchar_t*, const wchar_t*);
          /** @brief Search for wide character in string */
wchar_t * _wcschr(const wchar_t*, wchar_t);
          /** @brief Reverse search for wide character in string */
wchar_t * _wcsrchr(const wchar_t*, wchar_t);
          /** @brief Find wide-character string segment */
wchar_t * _wcsstr(const wchar_t*, const wchar_t*);
          /** @brief Tokenize wide-character string */
wchar_t * _wcstok(wchar_t*, const wchar_t*, wchar_t**);
          /** @brief Find wide character in memory */
wchar_t * _wmemchr(const wchar_t*, wchar_t, size_t);
          /** @brief Copy wide characters in memory */
wchar_t * _wmemcpy(wchar_t*, const wchar_t*, size_t);
          /** @brief Copy wide characters in memory with overlapping areas */
wchar_t * _wmemmove(wchar_t*, const wchar_t*, size_t);
          /** @brief Set wide characters in memory */
wchar_t * _wmemset(wchar_t*, wchar_t, size_t);

          /** @brief Concatenate wide-character strings to specified length */
size_t    _wcslcat(wchar_t*, const wchar_t*, size_t);
          /** @brief Copy wide-character string to specified length */
size_t    _wcslcpy(wchar_t*, const wchar_t*, size_t);
          /** @brief Wide-character string length */
size_t    _wcslen(const wchar_t*);
          /** @brief Wide-character string length with maximum limit */
size_t    _wcsnlen(const wchar_t*, size_t);
          /** @brief Find initial match in wide-character string */
size_t    _wcsspn(const wchar_t*, const wchar_t*);

          /** @brief Case-insensitive wide character string compare */
int       _wcscasecmp(const wchar_t*, const wchar_t*);
          /** @brief Case-insensitive wide character string compare with size */
int       _wcsncasecmp(const wchar_t*, const wchar_t*, size_t);
          /** @brief Wide-character string compare */
int       _wcscmp(const wchar_t*, const wchar_t*);
          /** @brief Wide-character string compare */
int       _wcsncmp(const wchar_t*, const wchar_t*, size_t);
          /** @brief Compare wide characters in memory */
int       _wmemcmp(const wchar_t*, const wchar_t*, size_t);

          /** @brief Write to stream char format variable argument list */
size_t    _vfprintf(FILE *restrict, const char *restrict, va_list)
                __attribute__((__nonnull__, __format__(__printf__, 2, 0)));

          /** @brief Write formatted data from variable argument list to sized buffer */
size_t    _vsnprintf(char *restrict, size_t, const char *restrict, va_list)
                __attribute__((__format__(__printf__, 3, 0)));

          /** @brief Write to stream char format variable arguments */
size_t    _fprintf(FILE *restrict, const char *restrict, ...)
                __attribute__((__nonnull__, __format__(__printf__, 2, 0)));

          /** @brief Format variable arguments list */
size_t    _snprintf(char *restrict, size_t, const char *restrict, ...)
                __attribute__((__format__(__printf__, 3, 0)));

          /** @brief Write to stream wide character format variable argument list */
size_t    _vfwprintf(FILE *restrict, const wchar_t *restrict, va_list)
                /* __attribute__((__nonnull__, __format__(__wprintf__, 2, 0))) */ ;

          /** @brief Write formatted data from variable argument list to sized buffer */
size_t    _vswprintf(wchar_t *restrict, size_t, const wchar_t *restrict, va_list ap)
                /* __attribute__((__format__(__wprintf__, 3, 0))) */ ;

          /** @brief Write to stream wide character format variable arguments */
size_t    _fwprintf(FILE *restrict, const wchar_t *restrict, ...)
                /* __attribute__((__nonnull__, __format__(__wprintf__, 2, 0))) */ ;

          /** @brief Write formatted wide character output */
size_t    _swprintf(wchar_t *restrict, size_t, const wchar_t *restrict, ...)
                /* __attribute__((__format__(__wprintf__, 3, 0))) */ ;

size_t    _wprintf(const wchar_t *restrict fmt, ...)
                /* __attribute__((__format__(__wprintf__, 1, 0))) */ ;

          /** @brief Write a wide character string to a file or stream */
int       _fputws(const wchar_t *restrict, FILE *restrict);
          /** @brief Write a wide character to a file or stream */
wchar_t   _fputwc(wchar_t, FILE *restrict);

          /** @brief Open file stream, accepts file name as wide characters, mode as const char */
FILE    * _wfopen(const wchar_t*, const char*);
          /** @brief Same as wfopen, include size file name variable */
FILE    * _wfopen_s(const wchar_t*, size_t, const char*);
          /** @brief Same as wfopen, file name as structure string_ws */
FILE    * _wfopen_ws(const string_ws*, const char*);
          /** @brief Automatic type selector for wfopen* functions */
FILE    * _wfopen_selector(int, const void*, size_t, const void*);
          /** @brief Open file stream, convert file name from wide characters to UTF-8, mode as const char */
FILE    * u8wfopen(const wchar_t*, const char*);

          /** @brief Statistic from file, wide char input */
int       _wstat(const wchar_t*, struct stat*);
          /** @brief Statistic from file, wide char input with size */
int       _wstat_s(const wchar_t*, size_t, struct stat*);
          /** @brief Statistic from file, struct string_ws input */
int       _wstat_ws(const string_ws*, struct stat*);
          /** @brief Automatic type selector for wstat* functions */
int       _wstat_selector(int, const void*, size_t, const void*);
          /** @brief Statistic from file, convert file name from wide characters to UTF-8 */
int       u8wstat(const wchar_t*, struct stat*);

          /** @brief Rename file, wide char input */
int       _wrename(const wchar_t*, const wchar_t*);
          /** @brief Rename file, wide char input with size */
int       _wrename_s(const wchar_t*, size_t, const wchar_t*, size_t);
          /** @brief Rename file, struct string_ws input */
int       _wrename_ws(const string_ws*, const string_ws*);
          /** @brief Automatic type selector for wrename* functions */
int       _wrename_selector(int, const void*, size_t, const void*, size_t);
          /** @brief Rename file, convert file name from wide characters to UTF-8 */
int       u8wrename(const wchar_t*, const wchar_t*);

          /** @brief Delete (remove) file, wide char input */
int       _wremove(const wchar_t*);
          /** @brief Delete (remove) file, wide char input with size */
int       _wremove_s(const wchar_t*, size_t);
          /** @brief Delete (remove) file, struct string_ws input */
int       _wremove_ws(const string_ws*);
          /** @brief Automatic type selector for wremove* functions */
int       _wremove_selector(int, const void*, size_t);
          /** @brief Delete (remove) file, convert file name from wide characters to UTF-8 */
int       u8wremove(const wchar_t*);

          /** @brief Make directory, wide char input */
int       _wmkdir(const wchar_t*, mode_t);
          /** @brief Make directory, wide char input with size */
int       _wmkdir_s(const wchar_t*, size_t, mode_t);
          /** @brief Make directory, struct string_ws input */
int       _wmkdir_ws(const string_ws*, mode_t);
          /** @brief Automatic type selector for wmkdir* functions */
int       _wmkdir_selector(int, const void*, size_t, mode_t);
          /** @brief Make directory, convert file name from wide characters to UTF-8 */
int       u8wmkdir(const wchar_t*, mode_t);

          /** @brief Parse path file name, wide char input */
wchar_t * _wbasename(const wchar_t*);
          /** @brief Parse path file name, wide char input with size, realy size not used, compatible only */
wchar_t * _wbasename_s(const wchar_t*, size_t __attribute__((__unused__)));
          /** @brief Parse path file name, struct string_ws input */
wchar_t * _wbasename_ws(const string_ws*);
          /** @brief Automatic type selector for wbasename* functions */
wchar_t * _wbasename_selector(int, const void*, size_t);

          /** @brief Parse path extension, wide char input */
wchar_t * _wbaseext(const wchar_t*);
          /** @brief Parse path extension, wide char input with size, realy size not used, compatible only */
wchar_t * _wbaseext_s(const wchar_t*, size_t __attribute__((__unused__)));
          /** @brief Parse path extension, struct string_ws input */
wchar_t * _wbaseext_ws(const string_ws*);
          /** @brief Automatic type selector for wbaseext* functions */
wchar_t * _wbaseext_selector(int, const void*, size_t);


#ifdef __cplusplus
    }
#endif

/**
 * \htmlonly
 */

/** Other non standart macro */

#if defined(__clang__)
#   pragma clang diagnostic ignored "-Wlanguage-extension-token"
#endif

 /** @brief auto check type macro */
#define __wchar_type_id(A)                                           \
       __builtin_types_compatible_p(typeof(A),         wchar_t*) * 1 \
    +  __builtin_types_compatible_p(typeof(A),   const wchar_t*) * 1 \
    +  __builtin_types_compatible_p(typeof(A),        wchar_t[]) * 1 \
    +  __builtin_types_compatible_p(typeof(A),  const wchar_t[]) * 1 \
    +  __builtin_types_compatible_p(typeof(A),       string_ws*) * 2 \
    +  __builtin_types_compatible_p(typeof(A), const string_ws*) * 2 \
    +  __builtin_types_compatible_p(typeof(A),            char*) * 3 \
    +  __builtin_types_compatible_p(typeof(A),      const char*) * 3 \
    +  __builtin_types_compatible_p(typeof(A),           char[]) * 3 \
    +  __builtin_types_compatible_p(typeof(A),     const char[]) * 3

#   define EV_FOPEN_ARG_3(_1,_2,_3) _wfopen_selector(4,_1,_3,_2)
#   define EV_FOPEN_ARG_2(_1,_2) _wfopen_selector(__wchar_type_id(_1),_1,0,_2)
#   define EV_FOPEN_ARG_1(_1) _wfopen_selector(__wchar_type_id(_1),_1,0,(const char*)&"r")
#   define EV_FOPEN_ARG_0(...)

#   define _wfopen_macro(...) \
        __WEV(EV_FOPEN_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_MKDIR_ARG_3(_1,_2,_3) _wmkdir_selector(4,_1,_3,_2)
#   define EV_MKDIR_ARG_2(_1,_2) _wmkdir_selector(__wchar_type_id(_1),_1,0,_2)
#   define EV_MKDIR_ARG_1(_1) _wmkdir_selector(__wchar_type_id(_1),_1,0,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#   define EV_MKDIR_ARG_0(...)

#   define _wmkdir_macro(...) \
        __WEV(EV_MKDIR_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_REMOVE_ARG_2(_1,_2) _wremove_selector(__wchar_type_id(_1),_1,_2)
#   define EV_REMOVE_ARG_1(_1) _wremove_selector(__wchar_type_id(_1),_1,0)
#   define EV_REMOVE_ARG_0(...)

#   define _wremove_macro(...) \
        __WEV(EV_REMOVE_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_RENAME_ARG_4(_1,_2,_3,_4) _wrename_selector(4,_1,_2,_3,_4)
#   define EV_RENAME_ARG_3(_1,_2,_3) _wrename_selector(__wchar_type_id(_1),_1,0,_2,0)
#   define EV_RENAME_ARG_2(_1,_2) _wrename_selector(__wchar_type_id(_1),_1,0,_2,0)
#   define EV_RENAME_ARG_1(_1)
#   define EV_RENAME_ARG_0(...)

#   define _wrename_macro(...) \
        __WEV(EV_RENAME_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_STAT_ARG_3(_1,_2,_3) _wstat_selector(4,_1,_3,_2)
#   define EV_STAT_ARG_2(_1,_2) _wstat_selector(__wchar_type_id(_1),_1,0,_2)
#   define EV_STAT_ARG_1(_1) _wstat_selector(__wchar_type_id(_1),_1,0,NULL)
#   define EV_STAT_ARG_0(...)

#   define _wstat_macro(...) \
        __WEV(EV_STAT_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_BNAME_ARG_3(_1,_2,_3) _wbasename_selector(4,_1,_3,_2)
#   define EV_BNAME_ARG_2(_1,_2) _wbasename_selector(__wchar_type_id(_1),_1,0,_2)
#   define EV_BNAME_ARG_1(_1) _wbasename_selector(__wchar_type_id(_1),_1,0,NULL)
#   define EV_BNAME_ARG_0(...)

#   define _wbasename_macro(...) \
        __WEV(EV_BNAME_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_BEXT_ARG_3(_1,_2,_3) _wbaseext_selector(4,_1,_3,_2)
#   define EV_BEXT_ARG_2(_1,_2) _wbaseext_selector(__wchar_type_id(_1),_1,0,_2)
#   define EV_BEXT_ARG_1(_1) _wbaseext_selector(__wchar_type_id(_1),_1,0,NULL)
#   define EV_BEXT_ARG_0(...)

#   define _wbaseext_macro(...) \
        __WEV(EV_BEXT_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

/**
 * \endhtmlonly
 */

 /**
   * @note Macro as convert type wchar_t to char
   * @See  wchar2.h
   *
   *
  */

 /**
  * @brief wchar_t* type to char[]
  * A char[]   - array name
  * B wchar_t* - source
  * D          - function return value if error
  */
#define wstocscvt(A,B,D)                                                                                           \
    size_t __WEV(sz,__LINE__); errno = 0;                                                                          \
    if ((__WEV(sz,__LINE__) = _wcsrtombs(NULL, &(const wchar_t*){B}, 0, 0)) <= 0) {                                \
        errno = EILSEQ; return D;                                                                                  \
    }                                                                                                              \
    char __WEV(A,__LINE__)[(__WEV(sz,__LINE__) + 1)], * A = (char*)&__WEV(A,__LINE__);                             \
    if ((__WEV(sz,__LINE__) = _wcsrtombs(__WEV(A,__LINE__), &(const wchar_t*){B}, (__WEV(sz,__LINE__) + 1), 0))) { \
        __WEV(A,__LINE__)[(__WEV(sz,__LINE__))] = '\0';                                                            \
    }

 /**
  * @brief wchar_t* type to char[] with size
  * A char[]   - array name
  * B wchar_t* - source
  * C size_t   - wchar_t* size
  * D          - function return value if error
  */
#define wstocsncvt(A,B,C,D)                                                                                         \
    char __WEV(A,__LINE__)[(C * 2 + 1)], * A = (char*)&__WEV(A,__LINE__); errno = 0;                                \
    if (((C) = _wcsrtombs(__WEV(A,__LINE__), &(const wchar_t*){B}, (C * 2 + 1), 0)) <= 0) {                         \
        errno = EILSEQ; return D;                                                                                   \
    }                                                                                                               \
    __WEV(A,__LINE__)[(C)] = '\0'

 /**
  * @brief string_ws type to char[]
  * this struct defined on top of this file
  * A char[]     - array name
  * B string_ws* - source
  * D            - function return value if error
  */
#define wstrtocscvt(A,B,D)                                                                                          \
    size_t __WEV(sz,__LINE__); errno = 0;                                                                           \
    char __WEV(A,__LINE__)[(B->sz * 2 + 1)], * A = (char*)&__WEV(A,__LINE__);                                       \
    if ((__WEV(sz,__LINE__) = _wcsrtombs(__WEV(A,__LINE__), &(const wchar_t*){B->str}, (B->sz * 2 + 1), 0)) <= 0) { \
        errno = EILSEQ; return D;                                                                                   \
    }                                                                                                               \
    __WEV(A,__LINE__)[__WEV(sz,__LINE__)] = '\0'

/** Redefined 'symbols' libc functions */

/** for osx Darwin
 *  macro redefined: /usr/include/secure/_stdio.h
 *    vsnprintf, snprintf, vsnprintf, snprintf
 */

#if defined(vsnprintf)
#   undef vsnprintf
#endif

#if defined(snprintf)
#   undef snprintf
#endif

#if defined(vsnprintf)
#   undef vsnprintf
#endif

#if defined(snprintf)
#   undef snprintf
#endif

#if defined(WS_FS_REDEFINE)
#      define fputc _fputwc
#      define fputs _fputws
#   if defined(WS_FS_UTF8)
#      define mkdir u8wmkdir
#      define remove u8wremove
#      define rename u8wrename
#      define stat u8wstat
#      define fopen u8wfopen
#   else
#      define mkdir _wmkdir_macro
#      define remove _wremove_macro
#      define rename _wrename_macro
#      define stat _wstat_macro
#      define fopen _wfopen_macro
#      define basename _wbasename_macro
#   endif
#endif

/**
 * \htmlonly
 */

#define wmkdir _wmkdir_macro
#define wmkdir_w _wmkdir
#define wmkdir_s _wmkdir_s
#define wmkdir_ws _wmkdir_ws

#define wremove _wremove_macro
#define wremove_w _wremove
#define wremove_s _wremove_s
#define wremove_ws _wremove_ws

#define wrename _wrename_macro
#define wrename_w _wrename
#define wrename_s _wrename_s
#define wrename_ws _wrename_ws

#define wstat _wstat_macro
#define wstat_w _wstat
#define wstat_s _wstat_s
#define wstat_ws _wstat_ws

#define wfopen _wfopen_macro
#define wfopen_w _wfopen
#define wfopen_s _wfopen_s
#define wfopen_ws _wfopen_ws

#define wbasename _wbasename_macro
#define wbasename_w _wbasename
#define wbasename_s _wbasename_s
#define wbasename_ws _wbasename_ws

#define wbaseext _wbaseext_macro
#define wbaseext_w _wbaseext
#define wbaseext_s _wbaseext_s
#define wbaseext_ws _wbaseext_ws

#define fputwc _fputwc
#define fputws _fputws
#define vfprintf _vfprintf
#define vsnprintf _vsnprintf
#define fprintf _fprintf
#define snprintf _snprintf
#define vfwprintf _vfwprintf
#define vswprintf _vswprintf
#define fwprintf _fwprintf
#define swprintf _swprintf
#define wprintf _wprintf
#define fprintf _fprintf

/** Tests compability only */
#define _wcprint wcprint
#define _wcsregexp wcsregexp
#define _wcstocscmp wcstocscmp
#define _u8stowcs u8stowcs
#define _wcstou8s wcstou8s
#define _u8wfopen u8wfopen
#define _u8wmkdir u8wmkdir
#define _u8wremove u8wremove
#define _u8wrename u8wrename
#define _u8wstat u8wstat
#define _u8sverify u8sverify

#define towupper _towupper
#define towlower _towlower
#define towctrans _towctrans
#define wctype _wctype
#define wctrans _wctrans
#define wcwidth _wcwidth
#define wcswidth _wcswidth
#define iswctype _iswctype
#define iswxdigit _iswxdigit
#define iswupper _iswupper
#define iswspace _iswspace
#define iswpunct _iswpunct
#define iswprint _iswprint
#define iswlower _iswlower
#define iswgraph _iswgraph
#define iswdigit _iswdigit
#define iswcntrl _iswcntrl
#define iswblank _iswblank
#define iswalpha _iswalpha
#define iswalnum _iswalnum

#define wcstombs _wcstombs
#define wcstombs_s _wcstombs_s
#define wcsrtombs _wcsrtombs
#define wcrtomb _wcrtomb
#define mbstowcs _mbstowcs
#define mbsrtowcs _mbsrtowcs
#define wcsnrtombs _wcsnrtombs
#define mbsnrtowcs _mbsnrtowcs
#define mbrtowc _mbrtowc
#define mbrlen _mbrlen
#define mblen _mblen
#define mbsinit _mbsinit
#define mbtowc _mbtowc
#define wctomb _wctomb
#define wctob _wctob
#define btowc _btowc
#define wcpcpy _wcpcpy
#define wcpncpy _wcpncpy
#define wcscat _wcscat
#define wcsncat _wcsncat
#define wcsncpy _wcsncpy
#define wcspbrk _wcspbrk
#define wcschr _wcschr
#define wcsrchr _wcsrchr
#define wcsstr _wcsstr
#define wcstok _wcstok
#define wcscmp _wcscmp
#define wmemchr _wmemchr
#define wmemcpy _wmemcpy
#define wmemmove _wmemmove
#define wmemset _wmemset
#define wcslcat _wcslcat
#define wcslcpy _wcslcpy
#define wcslen _wcslen
#define wcsnlen _wcsnlen
#define wcsspn _wcsspn
#define wcscasecmp _wcscasecmp
#define wcsncasecmp _wcsncasecmp
#define wcsncmp _wcsncmp
#define wmemcmp _wmemcmp

/**
 * \endhtmlonly
 */

#endif
