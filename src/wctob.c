
#include "libwchar.h"

int _wctob(wchar_t c)
{
    if (c < 128U) return c;
    return 0;
}
