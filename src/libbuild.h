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

#ifndef WCHAR2BUILD_LOCAL_H
#define WCHAR2BUILD_LOCAL_H

#if ( \
        defined(_WIN32) || defined(__WIN32__) || defined(_Windows) || \
        defined(_WIN64) || defined(__WIN64__) || \
        defined(__CYGWIN__) || defined(__MINGW32__) || defined(__MINGW64__))

#   define OS_WIN
#   if (defined(_WIN32) || defined(__WIN32__) || defined(_Windows))
#       define OS_WIN32
#   elif (defined(_WIN64) || defined(__WIN64__))
#       define OS_WIN64
#   else
#       define OS_NONE
#   endif

#   if  (defined(OS_WIN32) && defined(_MSC_VER))
#       define BUILD_MSVC32
#   elif  (defined(OS_WIN64) && defined(_MSC_VER))
#       define BUILD_MSVC64
#   elif  (defined(OS_WIN32) && defined(__CYGWIN__))
#       define BUILD_CYGWIN32
#   elif  (defined(OS_WIN64) && defined(__CYGWIN__))
#       define BUILD_CYGWIN64
#   elif  (defined(OS_WIN32) && defined(__MINGW32__))
#       define BUILD_MINGW32
#   elif  (defined(OS_WIN64) && defined(__MINGW64__))
#       define BUILD_MINGW64
#   endif

#endif

#if defined(_MSC_VER)
/* #define _CRT_SECURE_NO_WARNINGS (devel suppress) */
#endif

#endif
