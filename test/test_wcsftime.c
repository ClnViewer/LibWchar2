
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsftime)
{
    ck_assert_msg((&wcsftime == &_wcsftime), 0, "wcsftime NO equals! libc used!");
}
END_TEST
