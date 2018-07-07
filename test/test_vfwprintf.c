
START_TEST (test_vfwprintf)
{
    wchar_t *test;
    int ret;

    test = (wchar_t *) malloc(512 * sizeof(wchar_t));
    ret = _swprintf(test, 512, L"%a, \x20AC, %s, %S\n", 3.14, (char*)&"test", L"\x20AC");
    //ck_assert_int_eq(ret, (int)_wcslen(test));
    ck_assert_int_eq(ret, 33);

    _fprintf(stdout, "\tTest _vfprintf:%d -> [%d] = [%ls]\n", __LINE__, ret, test);
    _fwprintf(stdout, L"\tTest _vfwprintf:%d -> [%d] = [%ls]\n", __LINE__, ret, test);
    _fwprintf(stdout, L"\tTest _vfwprintf:%d -> [%d] = [%S]\n", __LINE__, ret, test);

    free(test);
    ck_assert_msg((&vfwprintf == &_vfwprintf), 0, "vfwprintf NO equals! libc used!");
}
END_TEST
