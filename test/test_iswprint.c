
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswprint)
{
    ck_assert_msg((&iswprint == &_iswprint), 0, "iswprint NO equals! libc used!");
}
END_TEST
