
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcscat)
{
    ck_assert_msg((&wcscat == &_wcscat), 0, "wcscat NO equals! libc used!");
}
END_TEST
