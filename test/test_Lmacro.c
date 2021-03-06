
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST (test_Lmacro)
{
    /* g++ -E -dD -fshort-wchar -xc++ /dev/null | grep WCHAR */

    _fwprintf(stdout, L"\n\tLibrary wchar2 version:%d -> %s\n\n", __LINE__, wchar2version());

#   if defined(__WCHAR_TYPE__)
    wchar_t a = L'a';
    if (!__builtin_types_compatible_p(typeof(a), __WCHAR_TYPE__))
    {
        ck_abort_msg("type compatible not definition as type");
    }
#   endif

#   if (defined(__WCHAR_MAX__) && (__WCHAR_MAX__ != 0xffff))
    ck_abort_msg("__WCHAR_MAX__ overflow");
#   endif

#   if (defined(__WCHAR_MIN__) && (__WCHAR_MIN__ != 0))
    ck_abort_msg("__WCHAR_MIN__ overflow");
#   endif

#   if (defined(__WCHAR_UNSIGNED__) && (__WCHAR_UNSIGNED__ != 1))
    ck_abort_msg("__WCHAR_UNSIGNED__ is not set property");
#   endif

#   if (defined(__SIZEOF_WCHAR_T__) && (__SIZEOF_WCHAR_T__ != 2))
    ck_abort_msg("__SIZEOF_WCHAR_T__ is not equal to 2");
#   endif

    ck_assert(sizeof(*L"") == sizeof(wchar_t));
    ck_assert(sizeof(wchar_t) == 2U);
}
END_TEST
