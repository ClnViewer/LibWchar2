
#include "libwchar.h"

static const unsigned char table[] = {
#include "table-punct.h"
};

int _iswpunct(wchar_t wc)
{
    if (wc < 0x20000U)
        return (table[table[wc>>8]*32+((wc&255)>>3)]>>(wc&7))&1;
    return 0;
}
