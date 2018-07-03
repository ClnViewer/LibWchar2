START_TEST(test_iswgraph)
{
	ck_assert_msg((&iswgraph == &_iswgraph), 0, "iswgraph NO equals! libc used!");
}
END_TEST
