
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswblank)
{
    ck_assert_msg((&iswblank == &_iswblank), 0, "iswblank NO equals! libc used!");
}
END_TEST
