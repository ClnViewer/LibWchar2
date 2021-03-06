
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wbasename)
{
    char    *outc;
    wchar_t *outw, *outwfree;
    wchar_t pathw[] = L"/this//path///to/////file.zip";
    char    pathc[] =  "/this////path//to///file.zip";
    string_ws wss   = { (wchar_t*)&pathw, 0 };

    _fprintf (stdout,  "\tTest SOURCE:%d\t\t-> wide: [%ls]\n\t\t\t\t-> char: [%s]\n",  __LINE__, pathw, pathc);

    outw = _wbasename(pathw);
    _fprintf (stdout,  "\tTest _wbasename:%d\t-> wide: [%ls]\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outw = _wbaseext(pathw);
    _fprintf (stdout,  "\tTest _wbaseext::%d\t-> wide: [%ls]\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"zip") == 0);

    outwfree = _wbasedir(pathw, 0);
    _fprintf (stdout,  "\tTest _wbasedir::%d\t-> wide: [%ls]\n",  __LINE__, outwfree);
    ck_assert(_wcscmp(outwfree, L"/this/path/to") == 0);
    if (outwfree) { __autofree(&outwfree); }

    outwfree = _wbasedir(pathw, 1);
    _fprintf (stdout,  "\tTest _wbasedir::%d\t-> wide: [%ls] + separator\n",  __LINE__, outwfree);
    ck_assert(_wcscmp(outwfree, L"/this/path/to/") == 0);
    if (outwfree) { __autofree(&outwfree); }

    outwfree = wbasedir_ws(&wss, 1);
    _fprintf (stdout,  "\tTest wbasedir_ws:%d\t-> wide: [%ls] - manual (string_ws)\n",  __LINE__, outwfree);
    ck_assert(_wcscmp(outwfree, L"/this/path/to/") == 0);
    if (outwfree) { __autofree(&outwfree); }

    outwfree = wbasedir((wchar_t*)&pathw, 1);
    _fprintf (stdout,  "\tTest  wbasedir::%d\t-> wide: [%ls] - auto (wchar_t[])\n",  __LINE__, outwfree);
    ck_assert(_wcscmp(outwfree, L"/this/path/to/") == 0);
    if (outwfree) { __autofree(&outwfree); }

    outwfree = wbasedir((string_ws*)&wss, 1);
    _fprintf (stdout,  "\tTest  wbasedir::%d\t-> wide: [%ls] - auto (string_ws)\n",  __LINE__, outwfree);
    ck_assert(_wcscmp(outwfree, L"/this/path/to/") == 0);
    if (outwfree) { __autofree(&outwfree); }

    outwfree = wbasedir((wchar_t*)&pathw, 1);
    _fprintf (stdout,  "\tTest  wbasedir::%d\t-> wide: [%ls] - auto (wchar_t)\n",  __LINE__, outwfree);
    ck_assert(_wcscmp(outwfree, L"/this/path/to/") == 0);
    if (outwfree) { __autofree(&outwfree); }

    outc = (char*) wbasedir((char*)&pathc, 1);
    _fprintf (stdout,  "\tTest  wbasedir::%d\t-> char: [%s] - auto (char)\n",  __LINE__, outc);
    ck_assert_str_eq(outc, "/this/path/to/");
    if (outc) { __autofree(&outc); }

    outw = (wchar_t*) _wbasename_selector(1, (void*)pathw);
    _fprintf (stdout,  "\tTest _wbasename:%d\t-> wide: [%ls] - manual (wchar_t[])\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outw = (wchar_t*) _wbasename_selector(2, (void*)&wss);
    _fprintf (stdout,  "\tTest _wbasename:%d\t-> wide: [%ls] - manual (string_ws)\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outw = (wchar_t*) wbasename(&wss);
    _fprintf (stdout,  "\tTest wbasename::%d\t-> wide: [%ls] - auto (string_ws)\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outw = (wchar_t*) wbasename((wchar_t*)&pathw);
    _fprintf (stdout,  "\tTest wbasename::%d\t-> wide: [%ls] - auto (wchar_t*)\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outc = (char*) wbasename((char*)&pathc);
    _fprintf (stdout,  "\tTest wbasename::%d\t-> char: [%s] - auto (char*)\n",  __LINE__, outc);
    ck_assert_str_eq(outc, "file.zip");
}
END_TEST
