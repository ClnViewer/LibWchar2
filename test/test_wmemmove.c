START_TEST(test_wmemmove)
{
	ck_assert_msg((&wmemmove == &_wmemmove), 0, "wmemmove NO equals! libc used!");
}
END_TEST
