
#include "libwchar.h"

int _iswupper(wchar_t wc)
{
    return _towlower(wc) != wc;
}
