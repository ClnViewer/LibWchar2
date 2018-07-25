
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
        wcstoimax Convert wide-character string to integer (? who is this)
        wcscoll   Locale-specific wide-character string compare
        wcscpy    Copy wide-character string
        wcscspn   Count wide characters not in string
        wcsftime  Convert date and time to a formatted wide-character string
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

#define __WS(x) __WS_(x) /**< static string to wide type macro */
#define __WSTR wchar_t   /**< defenition wchar_t string macro */
#define __WSTRFREE __attribute__((cleanup(__wsfree))) __WSTR /**< auto free wchar_t string macro */
#define __WSTR_FMT  "ls" /**< print format wchar_t string macro */
#define __WCHAR_FMT "lc" /**< print format wchar_t char macro */
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
typedef struct {
    wchar_t *str; /**<  wide string pointer */
    size_t   sz;  /**<  size wide string */

} string_ws;

/*! \brief enumeration for return waccess function */
typedef enum {
    ISERROR = -1, /**<  Error check */
    ISUNK   =  0, /**<  is a Unknown */
    ISFIL   =  1, /**<  is a Regular file */
    ISLNK   =  2, /**<  is a Symbolic link */
    ISDIR   =  3  /**<  is a Directory */
} access_e;

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
           * \brief Ttest for lowercase wide character
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

/*! \par Other non standart functions */

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
           * \param size: a pointer to integer where the matching lenght is stored
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
           *  \brief Covert utf-8 char* to wchar_t*
           *  wchar_t*          - output
           *  const char*       - input
           *  return size_t     - size
           *
           *  \note function u8stowcs required free result
           */
size_t    u8stowcs(wchar_t*, const char*);

          /*!
           *  \brief Convert wchar_t* to utf-8 char*
           *  char*             - output
           *  const wchar_t*    - input
           *  return size_t     - size
           *
           *  \note function wcstou8s required free result
           */
size_t    wcstou8s(char*, const wchar_t*);

          /*!
           *  \brief Verify char* to utf-8 valid string
           *  const char* - input
           *  int (bool)  - output
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
size_t    _vfprintf(FILE *restrict, const char *restrict, va_list)
                __attribute__((__nonnull__, __format__(__printf__, 2, 0)));

          /*! \brief Write formatted data from variable argument list to sized buffer */
size_t    _vsnprintf(char *restrict, size_t, const char *restrict, va_list)
                __attribute__((__format__(__printf__, 3, 0)));

          /*! \brief Write to stream char format variable arguments */
size_t    _fprintf(FILE *restrict, const char *restrict, ...)
                __attribute__((__nonnull__, __format__(__printf__, 2, 0)));

          /*! \brief Write to stdout char format variable arguments */
size_t    _printf(const char *restrict fmt, ...)
                __attribute__((__nonnull__, __format__(__printf__, 1, 0)));

          /*! \brief Format variable arguments list */
size_t    _snprintf(char *restrict, size_t, const char *restrict, ...)
                __attribute__((__format__(__printf__, 3, 0)));

          /*!
           * \brief Write to stream wide character format variable argument list
           *
           * - \subpage wprintf
           */
size_t    _vfwprintf(FILE *restrict, const wchar_t *restrict, va_list)
                /* __attribute__((__nonnull__, __format__(__wprintf__, 2, 0))) */ ;

          /*!
           * \brief Write formatted data from variable argument list to sized buffer
           *
           * - \subpage wprintf
           */
size_t    _vswprintf(wchar_t *restrict, size_t, const wchar_t *restrict, va_list)
                /* __attribute__((__format__(__wprintf__, 3, 0))) */ ;

          /*!
           * \brief Write to stream wide character format variable arguments
           *
           * - \subpage wprintf
           */
size_t    _fwprintf(FILE *restrict, const wchar_t *restrict, ...)
                /* __attribute__((__nonnull__, __format__(__wprintf__, 2, 0))) */ ;

          /*!
           * \brief Write formatted wide character output
           *
           * - \subpage wprintf
           */
size_t    _swprintf(wchar_t *restrict, size_t, const wchar_t *restrict, ...)
                /* __attribute__((__format__(__wprintf__, 3, 0))) */ ;

          /*!
           * \brief Write formatted wide character to `stdout` `IO`
           *
           * - \subpage wprintf
           */
size_t    _wprintf(const wchar_t *restrict fmt, ...)
                /* __attribute__((__format__(__wprintf__, 1, 0))) */ ;

          /*! \brief Write a wide character string to a file or stream */
int       _fputws(const wchar_t *restrict, FILE *restrict);
          /*! \brief Write a wide character to a file or stream */
wchar_t   _fputwc(wchar_t, FILE *restrict);

          /*!
           *  \paragraph Open file stream
           *  \note The wfopen* function opens the file whose name is the string pointed
           *        to by pathname and associates a stream with it, standart returned.
           *
           * - \subpage wfopen
           */

          /*! \brief Open file stream, accepts file name and mode as wide characters */
FILE    * _wfopen(const wchar_t*, const wchar_t*)
                __attribute__((warn_unused_result));
          /*! \brief Same as wfopen, include size file name variable */
