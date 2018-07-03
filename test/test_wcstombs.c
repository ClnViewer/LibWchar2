START_TEST(test_wcstombs)
{
    const wchar_t  chars[] = { L'h', L'e', L'l', L'l', L'o', L'\0' };
    int            ret;
    errno                  = 0;

    // Given a NULL destination, these functions count valid characters.
    ret = _wcstombs(NULL, chars, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);

    ret = _wcstombs(NULL, chars, 4);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);

    ret = _wcstombs(NULL, chars, 256);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);

    ck_assert_msg((&wcstombs == &_wcstombs), 0, "wcstombs NO equals! libc used!");
}
END_TEST
