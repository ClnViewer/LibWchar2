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

#include "libbuild.h"

#if defined(OS_WIN)
#   include "libwcharext.h"

#   if defined(BUILD_MINGW)
#      include <stdio.h>
#      include <unistd.h>
int fileno(FILE *stream);
#   endif

#else
#   define _POSIX_C_SOURCE 200809L
#   include <stdio.h>
#   include <unistd.h>
#   include "libwchar.h"

#endif

#if (defined(BUILD_MINGW) || !defined(OS_WIN))
#   define  __wwrite(A) if (write(fd, (void*)&(A), sizeof(wchar_t)) <= 0) { break; }
#elif defined(_MSC_VER)
#   define  __wwrite(A) putwchar(A)
#endif

void wcprint(wchar_t *w)
{
    wchar_t *p = w;
#   if (defined(BUILD_MINGW) || !defined(OS_WIN))
    int fd = fileno(stdout);
#   endif

    while(*p)
    {
        __wwrite(*p++);
    }
}
