
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */


START_TEST(test_wmemmove)
{
    const wchar_t wcs[] = L"This is a test of something or other.....";
    wchar_t dst[256] = {0}, *wcsp;

    wcsp = wmemmove(dst, wcs, __NELE(wcs));
    ck_assert(wcsp != NULL);
    ck_assert(_wcscmp(dst, wcs) == 0);

    ck_assert_msg((&wmemmove == &_wmemmove), 0, "wmemmove NO equals! libc used!");
}
END_TEST
