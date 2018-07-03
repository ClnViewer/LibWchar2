START_TEST(test_wctob)
{
	ck_assert_msg((&wctob == &_wctob), 0, "wctob NO equals! libc used!");
}
END_TEST
