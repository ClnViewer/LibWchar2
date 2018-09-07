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
  * \file string_s.h
  * \par LibWchar2 (char*) extension interface
  * \brief This extension interface LibWchar2 library to use (char*) all 'wstring_*' methods.
  * \details Use wchar2.h or wchar2ext.h instead
  *
  * \see https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html
  * \see https://clnviewer.github.io/LibWchar2/docs/html/pages.html
  *
  * \author     `PS`
  * \copyright  `MIT` 2018 (c) `PS`
  * \see https://clnviewer.github.io/LibWchar2/ [`Web Home`]
  * \see https://github.com/ClnViewer/LibWchar2 [`Git Home`]
  *
  */

#ifndef STRING_S_H
#define STRING_S_H

#if !defined(__CHKRET)
#   if defined(__GNUC__) && (__GNUC__ >= 4)
#      define __CHKRET __attribute__ ((warn_unused_result))
#   elif defined(_MSC_VER) && (_MSC_VER >= 1700)
#      define __CHKRET _Check_return_
#   else
#      define __CHKRET
#   endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Base string structure */
typedef struct
{
    char    *str; /**<  wide string pointer */
    size_t   sz;  /**<  size wide string */

} string_s;

/*! \~
 *  \brief CallBack for \ref string_split_cb
 *  \param char: - splitting part from string
 *  \param size_t: - Length of string part
 *  \param long: - counter
 *  \param void: - user data
 */
typedef void (*csplit_cb)(char*, size_t, long, void*);

/*!
 * \brief Library current version
 */

void      string_free(string_s *restrict);
int       string_isempty(const char *restrict s, int);

size_t    string_alloc(string_s *restrict, size_t);
size_t    string_appends_(string_s*, ...);
#define   string_appends(A,...) string_appends_(A,__VA_ARGS__,NULL)
size_t    string_append(string_s*, const char *restrict, size_t);
#define   string_append_auto(A,B) string_append(A,B,0U)
size_t    string_format(string_s*, const char *restrict, ...);

long      string_split_cb(const string_s*, char, csplit_cb, void*);

string_s  string_trunc(const char*, int);
size_t    string_trunc_alloc(string_s *restrict, const char*, int);

__CHKRET
char    * string_timeformat(const char *restrict, size_t, const char *restrict, const char *restrict);
__CHKRET
char    * string_timeformat_s(const string_s *restrict, const char *restrict, const char *restrict);

static inline void __attribute__((always_inline)) __autostring(void *v)
{
    if (v)
    {
        string_s *x = (string_s*)(*(void**)v);
        if (x)
            string_free(x);
    }
}

#endif
