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


/*!
  * \file wchar2.h
  * \mainpage LibWchar2
  * \brief This library design to use `wchar_t == 2`, Windows API software compatible.
  *
  * \par LibWchar2 Summary manual
  * https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html
  *
  * \par LibWchar2 Related manual pages
  * https://clnviewer.github.io/LibWchar2/docs/html/pages.html
  *
  * \tableofcontents
  *
  * \par Using
  * Using compilation keys to build your program with this library:
  *  - gcc as key:   `-fshort-wchar`
  *  - clang as key: `-fwchar-type=short` `-fno-signed-wchar`
  *
  * \author     `PS`
  * \copyright  `MIT` 2018 (c) `PS`
  * \see https://clnviewer.github.io/LibWchar2/ [`Web Home`]
  * \see https://github.com/ClnViewer/LibWchar2 [`Git Home`]
  *
  */

/*
  Missing curent, TODO ?:
      wcscoll   Locale-specific wide-character string compare
      wcscpy    Copy wide-character string
      wcscspn   Count wide characters not in string
      wcsxfrm   Locale-specific wide-character string transformation
 */

#ifndef WCHAR2_LIBC_H
#define WCHAR2_LIBC_H

#if defined(WCHAR2EXT_MSVC_H)
#   error "Only one header include, wchar2.h or wchar2ext.h"
#endif

#include <wctype.h>
#include <wchar.h>

#if !defined(__SIZEOF_WCHAR_T__)
#  error "'__SIZEOF_WCHAR_T__' NOT defined, system not supported"
#endif

#if defined(__SIZEOF_WCHAR_T__) && (__SIZEOF_WCHAR_T__ != 2)
#  error "size of 'wchar_t' != '2'; Use gcc key: '-fshort-wchar', or clang key: '-fwchar-type=short' '-fno-signed-wchar'"
#endif

#if ( \
        defined(_WIN32) || defined(__WIN32__) || defined(_Windows) || \
        defined(_WIN64) || defined(__WIN64__) || \
        defined(__CYGWIN__) || defined(__MINGW32__) || defined(__MINGW64__))

#  error "NOT include <wchar2.h>, for WINxx platform! use <wchar2ext.h> and libwchar2ext.* instead"
#endif

#if !defined(UINTMAX_MAX)
typedef unsigned long long int uintmax_t;
#endif
#if !defined(INTMAX_MAX)
typedef long long int intmax_t;
#endif

/*! \brief Define this flag for other software, indicate enable `libwchar2` in you project */
#define USED_WCHAR2LIB 1 /**< flag indicate enable libwchar2 */

#define __WS(x) __WS_(x) /**< static string to wide type macro */
#define __WSTR wchar_t   /**< definition wchar_t string macro */
#define __WSTRFREE __attribute__((cleanup(__wsfree))) __WSTR /**< auto free wchar_t string macro */
#define __WSTR_FMT "ls" /**< print format wchar_t string macro */
#define __WCHR_FMT "lc" /**< print format wchar_t char macro */
#define __WCSZ(x) ((x->sz + 1) * sizeof(wchar_t)) /**< determine size string_ws macro */

/*! \cond NOTINDOC */

#define __WS_(x) L##x
#define __WEV_(A,B) A ## B
#define __WEV(A,B)  __WEV_(A,B)
#define __WEVFA_(_11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N
#define __WEVFA(...) __WEVFA_(__VA_ARGS__, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define wsizeof(x) (unsigned long)(sizeof(x) / sizeof(wchar_t)) /**< determine size wchar_t object macro, replace `sizeof` */

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

/*! \endcond */

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Base wide string structure */
typedef struct
{
    wchar_t *str; /**<  \~English wide string pointer \~Russian указатель на строку широких символов */
    size_t   sz;  /**<  \~English size wide string \~Russian размер строки широких символов */

} string_ws;

/*! \~ \brief the contains constructs that facilitate directory traversing */
typedef struct _wdirent
{
    unsigned int   d_ino;        /**<  \~English Inode number \~Russian номер файла */
    long int       d_off;        /**<  \~English Offset \~Russian текущее положение */
    unsigned short d_reclen;     /**<  \~English Length of this record \~Russian длинна данных */
    unsigned char  d_type;       /**<  \~English Type of file \~Russian тип данных */
#   if defined(_DIRENT_HAVE_D_NAMLEN)
    unsigned char  d_namlen;     /**<  \~English Filename length \~Russian длинна поля имени файла */
#   endif
    wchar_t        d_name[256];  /**<  \~English Null-terminated filename \~Russian поле имени файла */
} wdirent_t;

/*! \~ \brief Main structure directory traversing, reference to `void` */
typedef void WDIR_t;

/*! \brief enumeration for return waccess function */
typedef enum
{
    ISERR        = -1, /**<  Error check */
    ISUNK        =  0, /**<  is a Unknown */
    ISFIL        =  1, /**<  is a Regular file */
    ISLNK        =  2, /**<  is a Symbolic link */
    ISDIR        =  3, /**<  is a Directory */
    ISCHR        =  4, /**<  is a character device */
    ISBLK        =  5, /**<  is a block device */
    ISSOCK       =  6, /**<  is a UNIX domain socket */
    ISFIFO       =  7, /**<  is a named pipe */
    ISWHT        =  8, /**<  is a whiteout" from BSD */
    DIRNODIR     =  9, /**<  options for read derrictory  - no print dir */
    DIRNOROOT    = 10, /**<  options for read derrictory  - no print root parent `.` or `..` dir */
    DIRENTRYSIZE = 11  /**<  options for read derrictory  - get files size */
} access_e;

/*! \~
 *  \brief CallBack for \ref _wreaddir_cb
 *  \param long: - counter
 *  \param access_e: - type of entry, see \ref access_e
 *  \param long long: - size of entry
 *  \param string_ws: - entry name (file/directory name), see \ref string_ws
 *  \param void: - user data
 */
typedef void (*wdir_cb)(unsigned int, access_e, long long, string_ws*, void*);

/*! \~
 *  \brief CallBack for \ref wstring_split_cb
 *  \param wchar_t: - splitting part from string
 *  \param size_t: - Length of string part
 *  \param long: - counter
 *  \param void: - user data
 */
typedef void (*split_cb)(wchar_t*, size_t, long, void*);

/*!
 * \brief Library current version
 */
const char * wchar2version(void);

/*!
 * \brief Translate wide characters to uppercase
 *
 * - \subpage towupper
 */
wchar_t   _towupper(wchar_t);

/*!
 * \brief Translate wide characters to lowercase
 *
 * - \subpage towlower
 */
wchar_t   _towlower(wchar_t);

/*!
 * \brief Extensible wide-character translation
 *
 * - \subpage towctrans
 */
wchar_t   _towctrans(wchar_t, wctrans_t);

/*!
 * \brief Compute wide-character test type
 *
 * - \subpage wctype
 */
wctype_t  _wctype(const char*);

/*!
 * \brief Compute wide-character translation type
 *
 * - \subpage wctrans
 */
wctrans_t _wctrans(const char*);

/*!
 * \brief Number of column positions of a wide-character code
 *
 * - \subpage wcwidth
 */
int       _wcwidth(wchar_t);

/*!
 * \brief Number of column positions of a wide-character string
 *
 * - \subpage wcswidth
 */
int       _wcswidth(const wchar_t*, size_t);

/*!
 * \brief Extensible wide-character test, wide-character classification
 *
 * - \subpage iswctype
 */
int       _iswctype(wchar_t, wctype_t);

/*!
 * \brief Test for hexadecimal digit wide character
 *
 * - \subpage iswxdigit
 */
int       _iswxdigit(wchar_t);

/*!
 * \brief Test for uppercase wide character
 *
 * - \subpage iswupper
 */
int       _iswupper(wchar_t);

/*!
 * \brief Test for whitespace wide character
 *
 * - \subpage iswspace
 */
int       _iswspace(wchar_t);

