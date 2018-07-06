START_TEST(test_mbsrtowcs)
{
    // uselocale(LC_GLOBAL_LOCALE);

    const char *VALID = "A" "\xc2\xa2" "\xe2\x82\xac" "\xf0\xa4\xad\xa2" "ef";
    const char *INVALID0 = "\x20";
    const char *INVALID1 = "A" "\xc2\x20" "ef";
    const const char *INCOMPLETE = "A" "\xc2";
    const char *instr;
    wchar_t out[4];
    int     ret;

    // 4-byte UTF-8. Check detail... Fix (table offset change to 0xffffffff)
    errno = 0;
    instr = VALID;
    ret = _mbsrtowcs(out, &instr, 4, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 4);
    ck_assert('A'     == *instr);
    ck_assert(L'A'    == out[0]);
    ck_assert(0x00a2  == out[1]);
    ck_assert(0x20ac  == out[2]);

    // Invalid multi byte continuation.
    errno = 0;
    instr = INVALID0;
    ret = _mbsrtowcs(out, &instr, 1, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 1); // TODO: needed -1

    errno = 0;
    instr = INVALID1;
    ret = _mbsrtowcs(out, &instr, 4, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);
    ck_assert('\xc2' == instr[0]); // GOOD! == INVALID1[1]

    errno = 0;
    instr = INCOMPLETE;
    ret = _mbsrtowcs(out, &instr, 2, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1);
    ck_assert('\xc2' == instr[0]); // GOOD! == INCOMPLETE[1]


    // If dst is null, *src shouldn't be updated.
    errno = 0;
    instr = VALID;
    ret = _mbsrtowcs(NULL, &instr, 0, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 6); // GOOD!

    errno = 0;
    instr = INVALID1;
    ret = _mbsrtowcs(NULL, &instr, 0, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1); // GOOD!

    errno = 0;
    instr = INCOMPLETE;
    ret = _mbsrtowcs(NULL, &instr, 0, 0);
    ck_assert(errno == EILSEQ);
    ck_assert_int_eq(ret, -1); // GOOD!

    ck_assert_msg((&mbsrtowcs == &_mbsrtowcs), 0, "mbsrtowcs NO equals! libc used!");
}
END_TEST
