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
#   include <sys/stat.h>
#   include "libwcharext.h"

#else
#   include <unistd.h>
#   include <sys/stat.h>
#   include <sys/types.h>
#   include "libwchar.h"

#endif

#if defined(OS_WIN)

static access_e __waccess(const wchar_t *s, const char *c, int m)
{
    access_e ret = ISERROR;
    do
    {
        struct _stat sb = {0};
        if (
            ((!s) && (!c))                ||
            ((s) && (_wstat(s, &sb) < 0)) ||
            ((c) && (_stat(c, &sb) < 0))
        )
        {
            break;
        }
        else if (((sb.st_mode) & _S_IFDIR) == _S_IFDIR)
        {
            ret = ISDIR;
        }
        else if (((sb.st_mode) & _S_IFREG) == _S_IFREG)
        {
            ret = ISFIL;
        }
        else
        {
            break;
        }
        switch (m)
        {
        case 0:
        {
            if (
                (((sb.st_mode) & _S_IREAD)  != _S_IREAD)  ||
                (((sb.st_mode) & _S_IWRITE) != _S_IWRITE) ||
                (((sb.st_mode) & _S_IEXEC)  != _S_IEXEC)
            )
            {
                ret = ISERROR;
            }
            break;
        }
        case 1:
        {
            if (((sb.st_mode) & _S_IEXEC) != _S_IEXEC)
            {
                ret = ISERROR;
            }
            break;
        }
        case 2:
        {
            if (((sb.st_mode) & _S_IWRITE) != _S_IWRITE)
            {
                ret = ISERROR;
            }
            break;
        }
        case 4:
        {
            if (((sb.st_mode) & _S_IREAD) != _S_IREAD)
            {
                ret = ISERROR;
            }
            break;
        }
        case 6:
        {
            if (
                (((sb.st_mode) & _S_IREAD)  != _S_IREAD) ||
                (((sb.st_mode) & _S_IWRITE) != _S_IWRITE)
            )
            {
                ret = ISERROR;
            }
            break;
        }
        default:
        {
            ret = ISERROR;
            break;
        }
        }

    }
    while (0);

    return ret;
}

access_e _waccess_s_(const wchar_t *w, size_t osz, int m)
{
    (void) osz;
    return __waccess(w, NULL, m);
}

access_e _waccess_ws(const string_ws *ws, int m)
{
    return __waccess(ws->str, NULL, m);
}

access_e u8waccess(const wchar_t *w, int m)
{
    char __AUTO *b  = NULL;

#   if defined(_MSC_VER)
    __try
    {
#   endif
        if (
            ((b = calloc(1, wcstou8s(NULL, w) + 1)) == NULL) ||
            (wcstou8s(b, w) <= 0)
        )
        {
            return -1;
        }

        return __waccess(NULL, b, m);

#  if defined(_MSC_VER)
    }
    __finally
    {
        if (b != NULL)
            free(b);
    }
#  endif
}

#else

static access_e __access(const char *s, int m)
{
    access_e ret = ISERROR;
    do
    {
        struct stat sb;
        memset((void*)&sb, 0, sizeof(struct stat));

        if (stat(s, &sb) < 0)
        {
            break;
        }
        else if (S_ISDIR(sb.st_mode))
        {
            ret = ISDIR;
        }
        else if (S_ISLNK(sb.st_mode))
        {
            ret = ISLNK;
        }
        else if (S_ISREG(sb.st_mode))
        {
            ret = ISFIL;
        }
        else
        {
            break;
        }
        switch (m)
        {
        case 0:
        {
            if (
                (!((sb.st_mode) & S_IRUSR)) ||
                (!((sb.st_mode) & S_IWUSR))
            )
            {
                ret = ISERROR;
            }
            break;
        }
        case 1:
        {
            if (!((sb.st_mode) & S_IXUSR))
            {
                ret = ISERROR;
            }
            break;
        }
        case 2:
        {
            if (!((sb.st_mode) & S_IWUSR))
            {
                ret = ISERROR;
            }
            break;
        }
        case 4:
        {
            if (!((sb.st_mode) & S_IRUSR))
            {
                ret = ISERROR;
            }
            break;
        }
        case 6:
        {
            if (
                (!((sb.st_mode) & S_IRUSR)) ||
                (!((sb.st_mode) & S_IWUSR)) ||
                (!((sb.st_mode) & S_IXUSR))
            )
            {
                ret = ISERROR;
            }
            break;
        }
        default:
        {
            ret = ISERROR;
            break;
        }
        }

    }
    while (0);

    return ret;
}

access_e u8waccess(const wchar_t *ws, int m)
{
    char __AUTO *b = NULL;

    if (
        ((b = calloc(1, wcstou8s(NULL, ws) + 1)) == NULL) ||
        (wcstou8s(b, ws) <= 0)
    )
    {
        return -1;
    }

    return __access(b, m);
}

access_e _waccess(const wchar_t *o, int m)
{
    wstocscvt(ob, o, -1);
    return __access(ob, m);
}

access_e _waccess_s(const wchar_t *o, size_t osz, int m)
{
    wstocsncvt(ob, o, osz, -1);
    return __access(ob, m);
}

access_e _waccess_ws(const string_ws *o, int m)
{
    wstrtocscvt(ob, o, -1);
    return __access(ob, m);
}

access_e _waccess_selector(int sel, const void *w, size_t osz, int m)
{
    switch(sel)
    {
    case 1:
    {
        return _waccess((const wchar_t*)w, m);
    }
    case 2:
    {
        return _waccess_ws((const string_ws*)w, m);
    }
    case 3:
    {
        return __access((const char*)w, m);
    }
    case 4:
    {
        return _waccess_s((const wchar_t*)w, osz, m);
    }
    default:
    {
        errno = EFAULT;
        return -1;
    }
    }
}

#endif
