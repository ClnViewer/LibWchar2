
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswxdigit)
{
    ck_assert_msg((&iswxdigit == &_iswxdigit), 0, "iswxdigit NO equals! libc used!");
}
END_TEST
