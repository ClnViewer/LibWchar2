
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcschr)
{
    ck_assert_msg((&wcschr == &_wcschr), 0, "wcschr NO equals! libc used!");
}
END_TEST
