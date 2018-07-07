
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wmemset)
{
    wchar_t bytes[4];
    wmemset(bytes, L'x', __NELE(bytes));
    ck_assert(bytes[0] == L'x');
    ck_assert(bytes[1] == L'x');
    ck_assert(bytes[2] == L'x');
    ck_assert(bytes[3] == L'x');

    wmemset(bytes, L'y', sizeof(bytes));
    ck_assert(bytes[0] == L'y');
    ck_assert(bytes[1] == L'y');
    ck_assert(bytes[2] == L'y');
    ck_assert(bytes[3] == L'y');

    ck_assert_msg((&wmemset == &_wmemset), 0, "wmemset NO equals! libc used!");
}
END_TEST
