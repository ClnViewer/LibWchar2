START_TEST(test_iswalnum)
{
	ck_assert_msg((&iswalnum == &_iswalnum), 0, "iswalnum NO equals! libc used!");
}
END_TEST
