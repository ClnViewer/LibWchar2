START_TEST(test_iswpunct)
{
	ck_assert_msg((&iswpunct == &_iswpunct), 0, "iswpunct NO equals! libc used!");
}
END_TEST
