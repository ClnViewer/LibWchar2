START_TEST(test_mbsnrtowcs)
{
	ck_assert_msg((&mbsnrtowcs == &_mbsnrtowcs), 0, "mbsnrtowcs NO equals! libc used!");
}
END_TEST
