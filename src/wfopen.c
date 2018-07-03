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

FILE * u8wfopen(const wchar_t *wc, const char *m)
{
    FILE *f = NULL;
    char *b = NULL;

    do
    {
        if (
            ((b = calloc(1, wcstou8s(NULL, wc) + 1)) == NULL) ||
            (wcstou8s(b, wc) <= 0)
           ) { break; }

        f = fopen(b, m);

    } while(0);

    if (b != NULL) free(b);
    return f;
}

FILE * _wfopen(const wchar_t *wc, const char *m)
{
    wstocscvt(b, wc, NULL);
    return fopen(b, m);
}

FILE * _wfopen_s(const wchar_t *wc, size_t sz, const char *m)
{
    wstocsncvt(b, wc, sz, NULL);
    return fopen(b, m);
}

FILE * _wfopen_ws(const string_ws *ws, const char *m)
{
    wstrtocscvt(b, ws, NULL);
    return fopen(b, m);
}

FILE * _wfopen_selector(int sel, const void *w, size_t sz, const void *m)
{
    switch(sel)
    {
        case 1: {
            return _wfopen((const wchar_t*)w, (const char*)m);
        }
        case 2: {
            return _wfopen_ws((const string_ws*)w, (const char*)m);
        }
        case 3: {
            return fopen((const char*)w, (const char*)m);
        }
        case 4: {
            return _wfopen_s((const wchar_t*)w, sz, (const char*)m);
        }
        default: {
            return NULL;
        }
    }
}
