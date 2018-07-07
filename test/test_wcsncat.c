
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsncat)
{
    ck_assert_msg((&wcsncat == &_wcsncat), 0, "wcsncat NO equals! libc used!");
}
END_TEST
