START_TEST(test_wcsspn)
{
	ck_assert_msg((&wcsspn == &_wcsspn), 0, "wcsspn NO equals! libc used!");
}
END_TEST
