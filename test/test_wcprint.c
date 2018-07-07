
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcprint)
{
    ck_assert_msg((&wcprint == &_wcprint), 0, "wcprint NO equals! libc used!");
}
END_TEST
