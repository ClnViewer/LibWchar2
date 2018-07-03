START_TEST(test_fputwc)
{
	ck_assert_msg((&fputwc == &_fputwc), 0, "fputwc NO equals! libc used!");
}
END_TEST
