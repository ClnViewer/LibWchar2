
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_mbstowcs)
{
    ck_assert_msg((&mbstowcs == &_mbstowcs), 0, "mbstowcs NO equals! libc used!");
}
END_TEST