/*!
 * \brief Test for punctuation or symbolic wide character
 *
 * - \subpage iswpunct
 */
int       _iswpunct(wchar_t);

/*!
 * \brief Test for printing wide character
 *
 * - \subpage iswprint
 */
int       _iswprint(wchar_t);

/*!
 * \brief Test for lowercase wide character
 *
 * - \subpage iswlower
 */
int       _iswlower(wchar_t);

/*!
 * \brief Test for graphic wide character
 *
 * - \subpage iswgraph
 */
int       _iswgraph(wchar_t);

/*!
 * \brief Test for decimal digit wide character
 *
 * - \subpage iswdigit
 */
int       _iswdigit(wchar_t);

/*!
 * \brief Test for control wide character
 *
 * - \subpage iswcntrl
 */
int       _iswcntrl(wchar_t);

/*!
 * \brief Test for whitespace wide character
 *
 * - \subpage iswblank
 */
int       _iswblank(wchar_t);

/*!
 * \brief Test for whitespace wide character, alphabetic wide character predicate
 *
 * - \subpage iswalpha
 */
int       _iswalpha(wchar_t);

/*!
 * \brief Test for alphanumeric wide character, alphabetic wide character predicate
 *
 * - \subpage iswalnum
 */
int       _iswalnum(wchar_t);

/*!
 *  \paragraph `wchar_t` to number function
 */

/*!
 * \brief Convert wide character ASCII string to `double` number
 *
 * - \subpage wcstod
 */
double                 _wcstod(const wchar_t*, wchar_t**);

/*!
 * \brief Convert wide character ASCII string to `float` number
 *
 * - \subpage wcstof
 */
float                  _wcstof(const wchar_t*, wchar_t**);

/*!
 * \brief Convert wide character ASCII string to `long double` number
 *
 * - \subpage wcstold
 */
long double            _wcstold(const wchar_t*, wchar_t**);

/*!
 * \brief Convert wide character ASCII string to `long int` number
 *
 * - \subpage wcstol
 */
long int               _wcstol(const wchar_t*, wchar_t**, int);

/*!
 * \brief Convert wide character ASCII string to `long long int` number
 *
 * - \subpage wcstoll
 */
long long int          _wcstoll(const wchar_t*, wchar_t**, int);

/*!
 * \brief Convert wide character ASCII string to `unsigned long int` number
 *
 * - \subpage wcstoul
 */
unsigned long int      _wcstoul(const wchar_t*, wchar_t**, int);

/*!
 * \brief Convert wide character ASCII string to `unsigned long long int` number
 *
 * - \subpage wcstoull
 */
unsigned long long int _wcstoull(const wchar_t*, wchar_t**, int);

/*!
 * \brief Convert wide character ASCII string to `intmax_t` integer
 *
 * - \subpage wcstoimax
 */
intmax_t               _wcstoimax(const wchar_t*, wchar_t**, int);

/*!
 * \brief Convert wide character ASCII string to `uintmax_t` integer
 *
 * - \subpage wcstoumax
 */
uintmax_t              _wcstoumax(const wchar_t*, wchar_t**, int);


/*!
 *  \paragraph `Multibyte String` functions
 */

/*!
 * \brief Minimal wide string to multibyte string converter
 *
 * - \subpage wcstombs
 */
size_t    _wcstombs(char *restrict, const wchar_t *restrict, size_t);

/*!
 * \brief Minimal wide string to multibyte string converter + double size out buffer
 *
 * - \subpage wcstombs
 */
size_t    _wcstombs_s(char *restrict, const wchar_t *restrict, size_t);

/*!
 * \brief Convert a wide-character string to a character string
 *
 * - \subpage wcsrtombs
 */
size_t    _wcsrtombs(char *restrict, const wchar_t **restrict, size_t, mbstate_t *restrict);

/*!
 * \brief Convert wide character to multibyte sequence
 *
 * - \subpage wcrtomb
 */
size_t    _wcrtomb(char *restrict, wchar_t, mbstate_t *restrict);

/*!
 * \brief Minimal multibyte string to wide string converter
 *
 * - \subpage mbstowcs
 */
size_t    _mbstowcs(wchar_t *restrict, const char *restrict, size_t);

/*!
 * \brief Convert a character string to a wide-character string
 *
 * - \subpage mbsrtowcs
 */
size_t    _mbsrtowcs(wchar_t *restrict, const char **restrict, size_t, mbstate_t *restrict);

/*!
 * \brief Convert a wide-character string to a character string
 *
 * - \subpage wcsnrtombs
 */
size_t    _wcsnrtombs(char *restrict, const wchar_t **restrict, size_t, size_t, mbstate_t *restrict);

/*!
 * \brief Convert a character string to a wide-character string
 *
 * - \subpage mbsnrtowcs
 */
size_t    _mbsnrtowcs(wchar_t *restrict, const char **restrict, size_t, size_t, mbstate_t *restrict);

/*!
 * \brief Converts a narrow multibyte character to a wide character
 *
 * - \subpage mbrtowc
 */
size_t    _mbrtowc(wchar_t *restrict, const char *restrict src, size_t, mbstate_t *restrict);

/*!
 * \brief Get length of multibyte character
 *
 * - \subpage mbrlen
 */
size_t    _mbrlen(const char *restrict, size_t, mbstate_t *restrict);

/*!
 * \brief Determines the size, in bytes, of the multibyte character whose first byte is pointed
 *
 * - \subpage mblen
 */
int       _mblen(const char*, size_t);

/*!
 * \brief Check if initial conversion state
 *
 * - \subpage mbsinit
 */
int       _mbsinit(const mbstate_t*);

/*!
 * \brief Minimal multibyte to wide char converter
 *
 * - \subpage mbtowc
 */
int       _mbtowc(wchar_t *restrict, const char *restrict, size_t);

/*!
 * \brief Minimal wide char to multibyte converter
 *
 * - \subpage wctomb
 */
int       _wctomb(char*, wchar_t);

/*!
 * \brief Convert wide character to single byte
 *
 * - \subpage wctob
 */
int       _wctob(wchar_t);

/*!
 * \brief Convert single byte character to wide character
 *
 * - \subpage btowc
 */
wchar_t   _btowc(int);

/*!
 * \~
 * \par Other non standart functions
 *
 */

/*!
 * \brief wchar_t* print
 * This function to test variably only!
 * Instead use _vfprintf, _vfwprintf, _fprintf, _fwprintf
 *
 */
void      wcprint(wchar_t*);

/*!
 * \brief compare char* <->  wchar_t*
 * This function quick compare only ASCII range, NOT all Unicode symbols support!
 * size_t - wchar_t* size
 * return - boolean
 *
 */
int       wcstocscmp(const char*, wchar_t*, size_t); // ASCII range only

/*!
 *    Original name: aov-rx - Angel Ortega's regular expression library
 *    Copyright (C) 2011/2012 Angel Ortega <angel@triptico.com>
 *    https://github.com/angelortega/aov-rx or http://triptico.com
 *
 * \brief wcsregexp - Matches a regular expression
 * \param rx: the regular expression
 * \param tx: the text to be matched
 * \param size: a pointer to integer where the matching length is stored
 *
 * Matches the string tx for the regular expression in rx.
 * On output, the integer pointer by size will contain the number
 * of matched characters (with 0 meaning that no matching was
 * possible). If the end of string mark ($) is used in the regular
 * expression and a match is effective, the ending zero is included
 * in the match.
 *
 * Returns the address of the match.
 */
wchar_t * wcsregexp(wchar_t *restrict, wchar_t *restrict, int*);

/*!
 *  \brief Covert utf-8 `char*` to `wchar_t*`
 *  \param wchar_t*:    - output
 *  \param const char*: - input
 *  return size_t       - size
 *
 *  \note function u8stowcs requires to free the returned result
 */
size_t    u8stowcs(wchar_t*, const char*);

/*!
 *  \brief Convert `wchar_t*` to utf-8 `char*`
 *  \param char*:          - output
 *  \param const wchar_t*: - input
 *  return size_t          - size
 *
 *  \note function wcstou8s requires to free the returned result
 */
