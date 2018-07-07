START_TEST(test_vfprintf)
{
    ck_assert_msg((&vfprintf == &_vfprintf), 0, "vfprintf NO equals! libc used!");
}
END_TEST
