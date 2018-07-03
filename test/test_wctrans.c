START_TEST(test_wctrans)
{
	ck_assert_msg((&wctrans == &_wctrans), 0, "wctrans NO equals! libc used!");
}
END_TEST
