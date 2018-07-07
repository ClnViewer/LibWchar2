
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsncmp)
{
    ck_assert_msg((&wcsncmp == &_wcsncmp), 0, "wcsncmp NO equals! libc used!");
}
END_TEST
