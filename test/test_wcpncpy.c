
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcpncpy)
{
    ck_assert_msg((&wcpncpy == &_wcpncpy), 0, "wcpncpy NO equals! libc used!");
}
END_TEST
