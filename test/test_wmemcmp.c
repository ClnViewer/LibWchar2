START_TEST(test_wmemcmp)
{
	ck_assert_msg((&wmemcmp == &_wmemcmp), 0, "wmemcmp NO equals! libc used!");
}
END_TEST