FILE    * _wfopen_s(const wchar_t*, size_t, const wchar_t*)
                __attribute__((warn_unused_result));
          /*! \brief Same as wfopen, file name as structure string_ws */
FILE    * _wfopen_ws(const string_ws*, const wchar_t*)
                __attribute__((warn_unused_result));
          /*! \brief Automatic type selector for wfopen* functions */
FILE    * _wfopen_selector(int, const void*, size_t, const void*)
                __attribute__((warn_unused_result));

          /*!
           *  \brief Open file stream, convert file name from wide characters to UTF-8
           *  \attention function u8wfopen required free result
           */
FILE    * u8wfopen(const wchar_t*, const wchar_t*)
                __attribute__((warn_unused_result));

          /*!
           *  \paragraph Statistic from file
           *  \note These functions return information about a file, standart returned
           *
           * - \subpage wstat
           */

          /*! \brief Statistic from file, wide char input */
int       _wstat(const wchar_t*, struct stat*);
          /*! \brief Statistic from file, wide char input with size */
int       _wstat_s(const wchar_t*, size_t, struct stat*);
          /*! \brief Statistic from file, struct string_ws input */
int       _wstat_ws(const string_ws*, struct stat*);
          /*! \brief Automatic type selector for wstat* functions */
int       _wstat_selector(int, const void*, size_t, const void*);
          /*! 
           *  \brief Statistic from file, convert file name from wide characters to UTF-8
           *  \attention function u8wstat required free result
           */
int       u8wstat(const wchar_t*, void*);

          /*!
           *  \paragraph Rename (move) file
           *  \note The wrename* function shall change the name or location of a file, standart returned
           *
           * - \subpage wrename
           */

          /*! \brief Rename file, wide char input */
int       _wrename(const wchar_t*, const wchar_t*);
          /*! \brief Rename file, wide char input with size */
int       _wrename_s(const wchar_t*, size_t, const wchar_t*, size_t);
          /*! \brief Rename file, struct string_ws input */
int       _wrename_ws(const string_ws*, const string_ws*);
          /*! \brief Automatic type selector for wrename* functions */
int       _wrename_selector(int, const void*, size_t, const void*, size_t);
          /*!
           *  \brief Rename file, convert file name from wide characters to UTF-8
           *  \attention function u8wrename required free result
           */
int       u8wrename(const wchar_t*, const wchar_t*);

          /*!
           *  \paragraph Delete (remove) file or directory
           *  \note Deletes a name from the file system, standart returned
           *
           * - \subpage wremove
           */

          /*! \brief Delete (remove) file, wide char input */
int       _wremove(const wchar_t*);
          /*! \brief Delete (remove) file, wide char input with size */
int       _wremove_s(const wchar_t*, size_t);
          /*! \brief Delete (remove) file, struct string_ws input */
int       _wremove_ws(const string_ws*);
          /*! \brief Automatic type selector for wremove* functions */
int       _wremove_selector(int, const void*, size_t);
          /*!
           *  \brief Delete (remove) file, convert file name from wide characters to UTF-8
           *  \attention function u8wremove required free result
           */
int       u8wremove(const wchar_t*);

          /*!
           *  \paragraph Make directory
           *  \note The equivalent of using the mkdir command with the -p switch for all functions _wmkdir*
           *        If the internal EXIST flag is received when creating the directory, return 0, otherwise
           *        the standard is returned.
           *
           * - \subpage wmkdir
           */

          /*! \brief Make directory, wide char input */
int       _wmkdir(const wchar_t*, mode_t);
          /*! \brief Make directory, wide char input with size */
int       _wmkdir_s(const wchar_t*, size_t, mode_t);
          /*! \brief Make directory, struct string_ws input */
int       _wmkdir_ws(const string_ws*, mode_t);
          /*! \brief Automatic type selector for wmkdir* functions */
int       _wmkdir_selector(int, const void*, size_t, mode_t);
          /*!
           *  \brief Make directory, convert file name from wide characters to UTF-8
           *  \attention function u8wmkdir required free result
           */
int       u8wmkdir(const wchar_t*, mode_t);


          /*!
           *  \paragraph Check permissions for a file or directory
           *  \note All waccess* function return extended status, see access_e enum value,
           *        if error return standart -1
           *
           * - \subpage waccess
           */

          /*! \brief Check permissions for a file or directory, wide char input */
access_e  _waccess(const wchar_t*, int);
          /*! \brief Check permissions for a file or directory, wide char input with size */
access_e  _waccess_s(const wchar_t*, size_t, int);
          /*! \brief Check permissions for a file or directory, struct string_ws input */
access_e  _waccess_ws(const string_ws*, int);
          /*! \brief Automatic type selector for wmkdir* functions */
access_e  _waccess_selector(int, const void*, size_t, int);
          /*!
           *  \brief Check permissions for a file or directory, convert file name from wide characters to UTF-8
           *  \attention function u8waccess required free result
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
           *  \attention all functions _wbasedir* required free result, use type __WSTRFREE for auto free
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
           *  \attention all functions _wpathnormalize* required free result, use type __WSTRFREE for auto free
           */

          /*! \brief Normalize slash from path, wide char input, int is string size, default 0 */
