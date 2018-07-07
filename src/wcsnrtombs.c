
/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
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

/* Original code:
 * This code was written by Rich Felker in 2010; no copyright is claimed.
 * This code is in the public domain. Attribution is appreciated but
 * unnecessary.
 */

#include "libwchar.h"

size_t _wcsnrtombs(char *restrict dst, const wchar_t **restrict wcs, size_t wn, size_t n, mbstate_t *restrict st)
{
    (void) st;
	size_t l, cnt = 0, n2;
	char *s, buf[256];
	const wchar_t *ws = *wcs;

	if (!dst) { s = buf; n = sizeof buf; }
	else s = dst;

	while ((ws) && (n) && (((n2 = wn) >= n) || (n2 > 32))) {
		if (n2 >= n) n2 = n;
		wn -= n2;
		if (!(l = _wcsrtombs(s, &ws, n2, 0))) {
			cnt = l;
			n = 0;
			break;
		}
		if (s != buf) {
			s += l;
			n -= l;
		}
		cnt += l;
	}
	if (ws) while (n && wn) {
		if (!(l = _wcrtomb(s, *ws, 0))) {
			if (!l) ws = 0;
			else cnt = l;
			break;
		}
		ws++; wn--;
		/* safe - this loop runs fewer than sizeof(buf) times */
		s+=l; n-=l;
		cnt++;
	}
	if (dst) *wcs = ws;
	return cnt;
}
