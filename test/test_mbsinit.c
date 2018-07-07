
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_mbsinit)
{
	ck_assert_msg((&mbsinit == &_mbsinit), 0, "mbsinit NO equals! libc used!");
}
END_TEST
