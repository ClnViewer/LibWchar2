START_TEST(test_wcsstr)
{
    const wchar_t* wcs_test  = L"matches hello world, not the second hello world";
    const wchar_t* wcs_empty = L"";
    const wchar_t* wcs_good  = L"ll";
    const wchar_t* wcs_bad   = L"wort";
    const wchar_t *wcs;

    wcs = _wcsstr(wcs3, L"llo");
    ck_assert(wcs != NULL);
    // _fwprintf(stdout, L"\tTest wcsstr:%d -> %ls\n", __LINE__, wcs);

    wcs = _wcsstr(wcs_test, wcs_empty);
    ck_assert(wcs != NULL);
    ck_assert(_wcscmp(wcs, wcs_test) == 0);

    wcs = _wcsstr(wcs_test, wcs_good);
    ck_assert(wcs != NULL);
    ck_assert(_wcscmp(wcs, &wcs_test[10]) == 0);

    wcs = _wcsstr(wcs_test, wcs_bad);
    ck_assert(wcs == NULL);

    ck_assert_msg((&wcsstr == &_wcsstr), 0, "wcsstr NO equals! libc used!");
}
END_TEST
