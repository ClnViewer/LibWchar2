START_TEST(test_wcprint)
{
	ck_assert_msg((&wcprint == &_wcprint), 0, "wcprint NO equals! libc used!");
}
END_TEST
