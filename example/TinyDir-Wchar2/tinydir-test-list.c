
/*
    Example use TinyDir and libwchar2
    This code to Linux only, not run in WINxx
    Origin TinyDir: https://github.com/cxong/tinydir
    gcc -E -fshort-wchar -I../../include tinydir-test-list.c
*/

#define UNICODE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    suppress error uintmax_t/intmax_t include this:
 */
#include <stdint.h>

#if defined(USE_WCHAR2LIB)
#  include <wchar2.h>
#endif

/*
    Sample selector, not fully
    See and use: https://github.com/ClnViewer/LibWchar2/blob/master/src/libbuild.h
 */
#if defined(UNICODE)
#  if (!defined(USED_WCHAR2LIB) && defined(__linux))
#   define __WS(x) x
#   define __WSTR_FMT "s"
#   define __FOPEN fopen
#   undef UNICODE
#  elif (!defined(USED_WCHAR2LIB) && defined(_WIN32))
#   define __WS _T
#   define __WSTR_FMT "ls"
#   define __FOPEN _wfopen
#  else
    /* enable libchar2 */
#   define __FOPEN(A,B) wfopen((__WSTR*)A,B)
#  endif
#else
#   define __WS(x) x
#   define __WSTR_FMT "s"
#   define __FOPEN fopen
#endif

#include "tinydir.h"

static const char bom[] = "\xFF\xFE";

/*
    Create core is crush, debug mode.
    Linux only.
*/
#if defined(USE_COREDUMP)
#include <sys/resource.h>
void proc_coredump(void)
{
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
}
#endif

int main(void)
{
    FILE *fp;
    tinydir_dir dir;

#   if defined(USE_COREDUMP)
    proc_coredump();
#   endif

    tinydir_open(&dir, __WS("."));

    if ((fp = __FOPEN(__WS("file-to-output"), __WS("w+"))) == NULL)
    {
        perror("Filed FOPEN: ");
        return 0;
    }

#   if defined(UNICODE)
    fwrite(bom, 1, 2, fp);
#   endif

    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);

        fprintf(fp, "\t%" __WSTR_FMT "%" __WSTR_FMT "\n",
            file.name,
            ((file.is_dir) ? __WS("/") : __WS(""))
        );
        tinydir_next(&dir);
    }

    tinydir_close(&dir);
    fclose(fp);

    return 0;
}
