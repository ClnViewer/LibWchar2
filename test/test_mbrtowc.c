START_TEST(test_mbrtowc)
{
    wchar_t out[8];
    int ret;
    out[0] = L'x';
    errno  = 0;

    ret = _mbrtowc(NULL, "hello", 0, 0);
    ck_assert_int_eq(ret, -2);

    ret = _mbrtowc(NULL, "", 0, 0);
    ck_assert_int_eq(ret, -2);

    ret = _mbrtowc(NULL, "hello", 1, 0);
    ck_assert_int_eq(ret, 1);

    ret = _mbrtowc(NULL, NULL, 0, 0);
    ck_assert_int_eq(ret, 0);

    ret = _mbrtowc(out, "hello", 0, 0);
    ck_assert_int_eq(ret, -2);
    ck_assert(out[0] == L'x');

    ret = _mbrtowc(out, "hello", 0, 0);
    ck_assert_int_eq(ret, -2);

    ret = _mbrtowc(out, "", 0, 0);
    ck_assert_int_eq(ret, -2);

    ret = _mbrtowc(out, "hello", 1, 0);
    ck_assert_int_eq(ret, 1);
    ck_assert(out[0] == L'h');

    // 1-byte UTF-8. OK
    ret = _mbrtowc(out, "abcdef", 6, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);

    // 2-byte UTF-8. BAD
    ret = _mbrtowc(out, "\xc2\xa2" "cdef", 6, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    // 3-byte UTF-8. BAD
    ret = _mbrtowc(out, "\xe2\x82\xac" "def", 6, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    // 4-byte UTF-8. BAD
    ret = _mbrtowc(out, "\xf0\xa4\xad\xa2" "ef", 6, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    // Illegal 5-byte UTF-8.
    ret = _mbrtowc(out, "\xf8\xa1\xa2\xa3\xa4" "f", 6, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    // Illegal over-long sequence.
    ret = _mbrtowc(out, "\xf0\x82\x82\xac" "ef", 6, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    ck_assert_msg((&mbrtowc == &_mbrtowc), 0, "mbrtowc NO equals! libc used!");
}
END_TEST
