
#include "libwchar.h"

wchar_t _btowc(int c)
{
    return ((c < 128U) ? c : 0);
}
