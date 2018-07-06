START_TEST(test_wcsncpy)
{
    size_t ssz = _wcslen(wcs1);
    wchar_t *out, dst[(ssz * 2 + 1)];

    //_fwprintf(stdout, L"\tTest wcsncpy:%d -> %ls, %zu\n", __LINE__, wcs1, ssz);
    out = wcsncpy(dst, wcs1, ssz + 1);
    ck_assert(out != NULL);
    ck_assert(dst[11] == L'\0');
    ck_assert(_wcscmp((const wchar_t*)&dst, wcs1) == 0);
    //_fwprintf(stdout, L"\tTest wcsncpy:%d -> %ls, %zu\n", __LINE__, dst, ssz);

    ck_assert_msg((&wcsncpy == &_wcsncpy), 0, "wcsncpy NO equals! libc used!");
}
END_TEST
