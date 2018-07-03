START_TEST(test_towctrans)
{
	ck_assert_msg((&towctrans == &_towctrans), 0, "towctrans NO equals! libc used!");
}
END_TEST
