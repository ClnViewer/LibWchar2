
/*
 * Example build:
 *    // use default libc
 *    gcc -std=gnu99 -Wall -Wextra -pedantic fs-redifine.c -o fs-redifine.libc
 *    // use libwchar2 && WS_FS_REDEFINE
 *    gcc -std=gnu99 -Wall -Wextra -pedantic -fshort-wchar -DWS_FS_REDEFINE -L../src/.libs -Wl,-rpath=../src/.libs -lwchar2 fs-redifine.c -o fs-redifine.wchar2
 */

#if !defined(_GNU_SOURCE)
#   define _GNU_SOURCE
#endif

#if !defined(_ISOC99_SOURCE)
#   define _ISOC99_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <errno.h>
#include <sys/stat.h>

#if defined(WS_FS_REDEFINE)
#  include "../include/wchar2.h"
#else
#  define __WSTR  char
#  define __WS(x) x
#  define __WSTR_FMT  "s"
#  define __WCHAR_FMT "c"
#endif

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    setlocale(LC_ALL, "en_US.utf8");

    FILE  *fp;
    __WSTR *file   = __WS("open-file-name.txt");
    __WSTR *string = __WS("A texts is a type of computer program that edits plain text.");

    if (!(fp = fopen(file, "a+"))) {
        fprintf(stdout, "\n\terror open file: [%" __WSTR_FMT "] [%s]\n", file, strerror(errno));
        return 127;
    }
    fputs(string, fp);
    fputs(__WS("\n"), fp);
    fclose(fp);

    fprintf(stdout, "\n\tstring [%" __WSTR_FMT "] ->\n\t\tfputs to file: [%" __WSTR_FMT "]\n", string, file);
    return 0;
}
