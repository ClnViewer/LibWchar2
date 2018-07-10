
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wpathnormalize)
{
    wchar_t *outwfree;
    wchar_t  pathw[] = L"/this//path///to/////file.zip";

    outwfree = _wpathnormalize(pathw, 0);
    _fprintf (stdout,  "\tTest wpathnormalize:%d\t-> wide: [%ls]\n",  __LINE__, outwfree);
    ck_assert(_wcscmp(outwfree, L"/this/path/to/file.zip") == 0);
    if (outwfree) { __wsfree(&outwfree); }

}
END_TEST