size_t    wcstou8s(char*, const wchar_t*);

/*!
 *  \brief Verify `char*` to utf-8 valid string
 *  \param const char*: - input
 *  \param int:         - output (bool)
 *
 */
int       u8sverify(const char*);

/*!
 * \brief Copy a wide-character string returning a pointer to its end
 *
 * - \subpage wcpcpy
 */
wchar_t * _wcpcpy(wchar_t*, const wchar_t*);

/*!
 * \brief Copy part of a wide-character string returning a pointer to its end
 *
 * - \subpage wcpncpy
 */
wchar_t * _wcpncpy(wchar_t*, const wchar_t*, size_t);

/*!
 * \brief Concatenate wide-character strings
 *
 * - \subpage wcscat
 */
wchar_t * _wcscat(wchar_t*, const wchar_t*);

/*!
 * \brief Concatenate wide-character strings with size
 *
 * - \subpage wcsncat
 */
wchar_t * _wcsncat(wchar_t*, const wchar_t*, size_t);

/*!
 * \brief Counted copy wide-character string
 *
 * - \subpage wcsncpy
 */
wchar_t * _wcsncpy(wchar_t*, const wchar_t*, size_t);

/*!
 * \brief Find wide characters in string
 *
 * - \subpage wcspbrk
 */
wchar_t * _wcspbrk(const wchar_t*, const wchar_t*);

/*!
 * \brief Search for wide character in string
 *
 * - \subpage wcschr
 */
wchar_t * _wcschr(const wchar_t*, wchar_t);

/*!
 * \brief Reverse search for wide character in string
 *
 * - \subpage wcsrchr
 */
wchar_t * _wcsrchr(const wchar_t*, wchar_t);

/*!
 * \brief Find wide-character string segment
 *
 * - \subpage wcsstr
 */
wchar_t * _wcsstr(const wchar_t*, const wchar_t*);

/*!
 * \brief Tokenize wide-character string
 *
 * - \subpage wcstok
 */
wchar_t * _wcstok(wchar_t*, const wchar_t*, wchar_t**);

/*!
 * \brief Find wide character in memory
 *
 * - \subpage wmemchr
 */
wchar_t * _wmemchr(const wchar_t*, wchar_t, size_t);

/*!
 * \brief Copy wide characters in memory
 *
 * - \subpage wmemcpy
 */
wchar_t * _wmemcpy(wchar_t*, const wchar_t*, size_t);

/*!
 * \brief Copy wide characters in memory with overlapping areas
 *
 * - \subpage wmemmove
 */
wchar_t * _wmemmove(wchar_t*, const wchar_t*, size_t);

/*!
 * \brief Set wide characters in memory
 *
 * - \subpage wmemset
 */
wchar_t * _wmemset(wchar_t*, wchar_t, size_t);

/*! \brief Concatenate wide-character strings to specified length */
size_t    _wcslcat(wchar_t*, const wchar_t*, size_t);
/*! \brief Copy wide-character string to specified length */
size_t    _wcslcpy(wchar_t*, const wchar_t*, size_t);

/*!
 * \brief Wide-character string length
 *
 * - \subpage wcslen
 */
size_t    _wcslen(const wchar_t*);

/*!
 * \brief Wide-character string length with maximum limit
 *
 * - \subpage wcsnlen
 */
size_t    _wcsnlen(const wchar_t*, size_t);

/*! \brief Find initial match in wide-character string */

/*!
 * \brief Find initial match in wide-character string
 *
 * - \subpage wcsspn
 */
size_t    _wcsspn(const wchar_t*, const wchar_t*);

/*!
 * \brief Case-insensitive wide character string compare
 *
 * - \subpage wcscasecmp
 */
int       _wcscasecmp(const wchar_t*, const wchar_t*);

/*!
 * \brief Case-insensitive wide character string compare with size
 *
 * - \subpage wcsncasecmp
 */
int       _wcsncasecmp(const wchar_t*, const wchar_t*, size_t);

/*!
 * \brief Wide-character string compare
 *
 * - \subpage wcscmp
 */
int       _wcscmp(const wchar_t*, const wchar_t*);
/*! \brief Wide-character string compare */

/*!
 * \brief Wide-character string compare
 *
 * - \subpage wcsncmp
 */
int       _wcsncmp(const wchar_t*, const wchar_t*, size_t);

/*!
 * \brief Compare wide characters in memory
 *
 * - \subpage wmemcmp
 */
int       _wmemcmp(const wchar_t*, const wchar_t*, size_t);

/*! \brief Write to stream char format variable argument list */
int       _vfprintf(FILE *restrict, const char *restrict, va_list)
__attribute__((__nonnull__, __format__(__printf__, 2, 0)));

/*! \brief Write formatted data from variable argument list to sized buffer */
int       _vsnprintf(char *restrict, size_t, const char *restrict, va_list)
__attribute__((__format__(__printf__, 3, 0)));

/*! \brief Write to stream char format variable arguments */
int       _fprintf(FILE *restrict, const char *restrict, ...)
__attribute__((__nonnull__, __format__(__printf__, 2, 0)));

/*! \brief Write to stdout char format variable arguments */
int       _printf(const char *restrict fmt, ...)
__attribute__((__nonnull__, __format__(__printf__, 1, 0)));

/*! \brief Format variable arguments list */
int       _snprintf(char *restrict, size_t, const char *restrict, ...)
__attribute__((__format__(__printf__, 3, 0)));

/*!
 * \brief Write to stream wide character format variable argument list
 *
 * - \subpage wprintf
 */
int       _vfwprintf(FILE *restrict, const wchar_t *restrict, va_list)
/* __attribute__((__nonnull__, __format__(__wprintf__, 2, 0))) */ ;

/*!
 * \brief Write formatted data from variable argument list to sized buffer
 *
 * - \subpage wprintf
 */
int       _vswprintf(wchar_t *restrict, size_t, const wchar_t *restrict, va_list)
/* __attribute__((__format__(__wprintf__, 3, 0))) */ ;

/*!
 * \brief Write to stream wide character format variable arguments
 *
 * - \subpage wprintf
 */
int       _fwprintf(FILE *restrict, const wchar_t *restrict, ...)
/* __attribute__((__nonnull__, __format__(__wprintf__, 2, 0))) */ ;

/*!
 * \brief Write formatted wide character output
 *
 * - \subpage wprintf
 */
int       _swprintf(wchar_t *restrict, size_t, const wchar_t *restrict, ...)
/* __attribute__((__format__(__wprintf__, 3, 0))) */ ;

/*!
 * \~English
 * \brief Write a formatted wide character string to 'stdout'.
 *
 * \~Russian
 * \brief Записать согласно формату широкий строку символов в консоль, поток 'stdout'.
 *
 * \~
 * - \subpage wprintf
 */
int       _wprintf(const wchar_t *restrict fmt, ...)
/* __attribute__((__format__(__wprintf__, 1, 0))) */ ;

/*!
 * \~English
 * \brief Write a wide character string to a file or stream.
 *
 * \~Russian
 * \brief Записать широкий строку символов в поток открытого файла.
 *
 * \~
 * - \subpage fputws
 */
int       _fputws(const wchar_t *restrict, FILE *restrict);

/*!
 * \~English
 * \brief Write a wide character to a file or stream.
 *
 * \~Russian
 * \brief Записать широкий символ в поток открытого файла.
 *
 * \~
 * - \subpage fputwc
 */
wchar_t   _fputwc(wchar_t, FILE *restrict);

