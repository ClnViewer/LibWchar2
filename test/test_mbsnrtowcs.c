START_TEST(test_mbsnrtowcs)
{
    int ret;
    wchar_t dst[256];
    const char* src;
    const char* incomplete = "\xc2";

    memset(dst, 0, sizeof(dst));
    src = cs3;
    ret = _mbsnrtowcs(dst, &src, 0, 0, 0);
    ck_assert_int_eq(ret, 0);

    // glibc chokes on SIZE_MAX, GOOD!
    memset(dst, 0, sizeof(dst));
    src = cs3;
    ret = _mbsnrtowcs(dst, &src, 2, 123, 0);
    ck_assert_int_eq(ret, 2);
    ck_assert(dst[0] == L'H');
    ck_assert(dst[1] == L'e');
    ck_assert(&cs3[2] == src);

    memset(dst, 0, sizeof(dst));
    src = cs3;
    ret = _mbsnrtowcs(dst, &src, SIZE_MAX, 3, 0);
    ck_assert_int_eq(ret, 3);
    ck_assert(dst[0] == L'H');
    ck_assert(dst[1] == L'e');
    ck_assert(dst[2] == L'l');
    // ck_assert(&cs3[3] == src); error ?

    // Incomplete UTF-8 sequence.
    src = incomplete;
    errno = 0;
    ret = _mbsnrtowcs(dst, &src, SIZE_MAX, 3, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    src = incomplete;
    errno = 0;
    ret = _mbsnrtowcs(NULL, &src, SIZE_MAX, 3, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);

    ck_assert_msg((&mbsnrtowcs == &_mbsnrtowcs), 0, "mbsnrtowcs NO equals! libc used!");
}
END_TEST
