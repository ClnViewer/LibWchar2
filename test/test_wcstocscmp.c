
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcstocscmp)
{
    int     ret;
    wchar_t src1[] = L"_this_one_string_",
            src2[] = L"_this_other_string_";
    const char *c  = "_this_one_string_",
               *cc = "_this_other_string_";

    errno = 0;

    ret = wcstocscmp(c, src1, wcslen(src1));
    _fprintf (stdout,  "\tTest wcstocscmp:%d\t-> [%s] -> [%ls][%d]\n",  __LINE__, c, src1, ret);
    ck_assert_int_eq(ret, 0);

    ret = wcstocscmp(cc, src2, wcslen(src2));
    _fprintf (stdout,  "\tTest wcstocscmp:%d\t-> [%s] -> [%ls][%d]\n",  __LINE__, cc, src2, ret);
    ck_assert_int_eq(ret, 0);

    ret = wcstocscmp(c, src2, wcslen(src2));
    _fprintf (stdout,  "\tTest wcstocscmp:%d\t-> [%s] -> [%ls][%d]\n",  __LINE__, c, src2, ret);
    ck_assert_int_eq(ret, 8);

    ck_assert(errno != EILSEQ);

    ck_assert_msg((&wcstocscmp == &_wcstocscmp), 0, "wcstocscmp NO equals! libc used!");
}
END_TEST
