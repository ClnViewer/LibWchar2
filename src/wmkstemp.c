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
#   include <stdio.h>
#   if defined(_MSC_VER)
#      include <io.h>
#      include <share.h>
#      include <windows.h>
#   endif

#else
#   include "libwchar.h"
#   include <stdio.h>
#   include <stdlib.h>

#endif

#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TMPS_MIN (62 * 62 * 62)

int wmkstemp(wchar_t *wtmpl)
{
    static const wchar_t dict[] = __WS("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    size_t i, wlen, bsz, tmpssz;

#if defined(TMP_MAX)
#   if TMPS_MIN < TMP_MAX
    tmpssz = TMP_MAX;
#   else
    tmpssz = TMPS_MIN;
#   endif
#else
    tmpssz = TMPS_MIN;
#endif

    if (
        (!wtmpl) ||
        ((wlen = _wcslen(wtmpl)) < 6) ||
        (_wcscmp(&wtmpl[(wlen - 6)], __WS("XXXXXX")))
    )
    {
        errno = EINVAL;
        return -1;
    }

#   if defined(_MSC_VER)
    bsz = (256 * 2);
    if (wlen >= bsz)
    {
        errno = EOVERFLOW;
        return -1;
    }
#   else
    bsz = (wlen + 1);
#   endif

    do
    {
        unsigned long long rnd_tb, res = 0ULL;
        wchar_t *pw;
#       if defined(_MSC_VER)
        errno_t err;
        char ctmpl[(256 * 2)];
#       else
        char ctmpl[((wlen + 1) * 2)];
#       endif
        time_t t = time(NULL);

#       if defined(_MSC_VER)
        rnd_tb = (unsigned long long)GetCurrentThreadId();
        res += (unsigned long)t ^ rnd_tb;
#       else
        rnd_tb = (unsigned long long)rand();
        res += (unsigned long)t ^ rnd_tb;
#       endif

        pw = &wtmpl[(wlen - 6)];

        for (i = 0U; i < tmpssz; res += 7777, ++i)
        {
            int fd;
            size_t n;
            unsigned long long v = res;

            for (n = 0U; n < 6U; n++)
            {
                pw[n] = (wchar_t)dict[(v % 62)];
                v /= 62;
            }

            if (!wstring_wstocs((char*)&ctmpl, bsz, wtmpl, wlen))
            {
                errno = EFAULT;
                return -1;
            }

            errno = 0;

#           if defined(_MSC_VER)
            if (!(err = _sopen_s(&fd, ctmpl, O_RDWR | O_CREAT | O_EXCL, _SH_DENYRW, _S_IREAD | _S_IWRITE)))
            {
                errno = 0;
                return fd;
            }
            else if (err != EEXIST)
            {
                errno = err;
                return -1;
            }
#           else
#              if defined(BUILD_MINGW)
            if ((fd = open(ctmpl, O_RDWR | O_CREAT | O_EXCL, _S_IREAD | _S_IWRITE)) >= 0)
#              else
            if ((fd = open(ctmpl, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) >= 0)
#              endif
            {
                errno = 0;
                return fd;
            }
            else if (errno != EEXIST)
            {
                return -1;
            }
#           endif
        }
    }
    while (0);

    errno = EEXIST;
    return -1;
}
