
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcstocscmp)
{
    ck_assert_msg((&wcstocscmp == &_wcstocscmp), 0, "wcstocscmp NO equals! libc used!");
}
END_TEST
