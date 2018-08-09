
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcstonum)
{
    wchar_t *wret = NULL;
    const wchar_t wstr[] = L"123";
    long int lr;
    long long int llr;
    unsigned long int ulr;
    unsigned long long int ullr;

// cppcheck-suppress invalidFunctionArg
    lr = wcstol(wstr, NULL, 1);
    ck_assert_int_eq(errno, EINVAL);
    ck_assert(lr == 0L);

    lr = wcstol(wstr, NULL, 10);
    ck_assert(lr == 123L);

    llr = wcstoll(wstr, NULL, 10);
    ck_assert(llr == 123LL);

    ulr = wcstoul(wstr, NULL, 10);
    ck_assert(ulr == 123UL);

    ullr = wcstoull(wstr, NULL, 10);
    ck_assert(ullr == 123ULL);

    lr = wcstol(L"123 Other sting", &wret, 10);
    ck_assert(lr == 123L);
    ck_assert(wret != NULL);
    _fwprintf(stdout, L"\tTest wcstoXX:%d\t\t-> wide: [%ls]\n", __LINE__, wret);


    ck_assert_msg((&wcstod == &_wcstod), 0, "wcstod NO equals! libc used!");
    ck_assert_msg((&wcstof == &_wcstof), 0, "wcstof NO equals! libc used!");
    ck_assert_msg((&wcstold == &_wcstold), 0, "wcstold NO equals! libc used!");
    ck_assert_msg((&wcstol == &_wcstol), 0, "wcstol NO equals! libc used!");
    ck_assert_msg((&wcstoll == &_wcstoll), 0, "wcstoll NO equals! libc used!");
    ck_assert_msg((&wcstoul == &_wcstoul), 0, "wcstoul NO equals! libc used!");
    ck_assert_msg((&wcstoull == &_wcstoull), 0, "wcstoull NO equals! libc used!");
    ck_assert_msg((&wcstoimax == &_wcstoimax), 0, "wcstoimax NO equals! libc used!");
    ck_assert_msg((&wcstoumax == &_wcstoumax), 0, "wcstoumax NO equals! libc used!");
}
END_TEST
