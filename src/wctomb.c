/* 
 * This code was written by Rich Felker in 2010; no copyright is claimed.
 * This code is in the public domain. Attribution is appreciated but
 * unnecessary.
 */

#include "libwchar.h"

int _wctomb(char *s, wchar_t wc)
{
    if (!s) return 0;
    return _wcrtomb(s, wc, 0);
}
