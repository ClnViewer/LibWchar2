START_TEST(test_fputws)
{
	ck_assert_msg((&fputws == &_fputws), 0, "fputws NO equals! libc used!");
}
END_TEST
