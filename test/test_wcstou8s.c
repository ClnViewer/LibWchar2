
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wcstou8s)
{
    char *cs = malloc(wcstou8s(NULL, wcs1) + 1);
    int ret = wcstou8s(cs, wcs1),
        len = strlen(cs),
        cmp = memcmp((void*)cs1, (void*)cs, len);
    // printf("%s [%d/%d/%d]\n", cs, _wcslen(wcs1), len, cmp);
    free(cs);
    ck_assert_int_eq(ret, len);
    ck_assert_int_eq(cmp, 0);
    ck_assert_msg((&wcstou8s == &_wcstou8s), 0, "wcstou8s NO equals! libc used!");
}
END_TEST
