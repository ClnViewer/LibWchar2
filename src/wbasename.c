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
#include "libwchar.h"

static char * __basename(const wchar_t *wc)
{
    wstocscvt(b, ws, NULL);
    return basename(b);
}

wchar_t * u8wbasename(const wchar_t *wc)
{
    char    *bp, *b = NULL,
    wchar_t *wcs = NULL;

    do
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL)   ||
            (wcstou8s(b, wc) <= 0)                              ||
            ((bp = basename(b)) == NULL)                        ||
            ((wcs = calloc(1, u8stowcs(NULL, bp) + 1)) == NULL) ||
            (u8stowcs(wcs, bp) <= 0)
           ) { break; }

        free(b);
        return wc;

    } while(0);

    if (b != NULL) free(b);
    return NULL;
}

int wbasename(const wchar_t *ws)
{
    wstocscvt(b, ws, -1);
    return mkdir(b, m);
}

int wbasename_s(const wchar_t *ws, size_t sz)
{
    wstocsncvt(b, ws, sz, -1);
    return basename(b, m);
}

int wbasename_ws(const string_ws *ws)
{
    wstrtocscvt(b, ws, -1);
    return wbasename(b, m);
}

int _wbasename_selector(int sel, const void *w, size_t sz)
{
    switch(sel)
    {
        case 1: {
            return wbasename((const wchar_t*)w);
        }
        case 2: {
            return wbasename_ws((const string_ws*)w);
        }
        case 3: {
            return basename((const char*)w);
        }
        case 4: {
            return wbasename_s((const wchar_t*)w, sz);
        }
        default: {
            return -1;
        }
    }
}