/*!
 * \~English
 * \brief Convert date and time to a formatted wide-character string.
 *
 * \details The original version of the `strftime()` function is used for the conversion.
 *          The `wcsftime()` function converts the results from wide characters to a multibyte
 *          string and back.
 *
 * \~Russian
 * \brief Преобразование даты и времени в форматированную строку с широкими символоми.
 *
 * \details Это широкосимвольный аналог `strftime()`.
 *          Для преобразования используется оригинальная версия функции `strftime()`.
 *          Функция преобразовывает результаты из строки широких символов в многобайтовую
 *          строку и обратно.
 *
 * \~

 IBM  | GNU |   MinGW   | MSVC/MSVS
------|-----|-----------|-----------
  x   |  x  | This code | This code

 *
 * - \subpage wcsftime
 * - \ref _wcsptime related \ref _wcsftime
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use wcsftime
 *
 */
size_t    _wcsftime(wchar_t *restrict, size_t sz, const wchar_t *restrict, const void *restrict);

/*!
 * \~English
 * \brief Convert a wide-character string representation of time to a time `tm` structure.
 *
 * \details The function `wcsptime()` is equivalent to the function `strptime()`.
 *          The `wcsptime()` function converts a wide character string into a `tm`
 *          structure format, according to the format specified in the parameters.
 *
 * \~Russian
 * \brief Преобразование широкоформатного строкового представления времени в структуру `tm`.
 *
 * \details Функция `wcsptime()` эквивалентна функции `strptime()`.
 *          Функция `wcsptime()` преобразует строку широких символов в формат структуры `tm`,
 *          в соответствии с форматом, указанным в параметрах.
 *
 * \~

 IBM  |    GNU    |   MinGW   | MSVC/MSVS
------|-----------|-----------|-----------
   x  | This code | This code | This code

 *
 * - \subpage wcsptime
 * - \ref _wcsptime related \ref _wcsftime
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use wcsftime
 *
 */
wchar_t * _wcsptime(const wchar_t*, const wchar_t*, void*);

/*!
 * \~English
 * \paragraph Open file stream
 *
 * \~Russian
 * \paragraph Открыть поток для файла
 *
 */

/*!
 * \~English
 * \brief Open the stream for the file, takes as the first parameter the file name
 *        and the second parameter the opening mode in the form of wide characters.
 *
 * \~Russian
 * \brief Открыть поток для файла, принимает в качестве первого параметра имя файла
 *        и второго параметра режим открытия в виде широких символов.
 *
 * \~
 * - \subpage wfopen
 */
FILE    * _wfopen(const wchar_t*, const wchar_t*)
__attribute__((warn_unused_result));

/*!
 * \~English
 * \brief The same as \ref _wfopen, the `size_t` parameter must contain the length
 *        of the variable of the file name, or zero.
 *
 * \~Russian
 * \brief То же, что и \ref _wfopen, параметр `size_t` должен содержать длинну переменной
 *        имени файла, или ноль.
 *
 * \~
 * - \subpage wfopen
 */
FILE    * _wfopen_s(const wchar_t*, size_t, const wchar_t*)
__attribute__((warn_unused_result));

/*!
 * \~English
 * \brief The same as \ref _wfopen, the input parameter filename is passed in the `string_ws` structure.
 *
 * \~Russian
 * \brief То же, что и \ref _wfopen, входной параметр имя файла передаеться в структуре `string_ws`.
 *
 * \~
 * - \subpage wfopen
 */
FILE    * _wfopen_ws(const string_ws*, const wchar_t*)
__attribute__((warn_unused_result));

/*!
 * \~English
 * \brief Automatic type selector for `wfopen*` functions
 *
 * \~Russian
 * \brief Автоматический селектор типов для функций `wfopen*`
 *
 * \~
 * - \subpage wfopen
 */
FILE    * _wfopen_selector(int, const void*, size_t, const void*)
__attribute__((warn_unused_result));

/*!
 * \~English
 * \brief Open file stream, after converting the file name from wide characters to UTF-8
 *
 * \attention function `u8wfopen` requires to free the returned result
 *
 * \~Russian
 * \brief Открыть поток для файла, предварительно преобразовав имя файла из широких символов в UTF-8
 *
 * \attention Функция `u8wfopen` требует освободить возвращаемый результат
 *
 */
FILE    * u8wfopen(const wchar_t*, const wchar_t*)
__attribute__((warn_unused_result));

/*!
 * \~English
 * \paragraph Statistic from file
 *
 * \brief Functions `wstat*()` fill the structure with data about the file pointed to by `struct stat`,
 *        associated with the file name.
 *
 * \return If stat is successfully populated, `0` is returned.
 *         In case of failure, `-1` is returned, and `errno` is set to `ENOENT`.
 *
 * \note The operation of the functions `wstat*()` is completely analogous to the function `stat()`
 *
 * \~Russian
 * \paragraph Статисика параметров файла
 *
 * \brief Функции `wstat*()` запоняют структуру данными о файле, на которую указывает `struct stat`,
 *        связанном с именем файла.
 *
 * \return При успешном заполнении структуры stat возвращается `0`.
 *         В случае неудачи возвращается `—1`, а `errno` устанавливается в `ENOENT`.
 *
 * \note Работа функций `wstat*()` полностью аналогична функции `stat()`
 *
 * \~
 * - \subpage wstat
 */
int       _wstat(const wchar_t*, void*);

/*!
 * \~English
 * \brief The same as \ref _wstat, the `size_t` parameter must contain the length
 *        of the variable of the file name, or zero.
 *
 * \~Russian
 * \brief То же, что и \ref _wstat, параметр `size_t` должен содержать длинну переменной
 *        имени файла, или ноль.
 *
 * \~
 * - \subpage wstat
 */
int       _wstat_s(const wchar_t*, size_t, void*);

/*!
 * \~English
 * \brief The same as \ref _wstat, the input parameter filename is passed in the `string_ws` structure.
 *
 * \~Russian
 * \brief То же, что и \ref _wstat, входной параметр имя файла передаеться в структуре `string_ws`.
 *
 * \~
 * - \subpage wstat
 */
int       _wstat_ws(const string_ws*, void*);

/*!
 * \~English
 * \brief Automatic type selector for `wstat*` functions
 *
 * \~Russian
 * \brief Автоматический селектор типов для функций `wstat*`
 *
 * \~
 * - \subpage wstat
 */
int       _wstat_selector(int, const void*, size_t, const void*);

/*!
 * \~English
 * \brief Get file statistics by first converting the file name from wide characters to UTF-8.
 *
 * \attention Function `u8wstat` requires to free the returned result
 *
 * \~Russian
 * \brief Получить статистику файла, предварительно преобразовав имя файла из широких символов в UTF-8
 *
 * \attention Функция `u8wstat` требует освободить возвращаемый результат
 */
int       u8wstat(const wchar_t*, void*);

/*!
 * \~English
 * \paragraph Rename (move) file
 *
 * \brief The `wrename()` function changes the file name to a new one.
 *
 * \details The `wrename*()` function changes the name or location of the file,
 *          returns a standard response as a function of `rename()`.
 *          The new name must not be the same as the names in the directory.
 *
 * \return The function `wrename()` returns `0` in case of success and a
 *         nonzero value in case of an error.
 *         On error, `errno` is set, indicating an error.
 *
 * \~Russian
 * \paragraph Переименовать (переместить) файл
 *
 * \brief Функция `wrename()` изменяет название файла на новое.
 *
 * \details Функция `wrename*()` изменяет имя или местоположение файла, возвращает стандартный ответ,
 *          как функция `rename()`.
 *          Новое имя не должно совпадать с именами, имеющимися в каталоге.
 *
 * \return Функция `wrename()` возвращает `0` в случае успеха и ненулевую величину — в случае ошибки.
 *         При ошибке устанавливается `errno` с указанием ошибки.
 *
 * \~
 * - \subpage wrename
 */
int       _wrename(const wchar_t*, const wchar_t*);

/*!
 * \~English
 * \brief The same as \ref _wrename, the `size_t` parameter must contain the length
 *        of the variable of the file name, or zero.
 *
 * \~Russian
 * \brief То же, что и \ref _wrename, параметр `size_t` должен содержать длинну переменной
 *        имени файла, или ноль.
 *
 * \~
 * - \subpage wrename
 */
