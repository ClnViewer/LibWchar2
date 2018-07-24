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

#   if defined(_MSC_VER)
typedef unsigned short mode_t;
#   elif defined(BUILD_MINGW)
#      include <stdlib.h>
#      include <sys/stat.h>
int _wmkdir(const wchar_t*);
#   endif

#else
#   include <stdlib.h>
#   include <sys/stat.h>
#   include "libwchar.h"

#endif

#if defined(OS_WIN)

static int __mkdirwp(const wchar_t *w)
{
    wchar_t __AUTO *p = NULL;
    errno = 0;

    if (!w)
    {
        errno = EINVAL;
        return -1;
    }

#   if defined(_MSC_VER)
    __try
    {
#   endif
        if (_wmkdir(w) == -1)
        {
            switch (errno)
            {
            case EEXIST:
            {
                return 0;
            }
            case ENOENT:
            {
                break;
            }
            default:
            {
                return -1;
            }
            }
            do
            {
#               if defined(_MSC_VER)
                __try
                {
#               endif

                if ((p = _wbasedir(w, 0)) == NULL)
                {
                    break;
                }
                if (__mkdirwp(p) == 0)
                    return _wmkdir(w);

#               if defined(_MSC_VER)
                }
                __except(__seh_except())
                {
                    if (p != NULL)
                        free(p);

                    errno = EFAULT;
                    return -1;
                }
#               endif
            }
            while (0);

            errno = ENOENT;
            return -1;
        }
        errno = 0;
        return errno;

#   if defined(_MSC_VER)
    }
    __finally
    {
        if (p != NULL)
            free(p);
    }
#   endif
}

int _wmkdir_s(const wchar_t *w, size_t sz, mode_t m)
{
    (void) sz;
    (void) m;
    return __mkdirwp(w);
}

int _wmkdir_ws(const string_ws *ws, mode_t m)
{
    (void) m;
    return __mkdirwp(ws->str);
}

int u8wmkdir(const wchar_t *w, mode_t m)
{
    /*
        TODO: char implement MSVC version
    */
    (void) w;
    (void) m;
    errno = ENOSYS;
    return -1;
}

#else

static int __mkdirp(const char *s, mode_t m)
{
    char __AUTO *p = NULL;
    errno = 0;

    if (!s)
    {
        errno = EINVAL;
        return -1;
    }

    if (mkdir(s, m) == -1)
    {
        switch (errno)
        {
        case EEXIST:
        {
            return 0;
        }
        case ENOENT:
        {
            break;
        }
        default:
        {
            return -1;
        }
        }
        do
        {
            if ((p = (char*) _wbasedir_selector(3, (const void*)s, 0)) == NULL)
            {
                break;
            }
            if (__mkdirp(p, m) == 0)
                return mkdir(s, m);

        }
        while (0);

        errno = ENOENT;
        return -1;
    }
    errno = 0;
    return errno;
}

int u8wmkdir(const wchar_t *wc, mode_t m)
{
    char __AUTO *b = NULL;

    if (
        ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL) ||
        (wcstou8s(b, wc) <= 0)
    )
    {
        return -1;
    }

    return __mkdirp(b, m);
}

int _wmkdir(const wchar_t *ws, mode_t m)
{
    wstocscvt(b, ws, -1);
    return __mkdirp(b, m);
}

int _wmkdir_s(const wchar_t *ws, size_t sz, mode_t m)
{
    wstocsncvt(b, ws, sz, -1);
    return __mkdirp(b, m);
}

int _wmkdir_ws(const string_ws *ws, mode_t m)
{
    wstrtocscvt(b, ws, -1);
    return __mkdirp(b, m);
}

int _wmkdir_selector(int sel, const void *w, size_t sz, mode_t m)
{
    switch(sel)
    {
    case 1:
    {
        return _wmkdir((const wchar_t*)w, m);
    }
    case 2:
    {
        return _wmkdir_ws((const string_ws*)w, m);
    }
    case 3:
    {
        return __mkdirp((const char*)w, m);
    }
    case 4:
    {
        return _wmkdir_s((const wchar_t*)w, sz, m);
    }
    default:
    {
        errno = EFAULT;
        return -1;
    }
    }
}

#endif
