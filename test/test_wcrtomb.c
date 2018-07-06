START_TEST(test_wcrtomb)
{
    char bytes[MB_LEN_MAX] = {0};
    int  ret;
    errno = 0;

    ret = _wcrtomb(NULL,  L'h', 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);

    ret = _wcrtomb(NULL,  L'\0', 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);

    // 1-byte UTF8
    ret = _wcrtomb(bytes, L'\0', 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);
    ck_assert(bytes[0] == '\0');

    ret = _wcrtomb(bytes,  L'h', 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);
    ck_assert(bytes[0] == 'h');

    // 2-byte UTF8
    memset(bytes, 0, sizeof(bytes));
    ret = _wcrtomb(bytes, 0x00a2, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 2); // TODO: return == -1 ?
    ck_assert(bytes[0] == '\xc2');
    ck_assert(bytes[1] == '\xa2');

    // 3-byte UTF8
    memset(bytes, 0, sizeof(bytes));
    ret = _wcrtomb(bytes, 0x20ac, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 3);
    ck_assert(bytes[0] == '\xe2');
    ck_assert(bytes[1] == '\x82');
    ck_assert(bytes[2] == '\xac');

    // 3-byte UTF8 is max value
    memset(bytes, 0, sizeof(bytes));
    ret = _wcrtomb(bytes, 0xffff, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 3);
    ck_assert(bytes[0] == '\xef');
    ck_assert(bytes[1] == '\xbf');
    ck_assert(bytes[2] == '\xbf');
    ck_assert(bytes[3] == '\0');

    ck_assert_msg((&wcrtomb == &_wcrtomb), 0, "wcrtomb NO equals! libc used!");
}
END_TEST
