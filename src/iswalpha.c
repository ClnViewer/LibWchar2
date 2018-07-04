
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
       ) { return 1; }

    switch (wc)
    {
        case 0x00U:  { return 0; }
        case 0x01U:
        case 0x15U:
        case 0xa0U:
        case 0xa1U:
        case 0xa2U:
        case 0xa3U:
        case 0xf9U:
        case 0xfcU:
        case 0x2f8U:
        case 0x2f9U: { return 1; }
        default:     { break; }
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
