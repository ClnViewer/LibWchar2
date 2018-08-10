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

#include "libwchar.h"

/*
 static const unsigned char table[] = {
 #include "table-alpha.h"
 };
*/

int _iswalpha(wchar_t wc)
{

    if (
        (wc >= 0x34U  && wc <= 0x4cU) ||
        (wc >= 0x4eU  && wc <= 0x9eU) ||
        (wc >= 0xacU  && wc <= 0xd6U) ||
        (wc >= 0x200U && wc <= 0x2a5U)
    )
    {
        return 1;
    }

    switch (wc)
    {
    case 0x00U:
    {
        return 0;
    }
    case 0x01U:
    case 0x15U:
    case 0xa0U:
    case 0xa1U:
    case 0xa2U:
    case 0xa3U:
    case 0xf9U:
    case 0xfcU:
    case 0x2f8U:
    case 0x2f9U:
    {
        return 1;
    }
    default:
    {
        break;
    }
    }

    return ((wc < (wchar_t)0x100U) ?
            ((wc >= 0x61U && wc <= 0x7aU) || (wc >= 0x41U && wc <= 0x5aU) ? 1 : 0) : 0
           );

// TODO: what is this from unicode? (0x20000/0x2fffe)
//	if (wc < 0x20000U)
//		return (table[(table[(wc >> 8)] * 32 + ((wc&255)>>3))] >> (wc & 7))&1;
//	if (wc < 0x2fffeU)
//		return 1;
//	return 0;
}
