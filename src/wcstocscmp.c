
#include "libwchar.h"

int wcstocscmp(const char *c, wchar_t *w, size_t wsz)
{
    size_t         cnt  = 0;
    const wchar_t *wchr = w;
    const char    *cchr = c;

    while(*cchr)
    {
        if (cnt == wsz) { return 0; }
        if (wchr[cnt++] != *cchr++) { return 1; }
    }
    return 0;
}
