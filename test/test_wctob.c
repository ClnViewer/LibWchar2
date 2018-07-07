
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wctob)
{
    ck_assert_msg((&wctob == &_wctob), 0, "wctob NO equals! libc used!");
}
END_TEST
