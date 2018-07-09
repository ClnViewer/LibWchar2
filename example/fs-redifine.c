
/*
 * Example build:
 *
 *    // use default libc, __WSTR as char
 *    gcc -std=gnu99 -Wall -Wextra -pedantic fs-redifine.c -o fs-redifine.libc
 *
 *    // use libwchar2 && WS_FS_REDEFINE, __WSTR as wchar_t == size 2
 *    gcc -std=gnu99 -Wall -Wextra -pedantic -fshort-wchar -DWS_FS_REDEFINE \
 *       -L../src/.libs -Wl,-rpath=../src/.libs -lwchar2 fs-redifine.c -o fs-redifine.wchar2
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
#  include <libgen.h> /* for dirname, basename */
#  define __WSTR  char
#  define __WSTRFREE __WSTR
#  define __WS(x) x
#  define __WSTR_FMT  "s"
#  define __WCHAR_FMT "c"
#endif

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    setlocale(LC_ALL, "en_US.utf8");

    FILE   *fp;
    const __WSTR fpath[] = __WS("/this/path/to/file.zip");
    __WSTR      *file    = __WS("open-file-name.txt");
    __WSTR      *string  = __WS("A texts is a type of computer program that edits plain text.");
    __WSTR      *bext    = __WS("--NOT SUPPORT LIBWCHAR2 EXTENSION--"),
                *bname   = NULL;
    __WSTRFREE  *bdir    = NULL;

    bdir   = dirname((__WSTR*)fpath); /* free instance needed, auto free is enabled */
    bname  = basename((__WSTR*)fpath);
#   if defined(WS_FS_REDEFINE)
    bext   = baseext((__WSTR*)fpath);
#   endif

    fprintf(stdout, "\n\tbase full path: [%" __WSTR_FMT "]" \
        "\n\tbase dir: [%" __WSTR_FMT "]\n\tname: [%" __WSTR_FMT "]\n\text: [%" __WSTR_FMT "]\n",
        fpath, bdir, bname, bext
    );

    if (!(fp = fopen(file, "a+"))) {
        fprintf(stdout, "\n\terror open file: [%" __WSTR_FMT "] [%s]\n", file, strerror(errno));
        return 127;
    }

    fputs(string, fp); fputs(__WS("\n"), fp);
    fputs(bdir,   fp); fputs(__WS("\n"), fp);
    fputs(bname,  fp); fputs(__WS("\n"), fp);
    fputs(bext,   fp); fputs(__WS("\n"), fp);

    fclose(fp);

#   if defined(WS_FS_REDEFINE)
    /*
        Is no declare variable as __WSTRFREE, manual free needed.
        free(bdir);
    */
#   endif

    fprintf(stdout, "\n\tstring [%" __WSTR_FMT "] ->\n\t\tfputs to file: [%" __WSTR_FMT "]\n", string, file);
    return 0;
}
