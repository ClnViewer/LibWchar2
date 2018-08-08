
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcsnlen)
{
    size_t ret;

    ret = _wcslen(wcs1);
    ck_assert_int_eq(ret, 11U);

    ret = _wcslen(wcs3);
    ck_assert_int_eq(ret, 13U);

    ck_assert_msg((&wcsnlen == &_wcsnlen), 0, "wcsnlen NO equals! libc used!");
}
END_TEST
