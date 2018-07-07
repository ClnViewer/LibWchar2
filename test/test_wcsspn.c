
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsspn)
{
    ck_assert_msg((&wcsspn == &_wcsspn), 0, "wcsspn NO equals! libc used!");
}
END_TEST
