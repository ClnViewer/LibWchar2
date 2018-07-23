#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <wchar.h>

// devel include mode
// #include "../libwcha2-extension/src/libbuild.h"
// #include "../libwcha2-extension/src/libwcharext.h"

#include "../include/wchar2ext.h"

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
// #pragma comment(lib, "libwchar2ext.lib")

#define F_OK 0

static const char * __access_error(access_e x)
{
    return (const char *)((x == ISERROR) ? "Error check" :
                          ((x == ISFIL) ? "is a Regular file" :
                           ((x == ISLNK) ? "is a Symbolic link" :
                            ((x == ISDIR) ? "is a Directory" : "Unknown result"))));
}

static const char * __get_error(char **errstr, int err)
{
#   if defined(_MSC_VER)
    (void) strerror_s(*errstr, 256, err);
    return (const char*)*errstr;
#   else
    *errstr = strerror(err);
    return (const char*)(*errstr);
#   endif
}


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
    const char wtext[] = "write text UTF8 - тест текст";
#   if defined(_MSC_VER)
    char bstr[256] = {0}, *errstr = (char*)&bstr;
#   else
    char *errstr = NULL;
#   endif

    printf("\n\ti sizeof wchar_t [%u]\n", sizeof(wchar_t));

    sz = wstring_appends_(&dst, (wchar_t*)a.str, (wchar_t*)aaa.str, (wchar_t*)aa.str, NULL);
    printf("\n\t*(%d) wstring_appends: [%ls][%u]\n", __LINE__, dst.str, dst.sz);
    wstring_free(&dst);

    sz = wstring_append(&dst, (wchar_t*)aa.str, 0);
    printf("\n\t*(%d) wstring_append: [%ls][%u]\n", __LINE__, dst.str, dst.sz);
    wstring_free(&dst);

    sz = wstring_format(&dst, L"%ls%ls%ls", a.str, aaa.str, aa.str);
    printf("\n\t*(%d) wstring_format: [%ls][%u]\n", __LINE__, dst.str, dst.sz);

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
    printf("\n\t*(%d) wmkdir: [create] [%ls] -> [%d/%d][%s]\n", __LINE__, pathmkd, ret, errno, __get_error((char**)&errstr, errno));

    ret = waccess(pathmkd, F_OK);
    printf("\n\t*(%d) waccess: [%ls] -> [%d][%s]\n", __LINE__, pathmkd, ret, __access_error(ret));

    ret = wmkdir(pathmkd, 0);
    printf("\n\t*(%d) wmkdir: [exist]  [%ls] -> [%d/%d][%s]\n", __LINE__, pathmkd, ret, errno, __get_error((char**)&errstr, errno));

    {
        FILE *fp;
        errno = 0;
        if (!(fp = wfopen(__WS("test-write.txt"), "a+")))
        {
            printf("\n\t*(%d) wfopen: [error] -> [%d][%s]\n", __LINE__, errno, __get_error((char**)&errstr, errno));
            return 0;
        }
        printf("\n\t*(%d) wfopen: [ok] -> [%d][%s]\n", __LINE__, errno, __get_error((char**)&errstr, errno));
        errno = 0;
        ret = fwrite((void*)wtext, sizeof(char), sizeof(wtext), fp);
        printf("\n\t*(%d) fwrite: [status]  -> [%d/%d][%s]\n", __LINE__, ret, errno, __get_error((char**)&errstr, errno));
        fclose(fp);
    }

    (void) getchar();
    return 0;
}