wchar_t * _wpathnormalize(const wchar_t*, int)
                __attribute__((warn_unused_result));
          /*! \brief Normalize slash from path, struct string_ws input */
wchar_t * _wpathnormalize_ws(const string_ws*)
                __attribute__((warn_unused_result));
          /*!
           *  \brief Normalize slash from path, convert file name from wide characters to UTF-8
           *  \attention function u8wpathnormalize required free result
           */
char *    u8wpathnormalize(const wchar_t*)
                __attribute__((warn_unused_result));


          /*!
           *  API use struct string_ws
           */

          /*!
           *  \paragraph Allocate memory functions
           */

          /*! \brief Memory free string, empty and clear struct string_ws */
void      wstring_free(string_ws *restrict);
          /*! \brief Memory allocation string, struct string_ws->str output */
size_t    wstring_alloc(string_ws *restrict, size_t);

          /*!
           *  \brief Converting string, wchar_t input, char allocate output
           *  \attention function wstring_wstocs_alloc required free result
           */
char    * wstring_wstocs_alloc(const wchar_t *restrict)
                __attribute__((warn_unused_result));

          /*!
           *  \brief Converting string, string_ws input, char allocate output
           *  \attention function wstring_swstocs_alloc required free result
           */
char    * wstring_swstocs_alloc(const string_ws *restrict)
                __attribute__((warn_unused_result));

          /*!
           *  \brief Converting string, char input, wchar_t allocate output
           *  \attention function wstring_cstows_alloc required free result
           */
wchar_t * wstring_cstows_alloc(const char *restrict)
                __attribute__((warn_unused_result));

          /*!
           *  \brief Converting string, string_ws input, length output
           *  \attention function wstring_cstows_alloc required free result
           */
size_t    wstring_cstows_ws_alloc(string_ws *restrict, const char *restrict);

          /*!
           *  \brief Append string, format vargs input, struct string_ws output
           *  \attention curent status: broken, if out data large 8192 byte!
           *             Now, fixing output buffer size 8192 byte for *nix version.
           *             For MinGW32 always fixing output buffer size 8192 byte.
           *             TODO: rewrite length detected for *nix
           */
size_t    wstring_format(string_ws*, const wchar_t *restrict, ...);

          /*! \brief Append string, wchar_t input, struct string_ws output */
size_t    wstring_append(string_ws*, const wchar_t *restrict, size_t);

          /*!
           *  \brief Append string, only wchar_t* args inputs, struct string_ws output
           *
           *  \note Do not use this function directly, first use the wstring_appends() macro,
           *        or end the last function's parameters with a value of NULL.
           *  \attention function wstring_appends_() required free result
           *
           */
size_t    wstring_appends_(string_ws*, ...);

          /*!
           *  \brief Macro to function wstring_appends_(), see notes
           */
#define   wstring_appends(A,...) wstring_appends_(A,__VA_ARGS__,NULL)

          /*! \brief Append string, char input, struct string_ws output */
size_t    wstring_append_cvt(string_ws*, const char *restrict, size_t);

          /*!
           *  \paragraph User buffer memory function
           */

          /*! \brief Converting string, char input, wchar_t array output, to alloc buffer write */
size_t    wstring_cstows(wchar_t [], size_t, const char *restrict, size_t);
          /*! \brief Converting string, struct wchar_t input, char array output, to alloc buffer write */
size_t    wstring_wstocs(char [], size_t, const wchar_t *restrict, size_t);
          /*! \brief Converting string, struct string_ws input, char array output, to alloc buffer write */
size_t    wstring_wstocs_ws(char [], size_t, const string_ws *restrict);


          /*!
           *  \paragraph misc function
           */

          /*! \brief Check wchar_t input string is empty, bool return */
int       wstring_isempty(const wchar_t *restrict s, int);

          /*!
           *  \brief Truncation string, wchar_t input, struct string_ws return
           */
string_ws wstring_trunc(const wchar_t *ws, int);

          /*!
           *  \brief Truncation string, wchar_t input, return pointer to struct string_ws and lenght
           */
size_t    wstring_trunc_alloc(string_ws *restrict, const wchar_t*, int);

/*! \cond NOTINDOC */

/* declaration from stdlib.h */
void free(void*);

/*! \endcond */

          /*! \brief User free instance callback */
static inline void __attribute__((always_inline)) __wsfree(void *v) {
    if (v) { void *x = *(void**)v; if (x) { free(x); x = ((void*)0); }}
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
    if ((__WEV(sz,__LINE__) = _wcsrtombs(NULL, &(const wchar_t*){B}, 0, 0)) <= 0) {                                \
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
    if (((C) = _wcsrtombs(__WEV(A,__LINE__), &(const wchar_t*){B}, (C * 2 + 1), 0)) <= 0) {                         \
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
    if ((__WEV(sz,__LINE__) = _wcsrtombs(__WEV(A,__LINE__), &(const wchar_t*){B->str}, (B->sz * 2 + 1), 0)) <= 0) { \
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

/*! Tests compability only */
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

/*! \endcond */

#endif
