START_TEST(test_wcsncat)
{
	ck_assert_msg((&wcsncat == &_wcsncat), 0, "wcsncat NO equals! libc used!");
}
END_TEST
