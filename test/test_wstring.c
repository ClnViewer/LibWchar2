
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wstring)
{
    size_t ret;
    wchar_t src1[] = L"_this_one_string_",
            src2[] = L"_this_other_string_",
            src3[] = L".",
            endw[] = L"_this_one_string_._this_other_string_";
    wchar_t *tout, tstr[] = L"2018-07-24T19:03:18Z", tres[] = L"07:03PM";
    string_ws  dst = {NULL, 0};

    ret = wstring_append(&dst, src1, 0);
    ck_assert_int_eq(ret, 17);
    ret = wstring_append(&dst, src3, 0);
    ck_assert_int_eq(ret, 18);
    ret = wstring_append(&dst, src2, _wcslen(src2));
    ck_assert_int_eq(ret, 37);

    _fprintf (stdout,  "\tTest wstring_append:%d\t-> wide: [%ls][%zu] : [%zu]\n",  __LINE__, dst.str, dst.sz, ret);
    ck_assert(_wcscmp(dst.str, endw) == 0);
    ck_assert_int_eq(_wcslen(dst.str), 37);
    wstring_free(&dst);

    // cppcheck-suppress varFuncNullUB
    ret = wstring_appends(&dst, src1, src3, src2);
    ck_assert_int_eq(ret, 37);
    _fprintf (stdout,  "\tTest wstring_appends:%d\t-> wide: [%ls][%zu] : [%zu]\n",  __LINE__, dst.str, dst.sz, ret);
    ck_assert(_wcscmp(dst.str, endw) == 0);
    wstring_free(&dst);

    ret = wstring_format(&dst, L"%S.%S", src1, src2);
    ck_assert_int_eq(ret, 37);
    _fprintf (stdout,  "\tTest wstring_format:%d\t-> wide: [%ls][%zu] : [%zu]\n",  __LINE__, dst.str, dst.sz, ret);
    ck_assert(_wcscmp(dst.str, endw) == 0);
    wstring_free(&dst);

    tout = wstring_timeformat(tstr, 0, L"%Y-%m-%dT%H:%M:%S%Ez", L"%I:%M%p");
    ck_assert(tout != NULL);
    _fprintf (stdout,  "\tTest wstring_time:%d\t-> wide: [%ls] <-> [%ls]\n", __LINE__, tstr, tout);
    ck_assert(_wcscmp(tout, tres) == 0);
    free(tout);
}
END_TEST
