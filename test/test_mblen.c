START_TEST(test_mblen)
{
    ck_assert_msg((&mblen == &_mblen), 0, "mblen NO equals! libc used!");
}
END_TEST
