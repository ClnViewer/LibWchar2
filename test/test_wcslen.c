START_TEST(test_wcslen)
{
	ck_assert_msg((&wcslen == &_wcslen), 0, "wcslen NO equals! libc used!");
}
END_TEST
