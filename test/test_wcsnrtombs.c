START_TEST(test_wcsnrtombs)
{
	ck_assert_msg((&wcsnrtombs == &_wcsnrtombs), 0, "wcsnrtombs NO equals! libc used!");
}
END_TEST
