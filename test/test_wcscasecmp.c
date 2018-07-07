
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcscasecmp)
{
    ck_assert_msg((&wcscasecmp == &_wcscasecmp), 0, "wcscasecmp NO equals! libc used!");
}
END_TEST
