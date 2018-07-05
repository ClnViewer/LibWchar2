
/*
 * Example build:
 *    // use default libc
 *    gcc -std=gnu99 -Wall fs-redifine.c -o fs-redifine
 *    // use libwchar2 && WS_FS_REDEFINE
 *    gcc -std=gnu99 -Wall -fshort-wchar -DWS_FS_REDEFINE -L../src/.libs -Wl,-rpath=../src/.libs -lwchar2 fs-redifine.c -o fs-redifine
 */

#if !defined(_GNU_SOURCE)
#   define _GNU_SOURCE
#endif

#if !defined(_ISOC99_SOURCE)
#   define _ISOC99_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <locale.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#if defined(WS_FS_REDEFINE)
#  include "../include/wchar2.h"
#  define WCHAR  wchar_t
#else
#  define WCHAR  char
#  define __WS(x) x
#  define __WS_STR_FMT  "s"
#  define __WS_CHAR_FMT "c"
#endif

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "en_US.utf8");

    FILE  *fp;
    WCHAR *file   = __WS("open-file-name.txt");
    WCHAR *string = __WS("A texts is a type of computer program that edits plain text.");

    if (!(fp = fopen(file, "a+"))) {
        fprintf(stdout, "\n\terror open file: [%" __WS_STR_FMT "] [%s]\n", file, strerror(errno));
        return 127;
    }
    fputs(string, fp);
    fputs(__WS("\n"), fp);
    fclose(fp);

    fprintf(stdout, "\n\tstring [%" __WS_STR_FMT "] ->\n\t\tfputs to file: [%" __WS_STR_FMT "]\n", string, file);
    return 0;
}
