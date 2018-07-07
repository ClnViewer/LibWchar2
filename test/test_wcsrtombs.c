
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST (test_wcsrtombs)
{
    const wchar_t  chars[] = { L'h', L'e', L'l', L'l', L'o', L'\0' };
    wchar_t       *string1 = L"Hello! \x20AC Hello!";
    const wchar_t *src     = NULL;
    char bytes[BUFSIZ]     = {0};
    int            ret;
    errno                  = 0;

    src = string1;
    ret = _wcsrtombs(bytes, &src, sizeof(bytes), 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 17);
    ck_assert(src == NULL); // All input consumed!

    src = chars;
    ret = _wcsrtombs(NULL, &src, 0, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);
    ck_assert(src != NULL);

    ret = _wcsrtombs(NULL, &src, 4, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);
    ck_assert(src != NULL);

    ret = _wcsrtombs(NULL, &src, 256, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);
    ck_assert(src != NULL);

    memset(bytes, 'x', sizeof(bytes));
    src = chars;
    ret = _wcsrtombs(bytes, &src, sizeof(bytes), 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);
    ck_assert_str_eq("hello", bytes);
    ck_assert(src == NULL);

    memset(bytes, 'x', sizeof(bytes));
    src = chars;
    ret = _wcsrtombs(bytes, &src, 4, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 4);
    bytes[5] = 0;
    ck_assert_str_eq("hellx", bytes);
    ck_assert(src == NULL);

    memset(bytes, 'x', sizeof(bytes));
    src = chars;
    ret = _wcsrtombs(bytes, &src, 256, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);
    ck_assert_str_eq("hello", bytes);
    ck_assert(src == NULL);

    memset(bytes, 'x', sizeof(bytes));
    src = chars;
    ret = _wcsrtombs(bytes, &src, 6, 0);
    ck_assert(errno != EILSEQ);
    ck_assert_int_eq(ret, 5);
    ck_assert_str_eq("hello", bytes);
    ck_assert(src == NULL);

    //ck_assert(_wcscmp((const wchar_t *)&chars, src) == 0);

    ck_assert_msg((&wcsrtombs == &_wcsrtombs), 0, "wcsrtombs NO equals! libc used!");
}
END_TEST
