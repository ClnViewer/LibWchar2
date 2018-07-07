
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcscmp)
{
    ck_assert_msg((&wcscmp == &_wcscmp), 0, "wcscmp NO equals! libc used!");
}
END_TEST
