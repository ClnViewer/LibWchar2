
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
  * \file wchar2ext.h
  * \par LibWchar2 extension
  * \brief This extension LibWchar2 library to use Windows API compatible platform.
  *
  * \see https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html
  * \see https://clnviewer.github.io/LibWchar2/docs/html/pages.html
  *
  * \par Using and testing only MSVC/MSVS
  *
  * \author     `PS`
  * \copyright  `MIT` 2018 (c) `PS`
  * \see https://clnviewer.github.io/LibWchar2/ [`Web Home`]
  * \see https://github.com/ClnViewer/LibWchar2 [`Git Home`]
  *
  */

#ifndef WCHAR2EXT_MSVC_H
#define WCHAR2EXT_MSVC_H

#if defined(WCHAR2_LIBC_H)
#   error "Only one header include, wchar2.h or wchar2ext.h"
#endif

/*! \cond NOTINDOC */

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

#if (defined(_MSC_VER) && !defined(WCHAR2EXT_MSVC_ORIGIN))
#   if !defined(WCHAR2LIB_PRAGMA_ADD)
#     define WCHAR2LIB_PRAGMA_ADD 1
#     pragma comment(lib, "libwchar2ext.lib")
#   endif
#endif

#define __WS_(x) L##x
#define __WEV_(A,B) A ## B
#define __WEV(A,B)  __WEV_(A,B)
#define __WEVFA_(_11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N
#define __WEVFA(...) __WEVFA_(__VA_ARGS__, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

/*! \endcond */

#include <wctype.h>
#include <wchar.h>

#define __WS(x) __WS_(x) /**< static string to wide type macro */
#define __WSTR wchar_t   /**< defenition wchar_t string macro */
#define __WSTRFREE __attribute__((cleanup(__wsfree))) __WSTR /**< auto free wchar_t string macro */
#define __WSTR_FMT  "ls" /**< print format wchar_t string macro */
#define __WCHAR_FMT "lc" /**< print format wchar_t char macro */
#define __WCSZ(x) ((x->sz + 1) * sizeof(wchar_t)) /**< determine size string_ws macro */

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

void      wstring_free(string_ws *restrict);
void      wcprint(wchar_t *restrict);
void      wstring_free(string_ws *restrict);
int       wstring_isempty(const wchar_t *restrict s, int);

size_t    wstring_alloc(string_ws *restrict, size_t);
size_t    wstring_append_cvt(string_ws*, const char *restrict, size_t);
size_t    wstring_appends_(string_ws *dst, ...);
size_t    wstring_append(string_ws*, const wchar_t *restrict, size_t);
size_t    wstring_format(string_ws *dst, const wchar_t *restrict, ...);

string_ws wstring_trunc(const wchar_t *ws, int);
size_t    wstring_trunc_alloc(string_ws *restrict, const wchar_t*, int);

char    * wstring_wstocs_alloc(const wchar_t *restrict);
char    * wstring_swstocs_alloc(const string_ws *restrict);
wchar_t * wstring_cstows_alloc(const char *restrict);
size_t    wstring_cstows_ws_alloc(string_ws *restrict, const char *restrict);

size_t    wstring_wstocs(char [], size_t, const string_ws *restrict);
size_t    wstring_cstows(wchar_t [], size_t, const char *restrict);

size_t    u8stowcs(wchar_t*, const char*);
size_t    wcstou8s(char*, const wchar_t*);
int       u8sverify(const char*);

wchar_t * _wpathnormalize(const wchar_t*, int);
wchar_t * _wpathnormalize_ws(const string_ws*);
char *    u8wpathnormalize(const wchar_t*);

int       _wrename_s(const wchar_t*, size_t, const wchar_t*, size_t);
int       _wrename_ws(const string_ws*, const string_ws*);
int       u8wrename(const wchar_t*, const wchar_t*);

int       _wremove_s(const wchar_t*, size_t);
int       _wremove_ws(const string_ws*);
int       u8wremove(const wchar_t*);

int       _wmkdir_s(const wchar_t*, size_t, unsigned short);
int       _wmkdir_ws(const string_ws*, unsigned short);
int       u8wmkdir(const wchar_t*, unsigned short); /* Function not implemented */

access_e  _waccess_s_(const wchar_t*, size_t, int);
access_e  _waccess_ws(const string_ws*, int);
access_e  u8waccess(const wchar_t*, int);

int       _wstat_s_(const wchar_t*, size_t, void*);
int       _wstat_ws(const string_ws*, void*);
int       u8wstat(const wchar_t*, void*);

FILE    * _wfopen_s_(const wchar_t*, size_t, const char*);
FILE    * _wfopen_ws(const string_ws*, const char*);
FILE    * u8wfopen(const wchar_t*, const char*);

wchar_t * _wbasename(const wchar_t*);
wchar_t * _wbasename_ws(const string_ws*);
wchar_t * _wbaseext(const wchar_t*);
wchar_t * _wbaseext_ws(const string_ws*);
wchar_t * _wbasedir(const wchar_t*, int);
wchar_t * _wbasedir_ws(const string_ws*, int);

/*! \cond NOTINDOC */

#if !defined(WCHAR2EXT_MSVC_ORIGIN)

#define wstring_appends(A,...) wstring_appends_(A,__VA_ARGS__,NULL)

#define wpathnormalize _wpathnormalize
#define wpathnormalize_ws _wpathnormalize_ws

#define wrename(A,B) _wrename_s(A,0,B,0)
#define wrename_s _wrename_s
#define wrename_ws _wrename_ws

#define wremove(A) _wremove_s(A,0)
#define wremove_s _wremove_s
#define wremove_ws _wremove_ws

#define wmkdir(A,B) _wmkdir_s(A,0,0)
#define wmkdir_s _wmkdir_s
#define wmkdir_ws _wmkdir_ws

#define waccess(A,B) _waccess_s_(A,0,B)
#define waccess_s _waccess_s_
#define waccess_ws _waccess_ws

#define wbasename _wbasename
#define wbasename_ws _wbasename_ws
#define wbaseext _wbaseext
#define wbaseext_ws _wbaseext_ws
#define wbasedir _wbasedir
#define wbasedir_ws _wbasedir_ws

#define wfopen(A,B) _wfopen_s_(A,0,B)
#define wfopen_s(A,B,C) _wfopen_s_(A,B,C)
#define wfopen_ws _wfopen_ws

#define wstat_s _wstat_s_
#define wstat_ws _wstat_ws
#define wstat(A,B) _wstat_s_(A,0,B)

#endif

/*! \endcond */

#endif
