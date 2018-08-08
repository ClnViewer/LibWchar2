
/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sub license, and/or sell
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

size_t _wcrtomb(char *restrict s, wchar_t wc, mbstate_t *restrict st)
{
    (void) st;
	if (!s) return 1;
	if ((unsigned)wc < 0x80U) {
		*s = (char)wc;
		return 1;
	} else if ((unsigned)wc < 0x800U) {
		*s++ = (char)(0xc0 | (wc >> 6));
		*s   = (char)(0x80 | (wc & 0x3f));
		return 2;
	} else if (((unsigned)wc < 0xd800U) || (((unsigned)wc - 0xe000U) < 0x2000U)) {
		*s++ = (char)(0xe0 |  (wc >> 12));
		*s++ = (char)(0x80 | ((wc >> 6) & 0x3f));
		*s   = (char)(0x80 |  (wc & 0x3f));
		return 3;
	} else if (((unsigned)wc - 0x10000U) < 0x100000U) {
		*s++ = (char)(0xf0 |  (wc >> 18));
		*s++ = (char)(0x80 | ((wc >> 12) & 0x3f));
		*s++ = (char)(0x80 | ((wc >> 6) & 0x3f));
		*s   = (char)(0x80 |  (wc & 0x3f));
		return 4;
	}
	errno = EILSEQ;
	return (size_t)-1;
}
