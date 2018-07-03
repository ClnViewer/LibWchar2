START_TEST(test_wmemchr)
{
	ck_assert_msg((&wmemchr == &_wmemchr), 0, "wmemchr NO equals! libc used!");
}
END_TEST
