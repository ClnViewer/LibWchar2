
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswctype)
{
    ck_assert_msg((&iswctype == &_iswctype), 0, "iswctype NO equals! libc used!");
}
END_TEST
