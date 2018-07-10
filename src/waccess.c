
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

#include <unistd.h>
#include <sys/stat.h>
#include "libwchar.h"

static access_e __access(const char *s, int m)
{
    access_e ret = ISERROR;
    struct stat sb;
    if (stat(s, &sb) < 0)         { return ret;     }
    else if (S_ISDIR(sb.st_mode)) { ret = ISDIR;    }
    else if (S_ISLNK(sb.st_mode)) { ret = ISLNK;    }
    else if (S_ISREG(sb.st_mode)) { ret = ISFIL;    }
    else                          { return ret;     }
    if (access(s, m) < 0)         { return ISERROR; }
    return ret;
}

access_e u8waccess(const wchar_t *ws, int m)
{
    int  ret       = -1;
    char __AUTO *b = NULL;

    do
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, ws) + 1)) == NULL) ||
            (wcstou8s(b, ws) <= 0)
           ) { break; }

        ret = __access(b, m);

    } while(0);

    return ret;
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
        case 1: {
            return _waccess((const wchar_t*)w, m);
        }
        case 2: {
            return _waccess_ws((const string_ws*)w, m);
        }
        case 3: {
            return __access((const char*)w, m);
        }
        case 4: {
            return _waccess_s((const wchar_t*)w, osz, m);
        }
        default: {
            errno = EFAULT;
            return -1;
        }
    }
}
