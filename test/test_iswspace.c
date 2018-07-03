START_TEST(test_iswspace)
{
	ck_assert_msg((&iswspace == &_iswspace), 0, "iswspace NO equals! libc used!");
}
END_TEST
