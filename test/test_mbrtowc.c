
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_mbrtowc)
{
    wchar_t out[8], wc;
    int ret;
    out[0] = L'x';
    errno  = 0;

    errno = 0;
    ret = _mbrtowc(NULL, "hello", 0, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, -2);

    errno = 0;
    ret = _mbrtowc(NULL, "", 0, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, -2);

    errno = 0;
    ret = _mbrtowc(NULL, "hello", 1, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);

    errno = 0;
    ret = _mbrtowc(NULL, NULL, 0, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 0);

    errno = 0;
    ret = _mbrtowc(out, "hello", 0, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, -2);
    ck_assert(out[0] == L'x');

    errno = 0;
    ret = _mbrtowc(out, "hello", 0, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, -2);

    errno = 0;
    ret = _mbrtowc(out, "", 0, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, -2);

    errno = 0;
    ret = _mbrtowc(out, "hello", 1, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);
    ck_assert(out[0] == L'h');

    // 1-byte UTF-8. OK
    errno = 0;
    ret = _mbrtowc(out, "abcdef", 6, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);

    // 2-byte UTF-8. GOOD!! Fix (table offset change to 0xffffffff)
    errno = 0;
    ret = _mbrtowc(out, "\xc2\xa2" "cdef", 6, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 2);

    // 3-byte UTF-8. GOOD!! Fix
    errno = 0;
    ret = _mbrtowc(out, "\xe2\x82\xac" "def", 6, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 3);

    // 4-byte UTF-8. GOOD!! Fix
    errno = 0;
    ret = _mbrtowc(out, "\xf0\xa4\xad\xa2" "ef", 6, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 4);

    // Illegal 5-byte UTF-8.
    errno = 0;
    ret = _mbrtowc(out, "\xf8\xa1\xa2\xa3\xa4" "f", 6, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    // Illegal over-long sequence.
    errno = 0;
    ret = _mbrtowc(out, "\xf0\x82\x82\xac" "ef", 6, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    // 1-byte character. GOOD!
    errno = 0;
    ret = _mbrtowc(&wc, "x", MB_CUR_MAX, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1);
    _fwprintf(stdout, L"\tTest _mbrtowc::%d\t-> %lc == x, %d (%s)\n", __LINE__, wc, ret,
        test_status(wc == L'x')
    );
    ck_assert(wc == L'x');

    // 2-byte character. probably BAD?
    errno = 0;
    ret = _mbrtowc(&wc, "\xc2\xa2", MB_CUR_MAX, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 2);
    _fwprintf(stdout, L"\tTest _mbrtowc::%d\t-> %lc == %lc, %d (%s)\n", __LINE__, wc, wc2_mbrtowc, ret,
        test_status(wc == wc2_mbrtowc)
    );
    // TODO: error off
    //ck_assert(wc == wc2_mbrtowc);

    // 3-byte character. GOOD!
    errno = 0;
    ret = _mbrtowc(&wc, "\xe2\x82\xac", MB_CUR_MAX, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 3);
    _fwprintf(stdout, L"\tTest _mbrtowc::%d\t-> %lc == %lc, %d (%s)\n", __LINE__, wc, wc3_mbrtowc, ret,
        test_status(wc == wc3_mbrtowc)
    );
    ck_assert(wc == wc3_mbrtowc);

    // Invalid 2-byte
    errno = 0;
    ret = _mbrtowc(&wc, "\xc2", 1, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, -2);

    errno = 0;
    ret = _mbrtowc(&wc, "\x20" "c", 2, 0);
    ck_assert(errno == EILSEQ); // this not work if remove mbstate ?
    ck_assert_int_eq(ret, -1);

    // Invalid multi byte continuation.
    errno = 0;
    ret = _mbrtowc(&wc, "\xc2", 1, 0);
    ck_assert(errno != EILSEQ); // TODO: ? no set errors ??
    ck_assert_int_eq(ret, -2);

    ck_assert_msg((&mbrtowc == &_mbrtowc), 0, "mbrtowc NO equals! libc used!");
}
END_TEST
