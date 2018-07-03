START_TEST(test_wcpcpy)
{
	ck_assert_msg((&wcpcpy == &_wcpcpy), 0, "wcpcpy NO equals! libc used!");
}
END_TEST
