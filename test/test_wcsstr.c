START_TEST(test_wcsstr)
{
	ck_assert_msg((&wcsstr == &_wcsstr), 0, "wcsstr NO equals! libc used!");
}
END_TEST
