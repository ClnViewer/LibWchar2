START_TEST(test_wcspbrk)
{
	ck_assert_msg((&wcspbrk == &_wcspbrk), 0, "wcspbrk NO equals! libc used!");
}
END_TEST
