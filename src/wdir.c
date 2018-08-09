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
#   include <stdio.h>
#   include <sys/stat.h>
#   include "libwcharext.h"
#   define  __sstat _stat

#   if defined(BUILD_MINGW)
#      include <dirent.h>
#      define __fwprn(x) x
#      define _fwprintf fprintf

#   elif defined(BUILD_MSVC)
#      define __fwprn(x) x
#      define _fwprintf fprintf
#   endif

#else
#   include <stdio.h>
#   include <stdlib.h>
#   include <dirent.h>
#   include <sys/stat.h>
#   include "libwchar.h"
#   define  __sstat stat
#   define  __fwprn(x) __WS(x)

#endif

static void __dir_default_cb(unsigned int ino, access_e etype, long long size, string_ws *name, void *data)
{
    (void) data;
    _fwprintf(stdout, __fwprn("\t\t- ino [%u] -> type [%d] size [%lld] -> [%ls][%zu]\n"),
              ino, etype, size, name->str, name->sz
             );
}

#if !defined(BUILD_MSVC)
static int __dir_entry_path(string_ws *w, wchar_t *path, wchar_t *name)
{
    wchar_t sep[2]  = { __WEV(L,__PSEP), L'\0' };
    memset((void*)w,  0, sizeof(string_ws));

    // cppcheck-suppress varFuncNullUB
    if (!wstring_appends_(w, path, sep, name, NULL))
        return 0;

    return 1;
}
#endif

#if defined(BUILD_MINGW)

static void __dir_entry_info(wchar_t *path, wchar_t *name, access_e *ae, long long *sz)
{
    access_e ret = ISERR;
    struct __sstat _s;
    string_ws wpath = { NULL, 0 };
    memset((void*)&_s, 0, sizeof(struct __sstat));

    do
    {
        if (
            (!__dir_entry_path(&wpath, path, name)) ||
            (_wstat_ws(&wpath, &_s) < 0)
        )
        {
            break;
        }

        if (((_s.st_mode) & _S_IFDIR) == _S_IFDIR)
        {
            ret = ISDIR;
        }
        else if (((_s.st_mode) & _S_IFREG) == _S_IFREG)
        {
            ret = ISFIL;
        }
        else if (((_s.st_mode) & _S_IFBLK) == _S_IFBLK)
        {
            ret = ISBLK;
        }
        else if (((_s.st_mode) & _S_IFCHR) == _S_IFCHR)
        {
            ret = ISCHR;
        }
        else if (((_s.st_mode) & _S_IFIFO) == _S_IFIFO)
        {
            ret = ISFIFO;
        }
        else if (((_s.st_mode) & _S_IFMT) == _S_IFMT)
        {
            ret = ISUNK;
        }
        else
        {
            ret = ISERR;
        }

    }
    while (0);

    wstring_free(&wpath);
    *sz = (long long)_s.st_size;
    *ae = ret;
}

int _wreaddir_cb(wchar_t *dirpath, long opt, wdir_cb fun, void *data)
{
    long              cnt      = 0L;
    struct _wdirent  *we       = NULL;
    _WDIR            *dp       = NULL;
    fun                        = ((fun) ? fun : __dir_default_cb);
    errno                      = 0;

    do
    {
        if (!(dp = _wopendir(dirpath)))
        {
            break;
        }
        while ((we = _wreaddir(dp)))
        {
            do
            {
                if ((we) && (we->d_name[0] != L'\0'))
                {
                    access_e   etype = 0;
                    long long  esz   = 0LL;
                    string_ws  wname = { (wchar_t*)we->d_name, _wcslen(we->d_name) };
                    __dir_entry_info(dirpath, wname.str, &etype, &esz);

                    if (
                        (__BITTST(opt, DIRNODIR)) &&
                        (etype == ISDIR)
                    )
                    {
                        break;
                    }

                    if (
                        (__BITTST(opt, DIRNOROOT))  &&
                        (etype == ISDIR)            &&
                        (wname.sz <= 2)             &&
                        ((!_wcscmp(we->d_name, __WS("."))) ||
                         (!_wcscmp(we->d_name, __WS(".."))))
                    )
                    {
                        break;
                    }

                    cnt++;
                    fun(cnt, etype, esz, &wname, data);
                }

            }
            while (0);
            we = NULL;
        }

        (void) _wclosedir(dp);

        if (we != NULL)
            break;

        return 1;

    }
    while (0);

    return 0;
}

#elif defined(BUILD_MSVC)

static access_e __dir_entry_type(WIN32_FIND_DATAW *we)
{
    if ((we->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) &&
            (we->dwReserved0 & IO_REPARSE_TAG_MOUNT_POINT)
#       if (_MSC_VER > 1500)
            || (we->dwReserved0 & IO_REPARSE_TAG_SYMLINK)
#       endif
       )
    {
        return ISLNK;
    }
    else if (we->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return ISDIR;
    }
    else
    {
        return ISFIL;
    }
}

