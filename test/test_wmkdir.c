
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wmkdir)
{
    wchar_t pathw[]    = L"thisdir/path/to/file";
    wchar_t pathwbad[] = L"thisdir///path//to//file";
    int ret;
    mode_t m = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;

    ret = _wmkdir(pathwbad, m);
    ck_assert_int_eq(ret, 0);
    _fprintf (stdout,  "\tTest _wmkdir:%d -> wide: [%ls] -> [%d/%d][%s]\n",
        __LINE__, pathwbad, ret, errno, strerror(errno)
    );

    ret = _wmkdir(pathw, m);
    ck_assert_int_eq(ret, 0);
    _fprintf (stdout,  "\tTest _wmkdir:%d -> wide: [%ls] -> [%d/%d][%s]\n",
        __LINE__, pathw, ret, errno, strerror(errno)
    );
}
END_TEST
