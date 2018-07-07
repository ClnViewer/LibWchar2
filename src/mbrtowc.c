/* 
 * This code was written by Rich Felker in 2010; no copyright is claimed.
 * This code is in the public domain. Attribution is appreciated but
 * unnecessary.
 */

#include "libwchar.h"

size_t _mbrtowc(wchar_t *restrict wc, const char *restrict src, size_t n, mbstate_t *restrict st)
{
    static unsigned is = 0U;
    unsigned int c;
    const unsigned char *s = (const void*)src;
    const unsigned int N = n;

    if (!st)
    {
        st = (void*)&is;
    }
    c = *(unsigned*)st;

    if (!s)
    {
        if (c) goto ilseq;
        return 0;
    }
    else if (!wc)
    {
        wc = (void*)&wc;
    }
    if (!n)
    {
        return -2;
    }
    if (!c)
    {
        if (*s < 0x80)
        {
            return !!(*wc = *s);
        }
        if ((*s - __SA) > (__SB - __SA))
        {
            goto ilseq;
        }
        c = bittab[(*s++ - __SA)];
        n--;
    }
    if (n) {
        if (__OOB(c,*s)) goto ilseq;
loop:
        c = ((c << 6) | (*s++ - 0x80)); n--;
        if (!(c & (1U << 31))) {
            *(unsigned*)st = 0;
            *wc = c;
            return N-n;
        }
        if (n) {
            if ((*s - 0x80U) >= 0x40) goto ilseq;
            goto loop;
        }
    }

    *(unsigned*)st = c;
    return -2;
ilseq:
    errno = EILSEQ;
    *(unsigned*)st = 0;
    return -1;
}
