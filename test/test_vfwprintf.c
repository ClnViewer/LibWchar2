
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST (test_vfwprintf)
{
    wchar_t *test;
    int ret;
    size_t len;

    test = (wchar_t *) malloc(512 * sizeof(wchar_t));
    ret = _swprintf(test, 512, L"%a, \x20AC, %s, %S\n", 3.14, (char*)&"test", L"\x20AC");
    ck_assert_int_eq(ret, 33);
    len = _wcslen(test);
    // ck_assert_int_eq(ret, len); ? TODO: not equals size

    _fprintf  (stdout,  "\tTest _vfprintf::%d\t-> [%d/%zu] = %ls\n",  __LINE__, ret, len, test);
    _fwprintf (stdout, L"\tTest _vfwprintf::%d\t-> [%d/%zu] = %ls\n", __LINE__, ret, len, test);
    _fwprintf (stdout, L"\tTest _vfwprintf::%d\t-> [%d/%zu] = %S\n",  __LINE__, ret, len, test);

    free(test);
    ck_assert_msg((&vfwprintf == &_vfwprintf), 0, "vfwprintf NO equals! libc used!");
    ck_assert_msg((&wprintf == &_wprintf), 0, "wprintf NO equals! libc used!");
    ck_assert_msg((&vswprintf == &_vswprintf), 0, "vswprintf NO equals! libc used!");
    ck_assert_msg((&fwprintf == &_fwprintf), 0, "fwprintf NO equals! libc used!");
    ck_assert_msg((&swprintf == &_swprintf), 0, "swprintf NO equals! libc used!");
}
END_TEST
