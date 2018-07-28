
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsftime)
{
    const char *tst = "2018-07-24T19:03:18Z";
    wchar_t wc[25],
            ws[] = L"2018-07-24 19:03:18";
    struct tm tm;
    size_t ret;

    strptime(tst, "%Y-%m-%dT%H:%M:%S%Ez", &tm);
    time_t t = mktime(&tm);

    ret = _wcsftime(wc, sizeof(wc), L"%Y-%m-%d %H:%M:%S", &tm);
    _fwprintf(stdout, L"\tTest _wcsftime:%d\t-> time: [%lu], size: [%u], wide: %ls\n", __LINE__, (unsigned long)t, ret, wc);
    ck_assert_int_eq(ret, 19);
    ck_assert(_wcscmp(ws, wc) == 0);

    ck_assert_msg((&wcsftime == &_wcsftime), 0, "wcsftime NO equals! libc used!");
}
END_TEST
