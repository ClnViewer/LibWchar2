
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wctrans)
{
    ck_assert_msg((&wctrans == &_wctrans), 0, "wctrans NO equals! libc used!");
}
END_TEST