int       _wrename_s(const wchar_t*, size_t, const wchar_t*, size_t);

/*!
 * \~English
 * \brief The same as \ref _wrename, the input parameter filename is passed in the `string_ws` structure.
 *
 * \~Russian
 * \brief То же, что и \ref _wrename, входной параметр имя файла передаеться в структуре `string_ws`.
 *
 * \~
 * - \subpage wrename
 */
int       _wrename_ws(const string_ws*, const string_ws*);

/*!
 * \~English
 * \brief Automatic type selector for `wrename*` functions
 *
 * \~Russian
 * \brief Автоматический селектор типов для функций `wrename*`
 *
 * \~
 * - \subpage wrename
 */
int       _wrename_selector(int, const void*, size_t, const void*, size_t);

/*!
 * \~English
 * \brief Rename file, after converting the file name from wide characters to UTF-8
 *
 * \attention function `u8wrename` requires to free the returned result
 *
 * \~Russian
 * \brief Переименовать файл, предварительно преобразовав имя файла из широких символов в UTF-8
 *
 * \attention Функция `u8wrename` требует освободить возвращаемый результат
 *
 */
int       u8wrename(const wchar_t*, const wchar_t*);

/*!
 * \~English
 * \paragraph Delete (remove) file or directory
 *
 * \brief The `wremove*()` function deletes a name from the file system.
 *
 * \return  If the file was safely deleted, `0` is returned, in the event of a `-1` error.
 *          On error, `errno` is set to: `ENOENT` - the file does not exist,
 *          or in `EACESS` - access is denied.
 *
 * \~Russian
 * \paragraph Удалить файл или дерикторию
 *
 * \brief Функция `цremove*()` удаляет файла или дерикторию по имени.
 *
 * \return Если файл был благополучно удален, возвращается `0`, в случае ошибки `-1`.
 *         При ошибке `errno` устанавливается в: `ENOENT` - Файл не существует,
 *         или в `EACESS` - доступ запрещен.
 *
 * \~
 * - \subpage wremove
 */
int       _wremove(const wchar_t*);

/*!
 * \~English
 * \brief The same as \ref _wremove, the `size_t` parameter must contain the length
 *        of the variable of the file name, or zero.
 *
 * \~Russian
 * \brief То же, что и \ref _wremove, параметр `size_t` должен содержать длинну переменной
 *        имени файла, или ноль.
 *
 * \~
 * - \subpage wremove
 */
int       _wremove_s(const wchar_t*, size_t);

/*!
 * \~English
 * \brief The same as \ref _wremove, the input parameter filename is passed in the `string_ws` structure.
 *
 * \~Russian
 * \brief То же, что и \ref _wremove, входной параметр имя файла передаеться в структуре `string_ws`.
 *
 * \~
 * - \subpage wremove
 */
int       _wremove_ws(const string_ws*);

/*!
 * \~English
 * \brief Automatic type selector for `wremove*` functions
 *
 * \~Russian
 * \brief Автоматический селектор типов для функций `wremove*`
 *
 * \~
 * - \subpage wremove
 */
int       _wremove_selector(int, const void*, size_t);

/*!
 * \~English
 * \brief Delete (remove) file or directory, after converting the file name from wide characters to UTF-8
 *
 * \attention function `u8wremove` requires to free the returned result
 *
 * \~Russian
 * \brief Удаляет файла или дерикторию, предварительно преобразовав имя файла из широких символов в UTF-8
 *
 * \attention Функция `u8wremove` требует освободить возвращаемый результат
 *
 */
int       u8wremove(const wchar_t*);

/*!
 * \~English
 * \brief Creates a directory or a chain of directories specified in the path
 * \note The equivalent of using the `mkdir` command with the `-p` switch for all functions `wmkdir*()`
 *       If the internal flag `EXIST` is received while creating the directory, the function continues execution,
 *       if this is the last one from the list of created directories, it returns `0`.
 *       In other cases, returns a standard response as a function of `mkdir()`.
 *       If the directory exists from the specified path, the function continues execution,
 *       proceeding to create the next directory.
 *
 * \~Russian
 * \brief Создает дерикторию или цепочку директорий указанных в пути
 * \note Эквивалент использования команды `mkdir` с ключом `-p` для всех функций `_wmkdir*()`.
 *       Если внутренний флаг `EXIST` получен при создании каталога, функция продолжает выполнение,
 *       если это последний из списка создаваемых каталогов, возвращаеться `0`.
 *       В других случаях, возвращает стандартный ответ, как функция `mkdir()`.
 *       В случае существования каталога из указанного пути, функция продолжает выполнение,
 *       переходя к созданию следующего каталога.
 *
 * \~
 * - \subpage wmkdir
 */
int       _wmkdir(const wchar_t*, mode_t);

/*!
 * \~English
 * \brief The same as \ref _wmkdir, the `size_t` parameter must contain the length
 *        of the variable of the file name, or zero.
 *
 * \~Russian
 * \brief То же, что и \ref _wmkdir, параметр `size_t` должен содержать длинну переменной
 *        имени файла, или ноль.
 *
 * \~
 * - \subpage wmkdir
 */
int       _wmkdir_s(const wchar_t*, size_t, mode_t);

/*!
 * \~English
 * \brief The same as \ref _wmkdir, the input parameter filename is passed in the `string_ws` structure.
 *
 * \~Russian
 * \brief То же, что и \ref _wmkdir, входной параметр имя файла передаеться в структуре `string_ws`.
 *
 * \~
 * - \subpage wmkdir
 */
int       _wmkdir_ws(const string_ws*, mode_t);

/*!
 * \~English
 * \brief Automatic type selector for `wmkdir*` functions
 *
 * \~Russian
 * \brief Автоматический селектор типов для функций `wmkdir*`
 *
 * \~
 * - \subpage wmkdir
 */
int       _wmkdir_selector(int, const void*, size_t, mode_t);

/*!
 * \~English
 * \brief Creates a directory or a chain of directories specified in the path,
 *        after converting the file name from wide characters to UTF-8
 *
 * \attention function `u8wmkdir` requires to free the returned result
 *
 * \~Russian
 * \brief Создает дерикторию или цепочку директорий указанных в пути,
 *        предварительно преобразовав имя файла из широких символов в UTF-8
 *
 * \attention Функция `u8wmkdir` требует освободить возвращаемый результат
 *
 */
int       u8wmkdir(const wchar_t*, mode_t);


/*!
 * \~
 *  \paragraph Check permissions for a file or directory
 *  \note All waccess* function return extended status, see \ref access_e enum value,
 *        if error return standart -1
 *
 * - \subpage waccess
 */

/*!
 * \~
 * \brief Check permissions for a file or directory, wide char input
 * \attention function returned Non-standard `enum` \ref access_e result
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use waccess errorcode
 * \snippet ./test/check_wchar2_MSVC.c Example use waccess declare
 * \snippet ./test/check_wchar2_MSVC.c Example use waccess code
 *
*/
access_e  _waccess(const wchar_t*, int);
/*! \brief Check permissions for a file or directory, wide char input with size */
access_e  _waccess_s(const wchar_t*, size_t, int);
/*! \brief Check permissions for a file or directory, struct string_ws input */
access_e  _waccess_ws(const string_ws*, int);
/*! \brief Automatic type selector for wmkdir* functions */
access_e  _waccess_selector(int, const void*, size_t, int);
/*!
 *  \brief Check permissions for a file or directory, convert file name from wide characters to UTF-8
 *  \attention function u8waccess requires to free the returned result
 */
access_e  u8waccess(const wchar_t*, int);

/*!
 *  \paragraph Parse path file name
 *  \note If Success return substring of path, else return NULL
 */

/*! \brief Parse path file name, wide char input */
wchar_t * _wbasename(const wchar_t*);
/*! \brief Parse path file name, struct string_ws input */
wchar_t * _wbasename_ws(const string_ws*);
/*! \brief Automatic type selector for wbasename* functions */
void *    _wbasename_selector(int, const void*);

