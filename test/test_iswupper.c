START_TEST(test_iswupper)
{
	ck_assert_msg((&iswupper == &_iswupper), 0, "iswupper NO equals! libc used!");
}
END_TEST
