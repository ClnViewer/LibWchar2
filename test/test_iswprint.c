START_TEST(test_iswprint)
{
	ck_assert_msg((&iswprint == &_iswprint), 0, "iswprint NO equals! libc used!");
}
END_TEST
