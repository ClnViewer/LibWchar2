START_TEST(test_wcsnlen)
{
	ck_assert_msg((&wcsnlen == &_wcsnlen), 0, "wcsnlen NO equals! libc used!");
}
END_TEST
