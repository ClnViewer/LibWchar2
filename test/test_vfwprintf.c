
START_TEST (test_vfwprintf)
{
    wchar_t *test;
    int ret;

    test = (wchar_t *) malloc(512 * sizeof(wchar_t));
    ret = _swprintf(test, 512, L"%a, \x20AC, %s, %S\n", 3.14, (char*)&"test", L"\x20AC");

    //* NOT WORK 
_fprintf(stdout, "[%ls] [%d]\n", test, ret);
    // 
_fwprintf(stdout, L"[%ls] [%d]\n", test, ret);

    free(test);
    ck_assert_int_eq(ret, 34); // 33!
    ck_assert_msg((&vfwprintf == &_vfwprintf), 0, "vfwprintf NO equals! libc used!");
}
END_TEST
