START_TEST(test_wcstocscmp)
{
	ck_assert_msg((&wcstocscmp == &_wcstocscmp), 0, "wcstocscmp NO equals! libc used!");
}
END_TEST
