START_TEST(test_iswblank)
{
	ck_assert_msg((&iswblank == &_iswblank), 0, "iswblank NO equals! libc used!");
}
END_TEST
