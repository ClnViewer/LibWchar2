
#include "libwchar.h"

size_t _wcstombs(char *restrict s, const wchar_t *restrict ws, size_t n)
{
    return _wcsrtombs(s, &(const wchar_t *){ws}, n, 0);
}

size_t _wcstombs_s(char *restrict s, const wchar_t *restrict ws, size_t n)
{
    return _wcsrtombs(s, &(const wchar_t *){ws}, (n * 2 + 1), 0);
}
