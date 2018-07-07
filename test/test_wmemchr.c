
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wmemchr)
{
    ck_assert_msg((&wmemchr == &_wmemchr), 0, "wmemchr NO equals! libc used!");
}
END_TEST
