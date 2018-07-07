
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsncasecmp)
{
    ck_assert_msg((&wcsncasecmp == &_wcsncasecmp), 0, "wcsncasecmp NO equals! libc used!");
}
END_TEST
