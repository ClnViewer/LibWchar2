START_TEST(test_iswlower)
{
	ck_assert_msg((&iswlower == &_iswlower), 0, "iswlower NO equals! libc used!");
}
END_TEST
