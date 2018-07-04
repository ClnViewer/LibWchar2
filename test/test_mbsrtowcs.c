START_TEST(test_mbsrtowcs)
{
    const char* VALID = "A" "\xc2\xa2" "\xe2\x82\xac" "\xf0\xa4\xad\xa2" "ef";
    // const const char* INVALID = "A" "\xc2\x20" "ef";
    // const const char* INCOMPLETE = "A" "\xc2";
    const char* valid = VALID;
    wchar_t out[4];
    int     ret;
    errno = 0;

    // 4-byte UTF-8. Check detail... Fix (table offset change to 0xffffffff)
    ret = _mbsrtowcs(out, &valid, 4, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 4);

    ck_assert_msg((&mbsrtowcs == &_mbsrtowcs), 0, "mbsrtowcs NO equals! libc used!");
}
END_TEST
