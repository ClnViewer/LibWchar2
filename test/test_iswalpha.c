
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswalpha)
{
    ck_assert_msg((&iswalpha == &_iswalpha), 0, "iswalpha NO equals! libc used!");
}
END_TEST
