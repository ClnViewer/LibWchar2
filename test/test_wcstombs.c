
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcstombs)
{
    const wchar_t  wchars[] = { L'h', L'e', L'l', L'l', L'o', L'\0' };
    const wchar_t  wchars_bad[] = { L'h', L'i', 0xffff, 0 };
    const char     cchars[] = "hello";
    size_t         ret;
    char bytes[BUFSIZ];

    // Given a NULL destination, these functions count valid characters.
    errno = 0;
    ret = _wcstombs(NULL, wchars, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5U);

    errno = 0;
    ret = _wcstombs(NULL, wchars, 4);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5U);

    errno = 0;
    ret = _wcstombs(NULL, wchars, 256);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5U);

    errno = 0;
    memset(bytes, 'x', sizeof(bytes));
    ret = _wcstombs(bytes, wchars, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, (size_t)-1);

    errno = 0;
    memset(bytes, 'x', sizeof(bytes));
    ret = _wcstombs(bytes, wchars, 4);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 4U);
    bytes[5] = 0;
    ck_assert_str_eq("hellx", bytes);

    errno = 0;
    memset(bytes, 'x', sizeof(bytes));
    ret = _wcstombs(bytes, wchars, 256);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5U);
    bytes[5] = 0;
    ck_assert_str_eq(cchars, bytes);

    errno = 0;
    memset(bytes, 'x', sizeof(bytes));
    ret = _wcstombs(bytes, wchars, 6);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5U);
    bytes[5] = 0;
    ck_assert_str_eq(cchars, bytes);

    // TODO section :)

    errno = 0;
    ret = _wcstombs(NULL, wchars_bad, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5U); // TODO: return == -1 good ?

    errno = 0;
    ret = _wcstombs(NULL, wchars_bad, 256);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5U); // TODO: return == -1 good ?

    memset(bytes, 'x', sizeof(bytes));
    errno = 0;
    ret = _wcstombs(bytes, wchars_bad, 256);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5U); // TODO: return == -1 good ?
    ck_assert(bytes[0] == L'h');
    ck_assert(bytes[1] == L'i');
    ck_assert(bytes[6] == 'x'); // TODO: bytes 2,3,4,5 is broken

    // _fwprintf(stdout, L"\tTest wcsstr:%d -> %lc == 0x%X  0x%X\n", __LINE__, bytes[2], bytes[2], wchars_bad[2]);
    // ck_assert(bytes[2] == 0xffffffef); // TODO: BAD, _wcstombs is not stoped

    ck_assert_msg((&wcstombs == &_wcstombs), 0, "wcstombs NO equals! libc used!");
}
END_TEST
