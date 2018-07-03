START_TEST(test_iswcntrl)
{
	ck_assert_msg((&iswcntrl == &_iswcntrl), 0, "iswcntrl NO equals! libc used!");
}
END_TEST
