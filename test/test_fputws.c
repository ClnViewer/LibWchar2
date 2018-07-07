
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_fputws)
{
    ck_assert_msg((&fputws == &_fputws), 0, "fputws NO equals! libc used!");
}
END_TEST
