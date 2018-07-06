
#include "libwchar.h"

wchar_t _btowc(int c)
{
    wchar_t wc;
    char cc = (char)c;

    if (
        ((c > 0) && (c < 128)) &&
        (_mbrtowc(&wc, &cc, 1, 0) == 1)
       ) { return (wc); }

    return L'\0';
}
