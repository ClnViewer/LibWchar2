START_TEST(test_wcsncpy)
{
	ck_assert_msg((&wcsncpy == &_wcsncpy), 0, "wcsncpy NO equals! libc used!");
}
END_TEST
