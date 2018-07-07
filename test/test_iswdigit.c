
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswdigit)
{
    ck_assert_msg((&iswdigit == &_iswdigit), 0, "iswdigit NO equals! libc used!");
}
END_TEST
