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

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "libwchar.h"

#define __DIR_DNAME_SIZE sizeof(((struct dirent*)0)->d_name)

static int __check_dirent(void)
{
    return (
            (sizeof(struct dirent) - sizeof(((struct dirent*)0)->d_name)) ==
            (sizeof(wdirent_t) - sizeof(((wdirent_t*)0)->d_name))
   );
}

int _wclosedir(WDIR_t *d)
{
    if (!d) return 0;
    return closedir((DIR*)d);
}

WDIR_t * _wopendir(const wchar_t *w)
{
    if (!__check_dirent())
    {
        errno = EFAULT;
        return NULL;
    }
    {
        wstocscvt(b, w, NULL);
        return (WDIR_t*) opendir(b);
    }
}

wdirent_t * _wreaddir(WDIR_t *d)
{
    wdirent_t __AUTO *wde = NULL;

    do
    {
        size_t     sz;
        wchar_t    dname[__DIR_DNAME_SIZE] = {0};
        wdirent_t *wdo;
        struct     dirent *de;

        if (!__check_dirent())
        {
            errno = EFAULT;
            break;
        }
        if (!d)
        {
            errno = EINVAL;
            break;
        }
        if (
            (!(de = readdir((DIR*)d)))              ||
            (!(wde = calloc(1, sizeof(wdirent_t)))) ||
            (!(sz = wstring_cstows(dname, __DIR_DNAME_SIZE, de->d_name, 0)))
           ) { break; }

        memcpy((void*)wde, (void*)de, (sizeof(struct dirent) - __DIR_DNAME_SIZE));
        _wmemcpy((wchar_t*)&wde->d_name, dname, sz);

        wdo = wde;
        wde = NULL;
        return wdo;

    } while (0);

    return NULL;
}

int _wreaddir_r(WDIR_t *d, wdirent_t *wde, wdirent_t **wdep)
{
    if (!__check_dirent())
    {
        errno = EFAULT;
        return EFAULT;
    }
    if ((!d) || (!wde))
    {
        errno = EINVAL;
        return EINVAL;
    }
    do
    {
        int     ret;
        size_t  sz;
        wchar_t dname[__DIR_DNAME_SIZE] = {0};
        struct  dirent de, *dep;
        errno = 0;

        if ((ret = readdir_r(d, &de, &dep)))
            return ret;

        if (dep != NULL)
        {
            if (!(sz = wstring_cstows(dname, __DIR_DNAME_SIZE, de.d_name, 0)))
            {
                errno = EFAULT;
                break;
            }
            memcpy((void*)wde, (void*)&de, (sizeof(struct dirent) - __DIR_DNAME_SIZE));
            _wmemcpy((wchar_t*)&wde->d_name, dname, sz);
            if (wdep) *wdep = wde;
        }
        else
        {
            memset((void*)wde, 0, sizeof(wdirent_t));
            if (wdep) *wdep = NULL;
        }

    } while (0);

    return 0;
}

void _wrewinddir(WDIR_t *d)
{
    if (!d) return;
    rewinddir((DIR*)d);
}

void _wseekdir(WDIR_t *d, long n)
{
    if (!d) return;
    seekdir((DIR*)d, n);
}

long int _wtelldir(WDIR_t *d)
{
    if (!d) return -1L;
    return telldir((DIR*)d);
}
