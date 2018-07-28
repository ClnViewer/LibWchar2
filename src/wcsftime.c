
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

#include "libwchar.h"
#include <sys/cdefs.h>
#include <time.h>

/*!
 * \brief Convert date and time to a wide-character string.
 *
 * \details This is the wide-character counterpart of strftime(). So that we do not
 * have to duplicate the code of strftime(), we convert the format string to
 * multibyte, call strftime(), then convert the result back into wide
 * characters.
 */

size_t _wcsftime(wchar_t *w, size_t sz, const wchar_t *fmt, const void *v)
{
    int bsz = (sz + 1 * sizeof(wchar_t));
    const struct tm *ptm = (const struct tm*)v;

    if ((!w) || (!fmt) || (!sz) || (!v))
    {
        errno = EINVAL;
        return 0U;
    }

    do
    {
        char    fb[bsz];
        char    cb[sz];
        size_t  osz = 0U;
        errno = 0;

        if (
            (!wstring_wstocs(fb, bsz, fmt, 0))    ||
            (!(osz = strftime(cb, sz, fb, ptm)))  ||
            (!(osz = wstring_cstows(w, sz, cb, osz)))
           ) { break; }

        return osz;

    } while (0);

    return 0U;
}
