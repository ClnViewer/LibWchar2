START_TEST(test_wcswidth)
{
	ck_assert_msg((&wcswidth == &_wcswidth), 0, "wcswidth NO equals! libc used!");
}
END_TEST
