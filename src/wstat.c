/*
  Copyright (c) 2018 PS

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "libwchar.h"

int u8wstat(const wchar_t *wc, struct stat *st)
{
    int   ret = -1;
    char *b   = NULL;

    do
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL) ||
            (wcstou8s(b, wc) <= 0)
           ) { break; }

        ret = stat(b, st);

    } while(0);

    if (b != NULL) free(b);
    return ret;
}

int _wstat(const wchar_t *ws, struct stat *st)
{
    wstocscvt(b, ws, -1);
    return stat(b, st);
}

int _wstat_s(const wchar_t *ws, size_t sz, struct stat *st)
{
    wstocsncvt(b, ws, sz, -1);
    return stat(b, st);
}

int _wstat_ws(const string_ws *ws, struct stat *st)
{
    wstrtocscvt(b, ws, -1);
    return stat(b, st);
}

int _wstat_selector(int sel, const void *w, size_t sz, const void *s)
{
    struct stat  sst = {0},
                *st  = ((s == NULL) ? (struct stat*)&sst : (struct stat*)s);

    switch (sel)
    {
        case 1: {
            return _wstat((const wchar_t*)w, st);
        }
        case 2: {
            return _wstat_ws((const string_ws*)w, st);
        }
        case 3: {
            return stat((const char*)w, st);
        }
        case 4: {
            return _wstat_s((const wchar_t*)w, sz, st);
        }
        default: {
            return -1;
        }
    }
}
