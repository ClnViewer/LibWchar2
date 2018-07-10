
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wbasename)
{
    char    *outc;
    wchar_t *outw, *outfree;
    wchar_t pathw[] = L"/this//path///to/////file.zip";
    char    pathc[] =  "/this////path//to///file.zip";
    string_ws wss   = { (wchar_t*)&pathw, 0 };

    _fprintf (stdout,  "\tTest SOURCE:%d -> wide: [%ls] char: [%s]\n",  __LINE__, pathw, pathc);

    outw = _wbasename(pathw);
    _fprintf (stdout,  "\tTest _wbasename:%d -> wide: [%ls]\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outw = _wbaseext(pathw);
    _fprintf (stdout,  "\tTest _wbaseext:%d  -> wide: [%ls]\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"zip") == 0);

    outfree = _wbasedir(pathw, 0);
    _fprintf (stdout,  "\tTest _wbasedir:%d  -> wide: [%ls]\n",  __LINE__, outfree);
    ck_assert(_wcscmp(outfree, L"/this/path/to") == 0);
    if (outfree) { free(outfree); outfree = NULL; }

    outfree = _wbasedir(pathw, 1);
    _fprintf (stdout,  "\tTest _wbasedir:%d  -> wide: [%ls] + separator\n",  __LINE__, outfree);
    ck_assert(_wcscmp(outfree, L"/this/path/to/") == 0);
    if (outfree) { free(outfree); outfree = NULL; }

    outfree = _wbasedir_ws(&wss, 1);
    _fprintf (stdout,  "\tTest _wbasedir:%d  -> wide: [%ls] - manual (string_ws)\n",  __LINE__, outfree);
    ck_assert(_wcscmp(outfree, L"/this/path/to/") == 0);
    if (outfree) { free(outfree); outfree = NULL; }

    outfree = wbasedir((wchar_t*)&pathw, 1);
    _fprintf (stdout,  "\tTest  wbasedir:%d  -> wide: [%ls] - auto (wchar_t[])\n",  __LINE__, outfree);
    ck_assert(_wcscmp(outfree, L"/this/path/to/") == 0);
    if (outfree) { free(outfree); outfree = NULL; }

    outfree = wbasedir((string_ws*)&wss, 1);
    _fprintf (stdout,  "\tTest  wbasedir:%d  -> wide: [%ls] - auto (string_ws)\n",  __LINE__, outfree);
    ck_assert(_wcscmp(outfree, L"/this/path/to/") == 0);
    if (outfree) { free(outfree); outfree = NULL; }

    outfree = wbasedir((wchar_t*)&pathw, 1);
    _fprintf (stdout,  "\tTest  wbasedir:%d  -> wide: [%ls] - auto (wchar_t)\n",  __LINE__, outfree);
    ck_assert(_wcscmp(outfree, L"/this/path/to/") == 0);
    if (outfree) { free(outfree); outfree = NULL; }

    outc = (char*) wbasedir((char*)&pathc, 1);
    _fprintf (stdout,  "\tTest  wbasedir:%d  -> char: [%s] - auto (char)\n",  __LINE__, outc);
    ck_assert_str_eq(outc, "/this/path/to/");
    if (outc) { free(outc); outc = NULL; }

    outw = (wchar_t*) _wbasename_selector(1, (void*)pathw);
    _fprintf (stdout,  "\tTest _wbasename:%d -> wide: [%ls] - manual (wchar_t[])\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outw = (wchar_t*) _wbasename_selector(2, (void*)&wss);
    _fprintf (stdout,  "\tTest _wbasename:%d -> wide: [%ls] - manual (string_ws)\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outw = (wchar_t*) wbasename(&wss);
    _fprintf (stdout,  "\tTest wbasename:%d  -> wide: [%ls] - auto (string_ws)\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outw = (wchar_t*) wbasename((wchar_t*)&pathw);
    _fprintf (stdout,  "\tTest wbasename:%d  -> wide: [%ls] - auto (wchar_t*)\n",  __LINE__, outw);
    ck_assert(_wcscmp(outw, L"file.zip") == 0);

    outc = (char*) wbasename((char*)&pathc);
    _fprintf (stdout,  "\tTest wbasename:%d  -> char: [%s] - auto (char*)\n",  __LINE__, outc);
    ck_assert_str_eq(outc, "file.zip");

}
END_TEST
