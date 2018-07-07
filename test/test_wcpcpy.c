
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcpcpy)
{
    ck_assert_msg((&wcpcpy == &_wcpcpy), 0, "wcpcpy NO equals! libc used!");
}
END_TEST
