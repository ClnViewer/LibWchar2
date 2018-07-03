START_TEST(test_mbsinit)
{
	ck_assert_msg((&mbsinit == &_mbsinit), 0, "mbsinit NO equals! libc used!");
}
END_TEST
