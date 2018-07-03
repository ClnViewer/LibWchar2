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

#include <stdio.h>
#include <stdlib.h>
#include "libwchar.h"

int u8wrename(const wchar_t *o, const wchar_t *n)
{
    int   ret = -1;
    char *ob  = NULL,
         *nb  = NULL;
    do
    {
        if (
            ((ob = calloc(1, wcstou8s(NULL, o) + 1)) == NULL) ||
            (wcstou8s(ob, o) <= 0)                            ||
            ((nb = calloc(1, wcstou8s(NULL, n) + 1)) == NULL) ||
            (wcstou8s(nb, n) <= 0)
           ) { break; }

        ret = rename(ob, nb);

    } while(0);

    if (ob != NULL) free(ob);
    if (nb != NULL) free(nb);
    return ret;
}

int _wrename(const wchar_t *o, const wchar_t *n)
{
    wstocscvt(ob, o, -1);
    wstocscvt(nb, n, -1);
    return rename(ob, nb);
}

int _wrename_s(const wchar_t *o, size_t osz, const wchar_t *n, size_t nsz)
{
    wstocsncvt(ob, o, osz, -1);
    wstocsncvt(nb, n, nsz, -1);
    return rename(ob, nb);
}

int _wrename_ws(const string_ws *o, const string_ws *n)
{
    wstrtocscvt(ob, o, -1);
    wstrtocscvt(nb, n, -1);
    return rename(ob, nb);
}

int _wrename_selector(int sel, const void *w, size_t osz, const void *s, size_t nsz)
{
    switch(sel)
    {
        case 1: {
            return _wrename((const wchar_t*)w, (const wchar_t*)s);
        }
        case 2: {
            return _wrename_ws((const string_ws*)w, (const string_ws*)s);
        }
        case 3: {
            return rename((const char*)w, (const char*)s);
        }
        case 4: {
            return _wrename_s((const wchar_t*)w, osz, (const wchar_t*)s, nsz);
        }
        default: {
            return -1;
        }
    }
}
