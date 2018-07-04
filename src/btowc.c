
#include "libwchar.h"

wchar_t _btowc(int c)
{
    return ((c < 128) ? (wchar_t)c : L'\0');
}
