
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcstok)
{
    ck_assert_msg((&wcstok == &_wcstok), 0, "wcstok NO equals! libc used!");
}
END_TEST
