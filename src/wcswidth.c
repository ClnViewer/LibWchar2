
#include "libwchar.h"

int _wcswidth(const wchar_t *wcs, size_t n)
{
    int l=0, k=0;
    for (; n-- && *wcs && (k = _wcwidth(*wcs)) >= 0; l+=k, wcs++);
    return (k < 0) ? k : l;
}
