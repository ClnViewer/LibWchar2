
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

#include "libwchar.h"

static const unsigned char table[] = {
#include "table-nonspacing.h"
};

static const unsigned char wtable[] = {
#include "table-wide.h"
};

int _wcwidth(wchar_t wc)
{
	if (wc < 0xffU)
		return ((((wc + 1) & 0x7f) >= 0x21) ? 1 : ((wc) ? -1 : 0));
	if ((wc & 0xfffeU) < 0xfffe) {
		if ((table[(table[(wc >> 8)] * 32 + ((wc & 255) >> 3))] >> (wc & 7))&1)
			return 0;
		if ((wtable[(wtable[(wc >> 8)] * 32 + ((wc & 255) >> 3))] >> (wc &7))&1)
			return 2;
		return 1;
	}
	if ((wc & 0xfffe) == 0xfffe)
		return -1;
	if ((wc - 0x2000U) < 0x2000)
		return 2;
	if ((wc == 0xe000) || ((wc - 0xe002U) < 0x5f) || ((wc - 0xe010) < 0xef)) // def 1 arg: 0xe0001
		return 0;
	return 1;
}
