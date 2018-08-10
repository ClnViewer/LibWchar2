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

#if !defined(OS_WIN)
//#   error "this code compiled ONLY for *nix platform!"

#define __DIR_DNAME_SIZE sizeof(((struct dirent*)0)->d_name)

typedef struct
{
    DIR          *dp;
    unsigned int  d_ino;
    wdirent_t     wde;
} __WDIR_t;

static int __check_dirent(void)
{
    return (
               (sizeof(struct dirent) - sizeof(((struct dirent*)0)->d_name)) ==
               (sizeof(wdirent_t) - sizeof(((wdirent_t*)0)->d_name))
           );
}

int _wclosedir(WDIR_t *d)
{
    int ret;
    __WDIR_t *dir = (__WDIR_t*)d;
    if ((!dir) || (!dir->dp))
    {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    ret = closedir(dir->dp);
    free(d);
    return ret;
}

WDIR_t * _wopendir(const wchar_t *w)
{
    if (!__check_dirent())
    {
        errno = EFAULT;
        return NULL;
    }
    {
        __WDIR_t *dir;
        wstocscvt(b, w, NULL);
        if ((dir = calloc(1, sizeof(__WDIR_t))) == NULL)
            return NULL;

        dir->dp = opendir(b);
        return (WDIR_t*) dir;
    }
}

wdirent_t * _wreaddir(WDIR_t *d)
{
    __WDIR_t  *dir = (__WDIR_t*)d;
    wdirent_t *wde;

    if ((!dir) || (!dir->dp))
    {
        errno = EINVAL;
        return NULL;
    }

    wde = (wdirent_t*)&dir->wde;
    errno = 0;

    do
    {
        size_t     sz;
        wchar_t    dname[__DIR_DNAME_SIZE] = {0};
        struct     dirent *de;

        if (!__check_dirent())
        {
            errno = EFAULT;
            break;
        }

        memset((void*)wde, 0, sizeof(wdirent_t));

        if (
            (!(de = readdir(dir->dp))) ||
            (!(sz = wstring_cstows(dname, __DIR_DNAME_SIZE, de->d_name, 0)))
        )
        {
            break;
        }

        dir->d_ino++;

        memcpy((void*)wde, (void*)de, (sizeof(struct dirent) - __DIR_DNAME_SIZE));
        _wmemcpy((wchar_t*)&wde->d_name, dname, sz);
#       if defined(_DIRENT_HAVE_D_NAMLEN)
        wde->d_namlen = sz;
#       endif

        return wde;

    }
    while (0);

    return NULL;
}

int _wreaddir_r(WDIR_t *d, wdirent_t *wde, wdirent_t **wdep)
{
    __WDIR_t *dir = (__WDIR_t*)d;

    if ((!dir) || (!dir->dp) || (!wde))
    {
        errno = EINVAL;
        return EINVAL;
    }
    if (!__check_dirent())
    {
        errno = EFAULT;
        return EFAULT;
    }
    do
    {
        int     ret;
        struct  dirent de, *dep;
        errno = 0;

        if ((ret = readdir_r(dir->dp, &de, &dep)))
        {
            return ret;
        }

        dir->d_ino++;

        if (dep != NULL)
        {
            size_t  sz;
            wchar_t dname[__DIR_DNAME_SIZE] = {0};

            if (!(sz = wstring_cstows(dname, __DIR_DNAME_SIZE, de.d_name, 0)))
            {
                errno = EFAULT;
                break;
            }
            memcpy((void*)wde, (void*)&de, (sizeof(struct dirent) - __DIR_DNAME_SIZE));
            _wmemcpy((wchar_t*)&wde->d_name, dname, sz);

#           if defined(_DIRENT_HAVE_D_NAMLEN)
            wde->d_namlen = sz;
#           endif

            if (wdep)
                *wdep = wde;
        }
        else
        {
            memset((void*)wde, 0, sizeof(wdirent_t));
            if (wdep)
                *wdep = NULL;
        }
    }
    while (0);

    return errno;
}

void _wrewinddir(WDIR_t *d)
{
    __WDIR_t *dir = (__WDIR_t*)d;
    if ((!dir) || (!dir->dp))
    {
        errno = EINVAL;
        return;
    }
    dir->d_ino = 0;
    rewinddir(dir->dp);
}

void _wseekdir(WDIR_t *d, long n)
{
    __WDIR_t *dir = (__WDIR_t*)d;
    if ((!dir) || (!dir->dp))
    {
        errno = EINVAL;
        return;
    }
    dir->d_ino = (unsigned int)n;
    seekdir(dir->dp, n);
}

long int _wtelldir(WDIR_t *d)
{
    __WDIR_t *dir = (__WDIR_t*)d;
    if ((!dir) || (!dir->dp))
    {
        errno = EINVAL;
        return -1L;
    }
    return telldir(dir->dp);
}

#endif
