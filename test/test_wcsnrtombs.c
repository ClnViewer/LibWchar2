
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsnrtombs)
{
    ck_assert_msg((&wcsnrtombs == &_wcsnrtombs), 0, "wcsnrtombs NO equals! libc used!");
}
END_TEST
