
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcslcat)
{
    ck_assert_msg((&wcslcat == &_wcslcat), 0, "wcslcat NO equals! libc used!");
}
END_TEST
