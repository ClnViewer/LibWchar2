
#include <stdio.h>
#include "libwchar.h"

void wcprint(wchar_t *w)
{
    wchar_t *p = w;
    while(*p)
    {
        putchar(*p++);
    }
}
