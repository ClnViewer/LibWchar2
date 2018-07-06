START_TEST(test_iswlower)
{
    wchar_t wcha = L'a', wchA = L'A';
    ck_assert(_iswlower(wcha));
    ck_assert(!_iswlower(wchA));

    ck_assert_msg((&iswlower == &_iswlower), 0, "iswlower NO equals! libc used!");
}
END_TEST
