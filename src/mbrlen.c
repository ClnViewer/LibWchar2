/* 
 * This code was written by Rich Felker in 2010; no copyright is claimed.
 * This code is in the public domain. Attribution is appreciated but
 * unnecessary.
 */

#include "libwchar.h"

size_t _mbrlen(const char *restrict s, size_t n, mbstate_t *restrict st)
{
    static unsigned internal;
    return _mbrtowc(0, s, n, ((st) ? st : (mbstate_t*)&internal));
}
