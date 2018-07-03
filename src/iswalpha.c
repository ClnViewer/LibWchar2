
#include "libwchar.h"

static const unsigned char table[] = {
#include "table-alpha.h"
};

int _iswalpha(wchar_t wc)
{
	if (wc < 0x20000U)
		return (table[table[wc>>8]*32+((wc&255)>>3)]>>(wc&7))&1;
	if (wc < 0x2fffeU)
		return 1;
	return 0;
}
