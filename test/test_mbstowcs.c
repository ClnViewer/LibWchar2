START_TEST(test_mbstowcs)
{
	ck_assert_msg((&mbstowcs == &_mbstowcs), 0, "mbstowcs NO equals! libc used!");
}
END_TEST
