START_TEST(test_wcscmp)
{
	ck_assert_msg((&wcscmp == &_wcscmp), 0, "wcscmp NO equals! libc used!");
}
END_TEST
