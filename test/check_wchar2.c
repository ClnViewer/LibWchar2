
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
