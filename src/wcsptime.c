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

#include "libbuild.h"

#if defined(OS_WIN)
#   include "libwcharext.h"
const char * _strptime(const char*, const char*, struct tm*);
#   include "strptime_w32.c"
#   define strptime _strptime

#else
#   include "libwchar.h"
#   include <sys/cdefs.h>

#endif

#include <time.h>

/*!
 * \brief Convert a wide-character string representation of time to a time tm structure.
 *
 * \details The `wcsptime()` function equivalent to `strptime()` function.
 * The `strptime()` function it converts the character string pointed to by s, preserving the values in the tm structure,
 * describes the time as a component, broken-down time, according to the format specified in the format.
 */

wchar_t * _wcsptime(const wchar_t *w, const wchar_t *fmt, void *v)
{
    int bsz, fsz;
    struct tm *ptm = (struct tm*)v;

    if ((!w) || (!fmt) || (!v))
    {
        errno = EINVAL;
        return NULL;
    }
    if (
        (!(bsz = _wcslen(w))) ||
        (!(fsz = _wcslen(fmt)))
    )
    {
        errno = EINVAL;
        return NULL;
    }

    fsz = ((fsz + 1) * sizeof(wchar_t));
    bsz = ((bsz + 1) * sizeof(wchar_t));

    memset(v, 0, sizeof(struct tm));

    do
    {
#       if defined(_MSC_VER)
        char *fb = NULL, *cb = NULL;
        __try
        {
            if (
                ((fb = calloc(1, fsz)) == NULL) ||
                ((cb = calloc(1, bsz)) == NULL)
            )
            {
                break;
            }
#       else
        char    fb[fsz], cb[bsz];
#       endif

            errno = 0;

            if (
                (!wstring_wstocs(fb, fsz, fmt, 0)) ||
                (!wstring_wstocs(cb, bsz, w,   0))
            )
            {
                break;
            }

            (void) strptime(cb, fb, ptm);
            return NULL;

#       if defined(_MSC_VER)
        }
        __finally
        {
            if (fb != NULL)
                free(fb);
            if (cb != NULL)
                free(cb);
        }
#       endif

    }
    while (0);

    return (wchar_t*)&__WS("");
}
