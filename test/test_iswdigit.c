START_TEST(test_iswdigit)
{
	ck_assert_msg((&iswdigit == &_iswdigit), 0, "iswdigit NO equals! libc used!");
}
END_TEST
