
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST (test_Lmacro)
{
    int ret = (sizeof(*L"") == sizeof(wchar_t));

    ck_assert_int_eq(ret, 1);
}
END_TEST