#include "wdir_msvc.c"

int _wreaddir_cb(wchar_t *dirpath, long opt, wdir_cb fun, void *data)
{
    long               cnt      = 0L;
    WIN32_FIND_DATAW   we       = {0};
    HANDLE             dp       = NULL;
    fun                         = ((fun) ? fun : __dir_default_cb);
    errno                       = 0;

    do
    {
        if (
            (!(dp = FindFirstFileW(dirpath, &we))) ||
            (dp == INVALID_HANDLE_VALUE)
        )
        {
            errno = GetLastError();
            break;
        }
        do
        {
            do
            {
                if (we.cFileName[0] != L'\0')
                {
                    access_e   etype;
                    string_ws  wname;
                    wname.str = (wchar_t*)we.cFileName;
                    wname.sz  = _wcslen(we.cFileName);
                    etype     = __dir_entry_type(&we);

                    if (
                        (__BITTST(opt, DIRNODIR)) &&
                        (etype == ISDIR)
                    )
                    {
                        break;
                    }

                    if (
                        (__BITTST(opt, DIRNOROOT))  &&
                        (etype == ISDIR)            &&
                        (wname.sz <= 2)             &&
                        ((!wcscmp(we.cFileName, __WS("."))) ||
                         (!wcscmp(we.cFileName, __WS(".."))))
                    )
                    {
                        break;
                    }

                    cnt++;
                    fun(cnt, etype, we.nFileSizeLow, &wname, data);
                }

            }
            while (0);

        }
        while (FindNextFileW(dp, &we));

        (void) FindClose(dp);

        errno = GetLastError();
        if (errno == ERROR_NO_MORE_FILES)
        {
            SetLastError(0);
            errno = 0;
        }
        else
        {
            break;
        }
        return 1;

    }
    while (0);

    return 0;
}

#elif !defined(OS_WIN)

static int __dir_type[] =
{
    [0]  = ISUNK,
    [1]  = ISFIL,
    [2]  = ISCHR,
    [4]  = ISDIR,
    [6]  = ISBLK,
    [8]  = ISFIL,
    [10] = ISLNK,
    [12] = ISSOCK,
    [14] = ISWHT
};

static long long __dir_entry_size(wchar_t *path, wchar_t *name)
{
    struct __sstat _s;
    string_ws wpath = { NULL, 0 };
    memset((void*)&_s, 0, sizeof(struct __sstat));

    if (
        (__dir_entry_path(&wpath, path, name)) &&
        (_wstat_ws(&wpath, &_s))
    ) { ; }

    wstring_free(&wpath);
    return (long long)_s.st_size;
}

#include "wdir_gnu.c"

int _wreaddir_cb(wchar_t *dirpath, long opt, wdir_cb fun, void *data)
{
    int        ret      = 0;
    wdirent_t  wentry,
               *we       = NULL;
    __WDIR_t  *dir      = NULL;
    fun                 = ((fun) ? fun : __dir_default_cb);
    errno               = 0;

    do
    {
        memset((void*)&wentry, 0, sizeof(wdirent_t));

        if (
            (!(dir = _wopendir(dirpath))) ||
            (!dir->dp)
        )
        {
            break;
        }
        while ((!(ret = _wreaddir_r(dir, &wentry, &we))) && (we != NULL))
        {
            do
            {
                if (wentry.d_name[0] != L'\0')
                {
                    access_e   etype;
                    long long  esz   = 0LL;
                    string_ws  wname = { (wchar_t*)wentry.d_name, _wcslen(wentry.d_name) };
                    etype            = __dir_type[wentry.d_type];

                    if (
                        (__BITTST(opt, DIRNODIR)) &&
                        (etype == ISDIR)
                    )
                    {
                        break;
                    }

                    if (
                        (__BITTST(opt, DIRNOROOT))  &&
                        (etype == ISDIR)            &&
                        (wname.sz <= 2)             &&
                        ((!_wcscmp(wentry.d_name, __WS("."))) ||
                         (!_wcscmp(wentry.d_name, __WS(".."))))
                    )
                    {
                        break;
                    }

                    if (
                        (__BITTST(opt, DIRENTRYSIZE)) &&
                        (etype == ISFIL)
                    )
                    {
                        esz = __dir_entry_size(dirpath, wname.str);
                    }

                    fun(dir->d_ino, etype, esz, &wname, data);
                }

            }
            while (0);
            memset((void*)&wentry, 0, sizeof(wdirent_t));
        }

        (void) _wclosedir(dir);

        if ((ret) || (we != NULL))
            break;

        return 1;

    }
    while (0);

    errno = ret;
    return 0;
}

#endif
