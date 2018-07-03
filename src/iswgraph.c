
#include "libwchar.h"

int _iswgraph(wchar_t wc)
{
    /* ISO C defines this function as: */
    return !_iswspace(wc) && _iswprint(wc);
}
