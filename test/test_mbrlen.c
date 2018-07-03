START_TEST(test_mbrlen)
{
    char bytes[] = { 'h', 'e', 'l', 'l', 'o', '\0' };
    int  ret;
    errno = 0;

    // size 0 return -2
    ret = _mbrlen(&bytes[0], 0, NULL);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, -2);

    ret = _mbrlen(&bytes[0], 1, NULL);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);

    ret = _mbrlen(&bytes[4], 1, NULL);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);

    ret = _mbrlen(&bytes[5], 1, NULL);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    ck_assert_msg((&mbrlen == &_mbrlen), 0, "mbrlen NO equals! libc used!");
}
END_TEST
