
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_iswupper)
{
    wchar_t wcha = L'a', wchA = L'A';
    ck_assert(_iswupper(wchA));
    ck_assert(!_iswupper(wcha));

    ck_assert_msg((&iswupper == &_iswupper), 0, "iswupper NO equals! libc used!");
}
END_TEST
