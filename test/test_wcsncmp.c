START_TEST(test_wcsncmp)
{
	ck_assert_msg((&wcsncmp == &_wcsncmp), 0, "wcsncmp NO equals! libc used!");
}
END_TEST
