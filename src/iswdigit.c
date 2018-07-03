
#include "libwchar.h"

//#undef iswdigit

int _iswdigit(wchar_t wc)
{
    return (unsigned)wc-'0' < 10;
}