/*!
 *  \paragraph Parse path extension
 *  \note If Success return substring of path, else return NULL
 */

/*! \brief Parse path extension, wide char input */
wchar_t * _wbaseext(const wchar_t*);
/*! \brief Parse path extension, struct string_ws input */
wchar_t * _wbaseext_ws(const string_ws*);
/*! \brief Automatic type selector for wbaseext* functions */
void *    _wbaseext_selector(int, const void*);

/*!
 *  \paragraph Parse path directory
 *  \note If Success return substring of path, else return NULL
 *  \attention all functions _wbasedir* requires to free the returned result, use type __WSTRFREE for auto free
 */

/*! \brief Parse path directory + normalize slash from path, wide char input */
wchar_t * _wbasedir(const wchar_t*, int)
__attribute__((warn_unused_result));
/*! \brief Parse path directory + normalize slash from path, struct string_ws input */
wchar_t * _wbasedir_ws(const string_ws*, int)
__attribute__((warn_unused_result));
/*! \brief Automatic type selector for wbasedir* functions */
void *    _wbasedir_selector(int, const void*, int)
__attribute__((warn_unused_result));

/*!
 *  \paragraph Normalize slash from path
 *  \note If Success return modified path, else return NULL
 *  \attention all functions _wpathnormalize* requires to free the returned result, use type __WSTRFREE for auto free
 */

/*! \brief Normalize slash from path, wide char input, int is string size, default 0 */
wchar_t * _wpathnormalize(const wchar_t*, size_t)
__attribute__((warn_unused_result));
/*! \brief Normalize slash from path, struct string_ws input */
wchar_t * _wpathnormalize_ws(const string_ws*)
__attribute__((warn_unused_result));

/*!
 *  \brief Normalize slash from path, convert file name from wide characters to UTF-8
 *  \attention function u8wpathnormalize requires to free the returned result
 */
char *    u8wpathnormalize(const wchar_t*)
__attribute__((warn_unused_result));


/*
 * \~English
 * \section wchar2wstring API use structure string_ws
 *
 * \~Russian
 * \section wchar2wstring API - Работа со структорой string_ws
 *
 */

/*!
 * \~English
 * \paragraph wchar2wsalloc Allocate memory functions
 *
 * \~Russian
 * \paragraph wchar2wsalloc Функции работы с динамической памятью
 *
 * \~
 */


/*! \brief Memory free string, empty and clear struct string_ws */
void      wstring_free(string_ws *restrict);

/*! \brief Memory allocation string, struct string_ws->str output */
size_t    wstring_alloc(string_ws *restrict, size_t);

/*!
 *  \brief Converting string, wchar_t input, char allocate output
 *  \attention function wstring_wstocs_alloc requires to free the returned result
 */
char    * wstring_wstocs_alloc(const wchar_t *restrict)
__attribute__((warn_unused_result));

/*!
 *  \brief Converting string, string_ws input, char allocate output
 *  \attention function wstring_swstocs_alloc requires to free the returned result
 */
char    * wstring_swstocs_alloc(const string_ws *restrict)
__attribute__((warn_unused_result));

/*!
 *  \brief Converting string, char input, wchar_t allocate output
 *  \attention function wstring_cstows_alloc requires to free the returned result
 */
wchar_t * wstring_cstows_alloc(const char *restrict)
__attribute__((warn_unused_result));

/*!
 *  \brief Converting string, string_ws input, length output
 *  \attention function wstring_cstows_alloc requires to free the returned result
 */
size_t    wstring_cstows_ws_alloc(string_ws *restrict, const char *restrict);

/*!
 *  \brief Append string, format `vargs` support input, `struct string_ws` output
 *
 *  \param destination: \ref string_ws
 *  \param format:  String type `wchar_t*`.
 *  \param arguments:  Arguments support to `vargs` types, 125 max.
 *  \return length of `output` produced.
 *
 *  \attention curent status: broken, if out data large 8192 byte!
 *             Now, fixing output buffer size 8192 byte for *nix version.
 *             For MinGW32 always fixing output buffer size 8192 byte.
 *             TODO: rewrite length detected for *nix
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use wstring_format code
 *
 */
size_t    wstring_format(string_ws*, const wchar_t *restrict, ...);

/*!
 *  \brief Append string: `wchar_t*`, length input, `struct string_ws` output
 *
 *  \param destination: \ref string_ws
 *  \param source:  String type `wchar_t*`.
 *  \param length:  length of `source` string.
 *  \return length of `output` produced.
 *
 *  \attention function `wstring_append()` requires to free the returned result
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use wstring_append code
 *
 */
size_t    wstring_append(string_ws*, const wchar_t *restrict, size_t);

/*!
 *  \brief Append strings, only `wchar_t*` strings args inputs, `struct string_ws` output
 *
 *  \param destination: \ref string_ws
 *  \param arguments:  Strings type `wchar_t*`, 126 max.
 *  \return length of `output` produced.
 *
 *  \note Do not use this function directly, first use the `wstring_appends()` macro,
 *        or end the last function's parameters with a value of `NULL`.
 *  \attention function `wstring_appends_()` requires to free the returned result
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use wstring_appends code
 *
 */
size_t    wstring_appends_(string_ws*, ...);

/*!
 *  \brief Macro to function \ref wstring_appends_, see notes
 */
#define   wstring_appends(A,...) wstring_appends_(A,__VA_ARGS__,NULL)

/*!
 *  \brief Append string: source type `char*`, length input, `struct string_ws` output
 *
 *  \param destination: \ref string_ws
 *  \param source:  String type `char*`.
 *  \param length:  length of `source` string.
 *  \return length of `output` produced.
 *
 *  \attention function `wstring_append_cvt()` requires to free the returned result
 *
 */
size_t    wstring_append_cvt(string_ws*, const char *restrict, size_t);

/*!
 *  \paragraph User buffer memory function
 */

/*!
 * \~
 * \brief Converting string, `char` input, `wchar_t` array output, to allocate buffer write
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use ws-cs convert
 *
 */
size_t    wstring_cstows(wchar_t [], size_t, const char *restrict, size_t);

/*!
 * \~
 * \brief Converting string, `wchar_t` input, `char` array output, to allocate buffer write
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use ws-cs convert
 *
 */
size_t    wstring_wstocs(char [], size_t, const wchar_t *restrict, size_t);

/*!
 * \~
 * \brief Converting string, structure `string_ws` input, `char` array output, to allocate buffer write
 *
 */
size_t    wstring_wstocs_ws(char [], size_t, const string_ws *restrict);

/*!
 * \~English
 * \subsection wchar2wstime Time format functions
 *
 * \~Russian
 * \subsection wchar2wstime Функции работы с датой и временем
 *
 * \~
 */


/*!
 * \brief Converting time format string to string, wchar_t and size_t input
 * \attention function wstring_timeformat requires to free the returned result
 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use wstring_timeformat
 *
 */
wchar_t * wstring_timeformat(const wchar_t *restrict, size_t, const wchar_t *restrict, const wchar_t *restrict)
__attribute__((warn_unused_result));

/*!
 *  \brief Converting time format string to string, string_ws input
 *  \attention function wstring_timeformat_ws requires to free the returned result
 */
wchar_t * wstring_timeformat_ws(const string_ws *restrict, const wchar_t *restrict, const wchar_t *restrict)
__attribute__((warn_unused_result));

/*!
 *  \brief Split string_ws string, from wchar_t  characters and call \ref split_cb to result data
 *  \return number of splits
 */
long      wstring_split_cb(const string_ws*, wchar_t, split_cb, void*);


/*!
 * \~English
 * \subsection wchar2wsalloc Other misc functions
 *
 * \~Russian
 * \subsection wchar2wsalloc Функции теста строк и их преобразования
 *
 * \~
 */

/*! \brief Check wchar_t input string is empty, bool return */
int       wstring_isempty(const wchar_t *restrict s, int);

/*!
 *  \brief Truncation string, wchar_t input, struct string_ws return
 */
