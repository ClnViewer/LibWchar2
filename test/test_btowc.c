START_TEST(test_btowc)
{
	ck_assert_msg((&btowc == &_btowc), 0, "btowc NO equals! libc used!");
}
END_TEST
