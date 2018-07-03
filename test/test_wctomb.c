START_TEST(test_wctomb)
{
    char bytes[MB_LEN_MAX] = {0};
    int ret;

    ret = _wctomb(NULL, L'h');
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    ret = _wctomb(NULL, L'\0');
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    ret = _wctomb(bytes, L'h');
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);
    ck_assert_int_eq(bytes[0], 'h');

    ret = _wctomb(bytes, L'\0');
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);
    ck_assert_int_eq(bytes[0], '\0');

    ck_assert_msg((&wctomb == &_wctomb), 0, "wctomb NO equals! libc used!");
}
END_TEST
