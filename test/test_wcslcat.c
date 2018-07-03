START_TEST(test_wcslcat)
{
	ck_assert_msg((&wcslcat == &_wcslcat), 0, "wcslcat NO equals! libc used!");
}
END_TEST
