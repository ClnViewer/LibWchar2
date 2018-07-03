
#include "libwchar.h"

wctrans_t _wctrans(const char *class)
{
	if (!strcmp(class, "toupper")) return (wctrans_t)1;
	if (!strcmp(class, "tolower")) return (wctrans_t)2;
	return 0;
}

wchar_t _towctrans(wchar_t wc, wctrans_t trans)
{
	if (trans == (wctrans_t)1) return _towupper(wc);
	if (trans == (wctrans_t)2) return _towlower(wc);
	return wc;
}
