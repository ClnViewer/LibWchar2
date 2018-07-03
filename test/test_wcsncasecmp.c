START_TEST(test_wcsncasecmp)
{
	ck_assert_msg((&wcsncasecmp == &_wcsncasecmp), 0, "wcsncasecmp NO equals! libc used!");
}
END_TEST
