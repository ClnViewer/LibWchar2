START_TEST(test_wmemcpy)
{
	ck_assert_msg((&wmemcpy == &_wmemcpy), 0, "wmemcpy NO equals! libc used!");
}
END_TEST
