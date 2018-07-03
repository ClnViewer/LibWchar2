
#include "libwchar.h"

size_t _mbstowcs(wchar_t *restrict ws, const char *restrict s, size_t wn)
{
    return _mbsrtowcs(ws, (void*)&s, wn, 0);
}
