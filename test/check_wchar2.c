
/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sub license, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */

#if !defined(_GNU_SOURCE)
#   define _GNU_SOURCE
#elif !defined(_ISOC99_SOURCE)
#   define _ISOC99_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <locale.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>

#if defined(HAVE_CONFIG_H)
#   include "../config.h"
#endif

#if defined(HAVE_CHECK_H)
#   include <check.h>
#else
#   error "libcheck header <check.h> NOT found, run ./configure again, abort"
#endif

#if !defined(HAVE_WCHAR_H)
#   error "<wchar.h> NOT defined, run ./configure again, abort.."
#endif

#if !defined(HAVE_WCTYPE_H)
#   error "<wctype.h> NOT defined, run ./configure again, abort.."
#endif

#if defined(HAVE_SYS_RESOURCE_H)
#   include <sys/resource.h>
#endif

#if defined(HAVE_LOCALE_H)
#   include <locale.h>
#endif

#include "../include/wchar2.h"

#define __NELE(A) (sizeof(A) / sizeof(A[0]))
#define __BITBOOL(x) (!(!(x)))
#define __BITSET(arg,mask) ((arg) | (1ULL << (mask)))
#define __BITCLR(arg,mask) ((arg) & ~(1ULL << (mask)))
#define __BITTST(arg,mask) __BITBOOL((arg) & (1ULL << (mask)))
#define __BITFLP(arg,mask) ((arg) ^ (1ULL << (mask)))


#if defined(PACKAGE_STRING)
    char testinfo[]
#  if (defined(__APPLE__) || defined(__OSX__) || defined(__MACH__))
    __attribute__((section("__SEGMENT,__TESTINFO")))
#  else
    __attribute__ ((section ("TESTINFO")))
#  endif
    = PACKAGE_STRING " " __DATE__ " " __TIME__;
#endif

static const char *test_status(int x)
{
    return ((!x) ?
        (const char *)&"probably BAD?" :
        (const char *)&"GOOD!"
    );
}

#include "check_wchar2_utf8.h"
#include "test_Lmacro.c"
#include "check_wchar2_include.c"

static Suite *wchar2_suite(void)
{
    Suite *s;
    TCase *t;
    s = suite_create("Wchar2 STD");
    t = tcase_create("Core");

    tcase_add_test(t, test_Lmacro);
#   include "check_wchar2_suite.c"

    suite_add_tcase(s, t);
    return s;
}

int main(void)
{
    int n;
    Suite *s;
    SRunner *sr;

#   if defined(HAVE_SYS_RESOURCE_H)
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
#   endif

#   if defined(HAVE_LOCALE_H)
    setlocale(LC_ALL, "en_US.utf8");
#   endif

    s  = wchar2_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL); // CK_VERBOSE);
    n = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (n == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
