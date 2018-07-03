START_TEST(test_wcsregexp)
{
    int ret;
    wchar_t *res = wcsregexp(L"[0-9]+", L"The number is 123, indeed", &ret);
    //_fwprintf(stdout, L"%d) %ls, %d\n", __LINE__, res, ret);
    ck_assert_int_eq((res == NULL), 0);
    ck_assert_int_eq(ret, 3);
    ck_assert_msg((&wcsregexp == &_wcsregexp), 0, "wcsregexp NO equals! libc used!");
}
END_TEST
