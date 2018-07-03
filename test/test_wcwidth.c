START_TEST(test_wcwidth)
{
	ck_assert_msg((&wcwidth == &_wcwidth), 0, "wcwidth NO equals! libc used!");
}
END_TEST
