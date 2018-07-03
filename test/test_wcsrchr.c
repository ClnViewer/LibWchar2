START_TEST(test_wcsrchr)
{
    static const wchar_t wstr[] = L"abcda";
    int ret;
    errno = 0;

    //_fwprintf(stdout, L"%ls\n", _wcsrchr(wstr, L'b'));
    ret = _wmemcmp(wstr + 1, _wcsrchr(wstr, L'b'),  4);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    ret = wmemcmp(wstr + 2, _wcsrchr(wstr, L'c'),  3);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    ret = wmemcmp(wstr + 3, _wcsrchr(wstr, L'd'),  2);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    ret = wmemcmp(wstr + 4, _wcsrchr(wstr, L'a'),  1);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    ck_assert_msg((&_wcsrchr == &_wcsrchr), 0, "wcsrchr NO equals! libc used!");
}
END_TEST
