/* 
 * This code was written by Rich Felker in 2010; no copyright is claimed.
 * This code is in the public domain. Attribution is appreciated but
 * unnecessary.
 */

#include "libwchar.h"

size_t _wcsrtombs(char *restrict s, const wchar_t **restrict ws, size_t n, mbstate_t *restrict st)
{
    (void) st;
	const wchar_t *ws2;
	char buf[2]; // original 4
	size_t N = n, l;
	if (!s) {
		for (n = 0, ws2 = *ws; *ws2; ws2++) {
			if (*ws2 >= 0x80u) {
				if (!(l = _wcrtomb(buf, *ws2, 0))) { return -1; }
				n += l;
			} else { n++; }
		}
		return n;
	}
	if ((!n) || (n < 2)) return -1;
	while ((n >= 2) && (**ws)) {
		if (**ws >= 0x80u) {
			if (!(l = _wcrtomb(s, **ws, 0))) { return -1; }
			s += l;
			n -= l;
		} else {
			*s++ = **ws;
			n--;
		}
		(*ws)++;
	}
	while (n && **ws) {
		if (**ws >= 0x80u) {
			if (!(l = _wcrtomb(buf, **ws, 0))) { return -1; }
			if (l > n)                         { return (N - n); }
			_wcrtomb(s, **ws, 0);
			s += l;
			n -= l;
		} else {
			*s++ = **ws;
			n--;
		}
		(*ws)++;
	}
	if (n) *s = 0;
	*ws = 0;
	return (N - n);
}
