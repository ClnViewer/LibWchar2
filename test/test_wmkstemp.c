
/*
    MIT License
    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2
 */

START_TEST(test_wmkstemp)
{
    wchar_t mkstemplate[] = L"/tmp/my-tmpfileXXXXXX";
    int ret;

    ret = wmkstemp(mkstemplate);
    ck_assert(ret != -1);
    _fprintf (stdout,  "\tTest wmkstemp:%d\t-> wide: [%ls] fd: [%d] [%d]:[%s]\n",
        __LINE__, mkstemplate, ret, errno, strerror(errno)
    );
    close(ret);
    _wremove(mkstemplate);
}
END_TEST
