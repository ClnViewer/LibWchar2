
#include "libwchar.h"

int _iswblank(wchar_t wc)
{
    return isblank(wc);
}
