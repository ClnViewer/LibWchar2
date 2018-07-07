
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcslcpy)
{
    ck_assert_msg((&wcslcpy == &_wcslcpy), 0, "wcslcpy NO equals! libc used!");
}
END_TEST
