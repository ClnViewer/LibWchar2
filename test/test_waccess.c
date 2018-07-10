
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

static const char * __access_error(access_e x)
{
    return (const char *)((x == ISERROR) ? "Error check" :
            ((x == ISFIL) ? "is a Regular file" :
             ((x == ISLNK) ? "is a Symbolic link" :
              ((x == ISDIR) ? "is a Directory" : "Unknown result"))));

}

START_TEST(test_waccess)
{

    access_e ret;
    wchar_t  pathw_dir[] = L"thisdir/path/to/file";
    wchar_t  pathw_file[] = L"../configure";
    wchar_t  pathw_bad[] = L"../cfg-not-found";

    ret = _waccess(pathw_dir, F_OK);
    _fprintf (stdout,  "\tTest _waccess:%d\t-> return: [%d][%s]\n",  __LINE__,
        ret, __access_error(ret)
    );
    ck_assert_int_eq(ret, ISDIR);

    ret = _waccess(pathw_file, F_OK);
    _fprintf (stdout,  "\tTest _waccess:%d\t-> return: [%d][%s]\n",  __LINE__,
        ret, __access_error(ret)
    );
    ck_assert_int_eq(ret, ISFIL);

    ret = _waccess(pathw_bad, F_OK);
    _fprintf (stdout,  "\tTest _waccess:%d\t-> return: [%d][%s]\n",  __LINE__,
        ret, __access_error(ret)
    );
    ck_assert_int_eq(ret, ISERROR);

}
END_TEST
