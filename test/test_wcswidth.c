START_TEST(test_wcswidth)
{
    int ret;
    unsigned int i;
    wchar_t wc_is0[] = { 0x0300, 0x20dd, 0x20dd, 0x200b };
    wchar_t wc_is2[] = { 0x4e00, 0x9fff, 0x3400, 0x4dbf }; // for wchar_t == 4 , 0x20000, 0x2a6df };

    errno  = 0;

    // Korean "crying" emoticon.
    ret = _wcwidth(wc1_wcwidth);
    ck_assert_int_eq(ret, 2);

    // Korean "laughing" emoticon.
    ret = _wcwidth(wc2_wcwidth);
    ck_assert_int_eq(ret, 2);

    // Combining grave, enclosing circle, Soft hyphen (SHY), Zero width space
    for (i = 0; i < __NELE(wc_is0); i++)
    {
        ret = _wcwidth(wc_is0[i]);
        if (ret)
        {
            _fwprintf(stdout, L"\tTest _wcswidth:%d -> return '%lc' == %d (%s)\n", __LINE__, wc_is0[i], ret,
                test_status(0)
            );
        }
        ck_assert_int_eq(ret, 0);
    }

    // Start of CJK unified block, End of CJK unified block, Start of CJK extension A block, End of CJK Ablock
    for (i = 0; i < __NELE(wc_is0); i++)
    {
        ret = _wcwidth(wc_is2[i]);
        if (ret != 2)
        {
            _fwprintf(stdout, L"\tTest _wcswidth:%d -> return '%lc' == %d (%s)\n", __LINE__, wc_is2[i], ret,
                test_status(0)
            );
        }
        ck_assert_int_eq(ret, 2);
    }

    ck_assert_msg((&wcswidth == &_wcswidth), 0, "wcswidth NO equals! libc used!");
}
END_TEST
