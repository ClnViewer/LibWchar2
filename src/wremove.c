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

int u8wremove(const wchar_t *wc)
{
    int   ret = -1;
    char *b   = NULL;

    do
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL) ||
            (wcstou8s(b, wc) <= 0)
           ) { break; }

        ret = remove(b);

    } while(0);

    if (b != NULL) free(b);
    return ret;
}

int _wremove(const wchar_t *ws)
{
    wstocscvt(b, ws, -1);
    return remove(b);
}

int _wremove_s(const wchar_t *ws, size_t sz)
{
    wstocsncvt(b, ws, sz, -1);
    return remove(b);
}

int _wremove_ws(const string_ws *ws)
{
    wstrtocscvt(b, ws, -1);
    return remove(b);
}

int _wremove_selector(int sel, const void *w, size_t sz)
{
    switch(sel)
    {
        case 1: {
            return _wremove((const wchar_t*)w);
        }
        case 2: {
            return _wremove_ws((const string_ws*)w);
        }
        case 3: {
            return remove((const char*)w);
        }
        case 4: {
            return _wremove_s((const wchar_t*)w, sz);
        }
        default: {
            return -1;
        }
    }
}
