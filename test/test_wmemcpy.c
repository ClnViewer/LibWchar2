
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wmemcpy)
{
    wchar_t dst[32] = {0};
    wchar_t *cmp;
    int ssz = _wcslen(wcs3);

    cmp = _wmemcpy(dst, wcs3, ssz);
    ck_assert(cmp != NULL);
    // _fwprintf(stdout, L"\tTest wmemcpy:%d -> [%ls]/[%ls] %d/%d\n", __LINE__, dst, cmp, ssz, _wcslen(dst));
    ck_assert(_wcscmp(dst, wcs3) == 0);

    ck_assert_msg((&wmemcpy == &_wmemcpy), 0, "wmemcpy NO equals! libc used!");
}
END_TEST
