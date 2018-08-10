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

#if (defined(OS_WIN) && defined(BUILD_MSVC))
//#   error "this code compiled ONLY for MSVC/MSVS!"

typedef struct
{
    HANDLE           dp;
    WIN32_FIND_DATAW we;
    string_ws        droot;
    unsigned int     d_ino;
    wdirent_t        wde;
} __WDIR_t;

WDIR_t * wopendir(const wchar_t *w)
{
    __WDIR_t *dir = NULL;
    if (!w)
    {
        errno = EINVAL;
        return NULL;
    }
    do
    {
        size_t wlen = _wcslen(w);
        while ((wlen) && ((w[wlen-1] == '\\') || (w[wlen-1] == '/')))
        {
            --wlen;
        }

        if (
            ((dir = calloc(1, sizeof(__WDIR_t))) == NULL)           ||
            (!wstring_append(&dir->droot, w, wlen))                 ||
            (!wstring_append(&dir->droot, __WS("\\*"), (wsizeof("\\*") - 1))) ||
            (!(dir->dp = FindFirstFileW(dir->droot.str, &dir->we))) ||
            (dir->dp == INVALID_HANDLE_VALUE)
        )
        {
            break;
        }

        dir->d_ino = 0;
        memset((void*)&dir->wde, 0, sizeof(wdirent_t));
        return (WDIR_t*)dir;

    }
    while (0);

    errno = GetLastError();
    wclosedir(dir);
    return NULL;
}

int wclosedir(WDIR_t *v)
{
    __WDIR_t *dir = (__WDIR_t*)v;
    if (!dir)
    {
        errno = EINVAL;
        return EINVAL;
    }
    if (dir->dp)
    {
        FindClose(dir->dp);
    }
    wstring_free(&dir->droot);
    free(dir);
    return 0;
}

int wreaddir_r(WDIR_t *v, wdirent_t *wde, wdirent_t **wdep)
{
    __WDIR_t *dir = (__WDIR_t*)v;
    if (!v)
    {
        errno = EINVAL;
        return EINVAL;
    }
    do
    {
        errno_t err;
        errno = 0;

        if (!FindNextFileW(dir->dp, &dir->we))
        {
            break;
        }

        wde->d_ino = ++dir->d_ino;
        wde->d_reclen = sizeof(wdirent_t);
        wde->d_type = (unsigned char) __dir_entry_type(&dir->we);

        if ((err = wcscpy_s(wde->d_name, sizeof(wde->d_name), dir->we.cFileName)) != 0)
        {
            errno = err;
            break;
        }
#       if defined(_DIRENT_HAVE_D_NAMLEN)
        wde->d_namlen = _wcslen(wde->d_name);
#       endif
        *wdep = wde;

        return 0;

    }
    while (0);

    if (!errno)
    {
        errno = GetLastError();
    }
    if (errno == ERROR_NO_MORE_FILES)
    {
        SetLastError(0);
        errno = 0;
    }
    if (wdep)
        *wdep = NULL;
    return errno;
}

wdirent_t * wreaddir(WDIR_t *v)
{
    wdirent_t *wdep = NULL;
    __WDIR_t *dir = (__WDIR_t*)v;
    if (!v)
    {
        errno = EINVAL;
        return NULL;
    }
    if (wreaddir_r(dir, &dir->wde, &wdep))
        return NULL;
    return wdep;
}

void wrewinddir(WDIR_t *v)
{
    __WDIR_t *dir = (__WDIR_t*)v;
    if (!v)
    {
        errno = EINVAL;
        return;
    }
    if (dir->dp)
    {
        FindClose(dir->dp);
    }
    dir->d_ino = 0;
    if (
        (!(dir->dp = FindFirstFileW(dir->droot.str, &dir->we))) ||
        (dir->dp == INVALID_HANDLE_VALUE)
    )
    {
        errno = EBADF;
    }
}

#endif

