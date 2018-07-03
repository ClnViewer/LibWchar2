START_TEST(test_mbtowc)
{
    int ret;
    wchar_t out[8];
            out[0] = L'x';

    errno = 0;
    ret = _mbtowc(out, "hello", 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);
    ck_assert(out[0] == L'x');

    errno = 0;
    ret = _mbtowc(out, "hello", 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    errno = 0;
    ret = _mbtowc(out, "", 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    errno = 0;
    ret = _mbtowc(out, "hello", 1);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);
    ck_assert(out[0] == L'h');

    errno = 0;
    ret = _mbtowc(NULL, "hello", 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    errno = 0;
    ret = _mbtowc(NULL, "", 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    errno = 0;
    ret = _mbtowc(NULL, "hello", 1);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);

    errno = 0;
    ret = _mbtowc(NULL, NULL, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    ck_assert_msg((&mbtowc == &_mbtowc), 0, "mbtowc NO equals! libc used!");
}
END_TEST