string_ws wstring_trunc(const wchar_t *ws, int);

/*!
 *  \brief Truncation string, wchar_t input, return pointer to struct string_ws and length
 */
size_t    wstring_trunc_alloc(string_ws *restrict, const wchar_t*, int);

/*!
 * \~English
 * \subsection wchar2dir Directory function
 *
 * \~Russian
 * \subsection wchar2dir Работа с каталогами
 *
 */

/*!
 * \~English
 * \brief Closes the directory stream
 *
 * \details The `wclosedir()` function closes the directory stream.
 *          If the function is successfully called, the file descriptor associated with the directory is also closed.
 *          The descriptor of the directory stream opened in the past will be unavailable after this call.
 *
 * \~Russian
 * \brief Закрывает поток каталога
 *
 * \details Функция `wclosedir()` закрывает поток каталога.
 *          При успешном вызове функции также закрывается файловый дескриптор, связанный с директорией.
 *          Дескриптор открытого в прошлом потока каталога будет недоступен после данного вызова.
 *
 * \~
 * \b Support:

 IBM  |    GNU    | MinGW | MSVC/MSVS
------|-----------|-------|-----------
  ?   | This code |   x   | This code

 *
 */
int        _wclosedir(WDIR_t*);

/*!
 * \~English
 * \brief Opens a directory stream and returns a pointer to the stream.
 *        The stream is set to the first entry in the directory.
 *
 * \details After a successful call, the file descriptor of the open directory is used only within
 *          the implementation and should not be used in the application.
 *          The function sets the `close-on-exec` flag for the file descriptor that points to the directory.
 *
 * \~Russian
 * \brief Открывает поток каталога и возвращает указатель на поток.
 *        Поток устанавливается на первую запись в каталоге.
 *
 * \details После успешного вызова, файловый дескриптор открытой директории используется только
 *          внутри реализации и не должен использоваться в приложении.
 *          Функция  устанавливает флаг `close-on-exec` для файлового дескриптора, указывающего на директорию.
 *
 * \~
 * \b Support:

 IBM  |    GNU    | MinGW | MSVC/MSVS
------|-----------|-------|-----------
  ?   | This code |   x   | This code

 *
 */
WDIR_t    *_wopendir(const wchar_t*);

/*!
 * \~English
 * \brief Reads the directory stream
 *
 * \details It reads the directory stream, returns a pointer to the `wdirent_t` structure,
 *          which represents the next element in the catalog stream.
 *          The function returns `NULL` when the last record in the directory stream is reached
 *          or if an error occurred.
 *
 * \~Russian
 * \brief Читает поток каталога
 *
 * \details Читает поток каталога, возвращает указатель на структуру `wdirent_t`, представляющую
 *          следующий элемент в потоке каталога.
 *          Функция возвращает `NULL` по достижении последней записи в потоке каталога или если
 *          произошла ошибка.
 *
 * \~
 * \b Support:

 IBM  |    GNU    | MinGW | MSVC/MSVS
------|-----------|-------|-----------
  ?   | This code |   x   | This code

 *
 */
wdirent_t *_wreaddir(WDIR_t*);

/*!
 * \~English
 * \brief Reads the directory stream extended
 *
 * \details The function `wreaddir_r()` is a reentrant version.
 *          It reads the next entry from the open catalog stream and returns it in the created call buffer
 *          pointed to by the second parameter of the function.
 *          The pointer to the returned element is placed in the third parameter of the function,
 *          if the end of the directory stream is reached, `NULL` is returned instead of the value.
 *
 * \~Russian
 * \brief Читает поток каталога, расширенная функция
 *
 * \details Функция `wreaddir_r()`является реентерабельной версией.
 *          Она читает следующую запись из открытого потока каталога и возвращает её в созданном
 *          вызывающим буфере, на который указывает второй параметр функции.
 *          Указатель на возвращаемый элемент помещается в третий параметр функции,
 *          если достигнут конец потока каталога, то возвращается `NULL` вместо значения.
 *
 * \~
 * \b Support:

 IBM  |    GNU    | MinGW | MSVC/MSVS
------|-----------|-------|-----------
  ?   | This code |   x   | This code

 *
 */
int        _wreaddir_r(WDIR_t*, wdirent_t*, wdirent_t**);

/*!
 * \~English
 * \brief Reads the directory stream callBack
 *
 * \param wchar_t: - directory path
 * \param long: - options, valid `DIRENTRYSIZE`, `DIRNOROOT`, `DIRNODIR` bit mask set: \ref wreaddir_cb_opt
 * \param wdir_cb: - callback function, see \ref wdir_cb
 * \param void: - user data
 *
 * \~
 * \b Support:

 IBM       |    GNU    |   MinGW   | MSVC/MSVS
-----------|-----------|-----------|-----------
 This code | This code | This code | This code

 *
 * \b Table flags compatible:

     FLAGS    | GNU | MinGW  | MSVC/MSVS | Description
--------------|-----|--------|-----------|-------------
 DIRENTRYSIZE |  x  | Always |  Always   | Calculate size of entry
 DIRNOROOT    |  x  |   x    |     x     | Skip root directory `.` and `..`
 DIRNODIR     |  x  |   x    |     x     | Skip all directory


 *
 * \b Example:
 * \snippet ./test/check_wchar2_MSVC.c Example use wreaddir_cb
 *
 * \b Example CallBack:
 * \snippet ./test/check_wchar2_MSVC.c Example declaration wreaddir CallBack
 *
 */
int        _wreaddir_cb(wchar_t*, long, wdir_cb, void*);

/*!
 * \~English
 * \brief Macro to set options value to function \ref _wreaddir_cb
 *
 * \param opt: - `long int` options variable
 * \param val: - option value, valid `DIRENTRYSIZE`, `DIRNOROOT`, `DIRNODIR`
 *
 *
 * \~
 * \b Support: `ALL`
 *
 */
#define    wreaddir_cb_opt(opt,val) ((opt) | (1L << (val)))

/*!
 * \~English
 * \brief Sets the beginning in the directory stream
 *
 * \details The `wrewinddir()` function flushes the current position of the stream
 *          to the beginning of the directory.
 *
 * \~Russian
 * \brief Устанавливает начало в потоке каталога
 *
 * \details Функция `wrewinddir()` сбрасывает текущее положение потока в начало каталога.
 *
 *
 * \~
 * \b Support:

 IBM       |    GNU    | MinGW | MSVC/MSVS
-----------|-----------|-------|-----------
 This code | This code |   x   | This code

 *
 */
void       _wrewinddir(WDIR_t*);

/*!
 * \~English
 * \brief Sets the position in the directory stream
 *
 * \details The \ref _wseekdir function sets the position in the directory stream from
 *          which the next call to \ref _wreaddir will begin.
 *          The position argument must be a value that is returned by the previously
 *          called \ref _wtelldir function.
 *
 * \~Russian
 * \brief Устанавливает позицию в потоке каталога
 *
 * \details Функция \ref _wseekdir устанавливает в потоке каталога позицию, с которой
 *          начнёт работу следующий вызов \ref _wreaddir().
 *          Аргумент позиции должен быть значением, которое возвращается ранее вызванной
 *          функцией \ref _wtelldir .
 *
 * \~
 * \b Support:

 IBM  |    GNU    | MinGW | MSVC/MSVS
------|-----------|-------|-----------
  ?   | This code |   -   | -

 *
 */
void       _wseekdir(WDIR_t*, long int);

/*!
 * \~English
 * \brief Returns the current position of the directory stream
 *
 * \details If successful, the `wtelldir()` function returns the current location in the directory stream.
 *          In case of an error, `-1` is returned, and the corresponding value of `errno` is set.
 *
 * \~Russian
 * \brief Возвращает текущее положение потока каталога
 *
 * \details При успешном выполнении функция `wtelldir()` возвращает текущее расположение в потоке каталога.
 *          В случае ошибки возвращается `-1`, и устанавливается соответствующее значение `errno`.
 *
 * \~
 * \b Support:

 IBM  |    GNU    | MinGW | MSVC/MSVS
------|-----------|-------|-----------
  ?   | This code |   -   | -

 *
 */
