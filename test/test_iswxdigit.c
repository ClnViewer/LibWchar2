START_TEST(test_iswxdigit)
{
	ck_assert_msg((&iswxdigit == &_iswxdigit), 0, "iswxdigit NO equals! libc used!");
}
END_TEST
