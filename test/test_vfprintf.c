
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_vfprintf)
{
    ck_assert_msg((&vfprintf == &_vfprintf), 0, "vfprintf NO equals! libc used!");
    ck_assert_msg((&vsnprintf == &_vsnprintf), 0, "vsnprintf NO equals! libc used!");
    ck_assert_msg((&fprintf == &_fprintf), 0, "fprintf NO equals! libc used!");
    ck_assert_msg((&snprintf == &_snprintf), 0, "snprintf NO equals! libc used!");
}
END_TEST
