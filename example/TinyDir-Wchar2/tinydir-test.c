
/*
    Example use TinyDir and libwchar2
    This code to Linux only, not run in WINxx
    Origin TinyDir: https://github.com/cxong/tinydir
    gcc -E -fshort-wchar -I../../include tinydir-test.c
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
#   undef UNICODE
#  elif (!defined(USED_WCHAR2LIB) && defined(_WIN32))
#   define __WS _T
#   define __WSTR_FMT "ls"
#  else
    /* enable libchar2 */
#  endif
#else
#   define __WS(x) x
#   define __WSTR_FMT "s"
#   define __FOPEN fopen
#endif

#include "tinydir.h"

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
    tinydir_dir dir;

#   if defined(USE_COREDUMP)
    proc_coredump();
#   endif

#   if defined(USE_WCHAR2LIB)
	printf("\n\t* LINUX: Use libwchar2: type wchar_t == %zu\n\n", sizeof(wchar_t));
#   else
	printf("\n\t* LINUX: Use libc: type char\n\n");
#   endif

#if defined(UNICODE)
	printf("\n\t* Unicode mode enable: type wchar_t == %zu\n\n", sizeof(wchar_t));
#else
	printf("\n\t* Unicode mode disable: type char\n\n");
#endif

	if (tinydir_open(&dir, __WS(".")) == -1)
	{
		perror("Error opening file");
		goto bail;
	}

	while (dir.has_next)
	{
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1)
		{
			perror("Error getting file");
			goto bail;
		}

		printf("\t- %" __WSTR_FMT, file.name);
		if (file.is_dir)
		{
			printf("/");
		}
		printf("\n");

		if (tinydir_next(&dir) == -1)
		{
			perror("Error getting next file");
			goto bail;
		}
	}

#   if defined(_MSC_VER)
    getchar();
#   endif

bail:
	tinydir_close(&dir);
	return 0;
}
