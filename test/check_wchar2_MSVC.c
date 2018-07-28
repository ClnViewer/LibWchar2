#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <wchar.h>

// devel include mode
// #include "../libwcha2-extension/src/libbuild.h"
// #include "../libwcha2-extension/src/libwcharext.h"

#if !defined(WCHAR2EXT_MSVC_ORIGIN)
#   undef WCHAR2EXT_MSVC_ORIGIN
#endif

#include "../include/wchar2ext.h"

#if defined(_MSC_VER)
#   pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
// #pragma comment(lib, "libwchar2ext.lib")
#endif

#define F_OK 0

static const char * __access_error(access_e x)
{
    return (const char *)((x == ISERROR) ? "Error check" :
                          ((x == ISFIL) ? "is a Regular file" :
                           ((x == ISLNK) ? "is a Symbolic link" :
                            ((x == ISDIR) ? "is a Directory" : "Unknown result"))));
}

#if defined(_MSC_VER)
static const char * __get_error(char errstr[], int err)
{
    (void) strerror_s(errstr, 256, err);
    return (const char*)errstr;
}
#else
static const char * __get_error(char *errstr, int err)
{
    (void) errstr;
    return (const char*)strerror(err);
}
#endif

int main(int argc, char *argv[])
{
    size_t sz;
    int ret;
    wchar_t *outw, pathw[] = L"\\this\\path\\to\\file.zip";
    wchar_t pathmkd[] = L"this\\path\\to\\file";
    string_ws dst = { NULL, 0U },
              a   = { L"_one_string_", 0U},
              aa  = { L"_two_string_", 0U },
              aaa  = { L".", 0U };
    const char wtext[] = "write text UTF8 -  просто текст";
    wchar_t wout[256];
    char    cout[(sizeof(wout) * 2)];

#   if defined(_MSC_VER)
    char errstr[256] = {0};
#   else
    char *errstr = NULL;
#   endif

    (void) argc;
    (void) argv;

    printf("\n\ti sizeof wchar_t [%u]\n", sizeof(wchar_t));

    /* low-level Function test */

    wmemset((void*)&wout, 0, wsizeof(wout));
    memset((void*)&cout, 0,  sizeof(cout));

    ret = wstring_cstows(wout, wsizeof(wout), (const char*)wtext, 0);
    printf("\n\t*(%d) wstring_cstows: [%ls][%d]\n", __LINE__, wout, ret);

    ret = wstring_wstocs(cout, sizeof(cout), (const wchar_t*)wout, 0);
    printf("\n\t*(%d) wstring_wstocs: [%s][%d]\n", __LINE__, cout, ret);

    sz = wstring_appends_(&dst, (wchar_t*)a.str, (wchar_t*)aaa.str, (wchar_t*)aa.str, NULL);
    printf("\n\t*(%d) wstring_appends: [%ls][%u] -> [%u]\n", __LINE__, dst.str, dst.sz, sz);
    wstring_free(&dst);

    sz = wstring_append(&dst, (wchar_t*)aa.str, 0);
    printf("\n\t*(%d) wstring_append: [%ls][%u] -> [%u]\n", __LINE__, dst.str, dst.sz, sz);
    wstring_free(&dst);

    sz = wstring_format(&dst, L"%ls%ls%ls", a.str, aaa.str, aa.str);
    printf("\n\t*(%d) wstring_format: [%ls][%u] -> [%u]\n", __LINE__, dst.str, dst.sz, sz);

    printf("\n\t*(%d) wcprint: ", __LINE__);
    wcprint(dst.str);
    wstring_free(&dst);

    outw = wbasename(pathw);
    printf("\n\n\t*(%d) wbasename: [%ls]\n", __LINE__, outw);

    outw = wbaseext(pathw);
    printf("\n\t*(%d) wbaseext: [%ls]\n", __LINE__, outw);

    outw = wbasedir(pathw, 0);
    printf("\n\t*(%d) wbasedir: [%ls]\n", __LINE__, outw);
    if (outw)
    {
        free(outw);
    }

    outw = wbasedir(pathw, 1);
    printf("\n\t*(%d) wbasedir: [%ls]\n", __LINE__, outw);
    if (outw)
    {
        free(outw);
    }

    ret = waccess(pathmkd, F_OK);
    printf("\n\t*(%d) waccess: [%ls] -> [%d][%s]\n", __LINE__, pathmkd, ret, __access_error(ret));

    ret = wmkdir(pathmkd, 0);
    printf("\n\t*(%d) wmkdir: [create] [%ls] -> [%d/%d][%s]\n", __LINE__, pathmkd, ret, errno, __get_error(errstr, errno));

    ret = waccess(pathmkd, F_OK);
    printf("\n\t*(%d) waccess: [%ls] -> [%d][%s]\n", __LINE__, pathmkd, ret, __access_error(ret));

    ret = wmkdir(pathmkd, 0);
    printf("\n\t*(%d) wmkdir: [exist]  [%ls] -> [%d/%d][%s]\n", __LINE__, pathmkd, ret, errno, __get_error(errstr, errno));

    do
    {
        FILE *fp;
        errno = 0;
        if (!(fp = wfopen(__WS("test-write.txt"), __WS("a+"))))
        {
            printf("\n\t*(%d) wfopen: [error] -> [%d][%s]\n", __LINE__, errno, __get_error(errstr, errno));
            break;
        }
        printf("\n\t*(%d) wfopen: [ok] -> [%d][%s]\n", __LINE__, errno, __get_error(errstr, errno));
        errno = 0;
        ret = fwrite((void*)wtext, sizeof(char), sizeof(wtext), fp);
        printf("\n\t*(%d) fwrite: [status]  -> [%d/%d][%s]\n", __LINE__, ret, errno, __get_error(errstr, errno));
        fclose(fp);

    }
    while (0);

    do
    {
        time_t t;
        struct tm *tmi = NULL, tms = {0};
        wchar_t buffer [180] = {0};

        t = time(NULL);

#       if defined(_MSC_VER)
        if (localtime_s(&tms, &t))
            break;
        tmi = &tms;
#       else
        tmi = localtime(&t);
#       endif

        wcsftime(buffer, 180, L"%Y-%m-%d %H:%M:%S", tmi);
        printf("\n\t*(%d) wcsftime -> %ls\n", __LINE__, buffer);

        wcsptime(buffer, L"%Y-%m-%d %H:%M:%S", &tms);
        t = mktime(&tms);

#       if defined(_MSC_VER)
        {
            char cbuf[256];
            if (ctime_s(cbuf, sizeof(cbuf), &t))
                break;
            printf("\n\t*(%d) wcsptime -> %s\n", __LINE__, cbuf);
        }
#       else
        printf("\n\t*(%d) wcsptime -> %s\n", __LINE__, ctime(&t));
#       endif

    }
    while (0);

    (void) getchar();
    return 0;
}
