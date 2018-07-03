START_TEST(test_wcstok)
{
	ck_assert_msg((&wcstok == &_wcstok), 0, "wcstok NO equals! libc used!");
}
END_TEST