long int   _wtelldir(WDIR_t*);


/*! \~ */
/*! \cond NOTINDOC */

/* declaration from stdlib.h */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wredundant-decls"
void free(void*);
#pragma GCC diagnostic pop

/*! \endcond */

/*! \brief User free instance callback */
static inline void __attribute__((always_inline)) __wsfree(void *v)
{
    if (v)
    {
        void *x = *(void**)v;
        if (x)
        {
            free(x);
            // cppcheck-suppress unreadVariable
            x = ((void*)0);
        }
    }
}

#ifdef __cplusplus
}
#endif

/*! Other non standart macro */

/*! \cond NOTINDOC */

#if defined(__clang__)
#   pragma clang diagnostic ignored "-Wlanguage-extension-token"
#endif

/*! \brief auto check type macro */
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

#   define EV_ACCESS_ARG_3(_1,_2,_3) _waccess_selector(4,_1,_3,_2)
#   define EV_ACCESS_ARG_2(_1,_2) _waccess_selector(__wchar_type_id(_1),_1,_2,0)
#   define EV_ACCESS_ARG_1(_1) _waccess_selector(__wchar_type_id(_1),_1,0,0)
#   define EV_ACCESS_ARG_0(...)

#   define _waccess_macro(...) \
        __WEV(EV_ACCESS_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_BNAME_ARG_2(_1,_2) _wbasename_selector(_1,_2)
#   define EV_BNAME_ARG_1(_1) _wbasename_selector(__wchar_type_id(_1),_1)
#   define EV_BNAME_ARG_0(...)

#   define _wbasename_macro(...) \
        __WEV(EV_BNAME_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_BEXT_ARG_2(_1,_2) _wbaseext_selector(_1,_2)
#   define EV_BEXT_ARG_1(_1) _wbaseext_selector(__wchar_type_id(_1),_1)
#   define EV_BEXT_ARG_0(...)

#   define _wbaseext_macro(...) \
        __WEV(EV_BEXT_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

#   define EV_BDIR_ARG_3(_1,_2,_3) _wbasedir_selector(_1,_2,_3)
#   define EV_BDIR_ARG_2(_1,_2) _wbasedir_selector(__wchar_type_id(_1),_1,_2)
#   define EV_BDIR_ARG_1(_1) _wbasedir_selector(__wchar_type_id(_1),_1, 0)
#   define EV_BDIR_ARG_0(...)

#   define _wbasedir_macro(...) \
        __WEV(EV_BDIR_ARG_, __WEVFA(__VA_ARGS__))(__VA_ARGS__)

/*! \endcond */

/*! \paragraph usemacro Macro as convert type wchar_t to char */

/*!
 * \def wstocscvt(A,B,D)
 * \brief wchar_t* type to char[]
 * A char[]   - array name
 * B wchar_t* - source
 * D          - function return value if error
 */
#define wstocscvt(A,B,D)                                                                                           \
    size_t __WEV(sz,__LINE__); errno = 0;                                                                          \
    if (!(__WEV(sz,__LINE__) = _wcsrtombs(NULL, &(const wchar_t*){B}, 0, 0))) {                                    \
        errno = EILSEQ; return D;                                                                                  \
    }                                                                                                              \
    char __WEV(A,__LINE__)[(__WEV(sz,__LINE__) + 1)], * A = (char*)&__WEV(A,__LINE__);                             \
    if ((__WEV(sz,__LINE__) = _wcsrtombs(__WEV(A,__LINE__), &(const wchar_t*){B}, (__WEV(sz,__LINE__) + 1), 0))) { \
        __WEV(A,__LINE__)[(__WEV(sz,__LINE__))] = '\0';                                                            \
    }

/*!
 * \def wstocsncvt(A,B,C,D)
 * \brief wchar_t* type to char[] with size
 * A char[]   - array name
 * B wchar_t* - source
 * C size_t   - wchar_t* size
 * D          - function return value if error
 */
#define wstocsncvt(A,B,C,D)                                                                                         \
    char __WEV(A,__LINE__)[(C + 1 * sizeof(wchar_t))], * A = (char*)&__WEV(A,__LINE__); errno = 0;                  \
    if (!((C) = _wcsrtombs(__WEV(A,__LINE__), &(const wchar_t*){B}, (C * 2 + 1), 0))) {                             \
        errno = EILSEQ; return D;                                                                                   \
    }                                                                                                               \
    __WEV(A,__LINE__)[(C)] = '\0'

/*!
 * \def wstrtocscvt(A,B,D)
 * \brief string_ws type to char[]
 * this struct defined on top of this file
 * A char[]     - array name
 * B string_ws* - source
 * D            - function return value if error
 */
#define wstrtocscvt(A,B,D)                                                                                          \
    size_t __WEV(sz,__LINE__); errno = 0;                                                                           \
    char __WEV(A,__LINE__)[(B->sz + 1 * sizeof(wchar_t))], * A = (char*)&__WEV(A,__LINE__);                         \
    if (!(__WEV(sz,__LINE__) = _wcsrtombs(__WEV(A,__LINE__), &(const wchar_t*){B->str}, (B->sz * 2 + 1), 0))) {     \
        errno = EILSEQ; return D;                                                                                   \
    }                                                                                                               \
    __WEV(A,__LINE__)[__WEV(sz,__LINE__)] = '\0'

/*! \paragraph redefsym Redefined 'symbols' libc functions */

/*! for osx Darwin
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
#      define access u8waccess
#   else
#      define mkdir _wmkdir_macro
#      define remove _wremove_macro
#      define rename _wrename_macro
#      define stat _wstat_macro
#      define access _waccess_macro
#      define fopen _wfopen_macro
#      define access _waccess_macro
#      define basename(A) (__WSTR *) _wbasename_macro(A)
#      define dirname(A)  (__WSTR *) _wbasedir_macro(A)
#      define baseext(A)  (__WSTR *) _wbaseext_macro(A)
#   endif
#endif

/*! \cond NOTINDOC */

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

#define waccess _waccess_macro
#define waccess_w _waccess
#define waccess_s _waccess_s
#define waccess_ws _waccess_ws

#define wbasename _wbasename_macro
#define wbasename_w _wbasename
#define wbasename_ws _wbasename_ws

#define wbaseext _wbaseext_macro
#define wbaseext_w _wbaseext
#define wbaseext_ws _wbaseext_ws

#define wbasedir _wbasedir_macro
#define wbasedir_w _wbasedir
#define wbasedir_ws _wbasedir_ws
#define wpathnormalize _wpathnormalize
#define wpathnormalize_ws _wpathnormalize_ws

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
#define printf _printf

/*! Tests compatibility only */
#define _wcprint wcprint
#define _wcsregexp wcsregexp
#define _wcstocscmp wcstocscmp
#define _u8stowcs u8stowcs
#define _wcstou8s wcstou8s
#define _u8wfopen u8wfopen
#define _u8wmkdir u8wmkdir
#define _u8waccess u8waccess
#define _u8wremove u8wremove
#define _u8wrename u8wrename
#define _u8wstat u8wstat
#define _u8sverify u8sverify

#define wclosedir _wclosedir
#define wopendir _wopendir
#define wreaddir _wreaddir
#define wreaddir_r _wreaddir_r
#define wreaddir_cb _wreaddir_cb
#define wrewinddir _wrewinddir
#define wseekdir _wseekdir
#define wtelldir _wtelldir

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

#define wcstod _wcstod
#define wcstof _wcstof
#define wcstold _wcstold
#define wcstol _wcstol
#define wcstoll _wcstoll
#define wcstoul _wcstoul
#define wcstoull _wcstoull
#define wcstoimax _wcstoimax
#define wcstoumax _wcstoumax

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
#define wcsftime _wcsftime
#define wcsptime _wcsptime
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

/*! \endcond */

#endif
