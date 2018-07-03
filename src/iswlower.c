
#include "libwchar.h"

int _iswlower(wchar_t wc)
{
    return _towupper(wc) != wc || wc == 0xdf;
}
