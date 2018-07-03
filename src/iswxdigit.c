
#include "libwchar.h"

int _iswxdigit(wchar_t wc)
{
    return (unsigned)(wc-'0') < 10 || (unsigned)((wc|32)-'a') < 6;
}
