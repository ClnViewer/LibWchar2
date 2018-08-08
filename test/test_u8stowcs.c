
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_u8stowcs)
{
    wchar_t *wcs = malloc(u8stowcs(NULL, cs1) + 1);
    size_t ret = u8stowcs(wcs, cs1);
    // _fwprintf(stdout, L"%ls\n", wcs);
    free(wcs);

    ck_assert_int_eq(ret, 11U);
    ck_assert_msg((&u8stowcs == &_u8stowcs), 0, "u8stowcs NO equals! libc used!");
}
END_TEST
