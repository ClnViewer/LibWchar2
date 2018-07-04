
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
