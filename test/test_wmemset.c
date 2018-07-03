START_TEST(test_wmemset)
{
	ck_assert_msg((&wmemset == &_wmemset), 0, "wmemset NO equals! libc used!");
}
END_TEST
