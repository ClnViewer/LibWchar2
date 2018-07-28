
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsptime)
{
    const wchar_t *wtst = L"2018-07-24T19:03:18Z";
    wchar_t *wc;
    struct tm tm;
    time_t t;

    wc = _wcsptime(wtst, L"%Y-%m-%dT%H:%M:%S%Ez", &tm);
    ck_assert(wc == NULL);
    t = mktime(&tm);
    ck_assert((unsigned long)t == 1532444598UL);
    _fwprintf(stdout, L"\tTest _wcsptime:%d\t-> time: [%lu], %s\n", __LINE__, (unsigned long)t, ctime(&t));

    ck_assert_msg((&wcsptime == &_wcsptime), 0, "wcsptime NO equals! libc used!");
}
END_TEST
