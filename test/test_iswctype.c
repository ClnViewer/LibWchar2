START_TEST(test_iswctype)
{
	ck_assert_msg((&iswctype == &_iswctype), 0, "iswctype NO equals! libc used!");
}
END_TEST
