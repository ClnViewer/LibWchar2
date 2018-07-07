
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_towctrans)
{
    wchar_t wcha = L'a', wchA = L'A', wret;

    wret = _towlower(wchA);
    ck_assert_int_eq(wret, wcha);

    wret = _towupper(wcha);
    ck_assert_int_eq(wret, wchA);

    ck_assert_msg((&towctrans == &_towctrans), 0, "towctrans NO equals! libc used!");
}
END_TEST
