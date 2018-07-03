
#include "libwchar.h"

int _iswalnum(wchar_t wc)
{
    return _iswdigit(wc) || _iswalpha(wc);
}
