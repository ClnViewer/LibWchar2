
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wstat)
{

    int ret;
    long opt = 0L;
    wchar_t    path[] = L"../";
    wdirent_t *entry  = NULL;
    WDIR_t    *dp     = NULL;

    _fwprintf(stdout, L"\n\tTest _wreaddir_cb:%d\t\t-> opt: NONE\n", __LINE__);
    ret = _wreaddir_cb(path, 0L, NULL, NULL);
    ck_assert(ret == 1);
    ck_assert(errno == 0);

    _fwprintf(stdout, L"\n\tTest _wreaddir_cb:%d\t\t-> opt: DIRENTRYSIZE, DIRNOROOT\n", __LINE__);
    opt = wreaddir_cb_opt(opt, DIRNOROOT);
    opt = wreaddir_cb_opt(opt, DIRENTRYSIZE);
    ret = _wreaddir_cb(path, opt, NULL, NULL);
    ck_assert(ret == 1);
    ck_assert(errno == 0);

    _fwprintf(stdout, L"\n\tTest _wreaddir_cb:%d\t\t-> opt: DIRENTRYSIZE, DIRNODIR\n", __LINE__);
    opt = 0L;
    opt = wreaddir_cb_opt(opt, DIRNODIR);
    opt = wreaddir_cb_opt(opt, DIRENTRYSIZE);
    ret = _wreaddir_cb(path, opt, NULL, NULL);
    ck_assert(ret == 1);
    ck_assert(errno == 0);

    do
    {
        dp = _wopendir(path);
        ck_assert(dp != NULL);

        _fwprintf(stdout, L"\tTest wopendir:%d\t-> begin directory %ls listing\n", __LINE__, path);

        while((entry = _wreaddir(dp)))
        {
            ck_assert(entry->d_name[0] != L'\0');
            _fwprintf(stdout, L"\t\t- [%ls]\n", entry->d_name);
            free(entry); entry = NULL;
        }

    } while (0);

    errno = 0;

    if (dp != NULL)  _wclosedir(dp);
    ck_assert(errno == 0);

    if (entry != NULL)  free(entry);

    _fwprintf(stdout, L"\tTest wopendir:%d\t-> end directory %ls listing\n", __LINE__, path);
}
END_TEST
