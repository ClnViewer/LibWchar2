#if defined(__CROSS_COMPILE_TIME__)
#   define __USE_MINGW_ANSI_STDIO 1
#endif

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <locale.h>
#if defined(_MSC_VER)
#   include <io.h>
#   define __close _close
#else
#   define __close close
#endif
#include <fcntl.h>
#include <wchar.h>
#include <windows.h>

#if !defined(WCHAR2EXT_MSVC_ORIGIN)
#   undef WCHAR2EXT_MSVC_ORIGIN
#endif

#include "../include/wchar2ext.h"

#if defined(_MSC_VER)
#   pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
// #pragma comment(lib, "libwchar2ext.lib")
// #pragma execution_character_set("utf-8")
#endif

#define F_OK 0

#if 0

/* Set "Lucida Console" utf8 support font to console */

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

typedef BOOL (WINAPI *SETCURRENTCONSOLEFONTEX)(HANDLE, BOOL, PCONSOLE_FONT_INFOEX);

static void ExChangeUTFConsoleFont(void)
{
    HMODULE StdOut, hmod;
    SETCURRENTCONSOLEFONTEX SetCurrentConsoleFontEx;
    CONSOLE_FONT_INFOEX font;

    hmod = GetModuleHandle("KERNEL32.DLL");
    SetCurrentConsoleFontEx = (SETCURRENTCONSOLEFONTEX)GetProcAddress(hmod, "SetCurrentConsoleFontEx");
    if (!SetCurrentConsoleFontEx)
    {
        printf("\n\t* SetCurrentConsoleFontEx GetProcAddress error\n");
        return;
    }

    StdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    memset(&font, 0, sizeof(CONSOLE_FONT_INFOEX));
    font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    font.FontFamily   = FF_DONTCARE;
    font.dwFontSize.X = 0;
    font.dwFontSize.Y = 14;
    font.FontWeight   = 400;
    wcscpy(font.FaceName, L"Lucida Console");

    if (SetCurrentConsoleFontEx(StdOut, FALSE, &font))
    {
        printf("\n\t* SetCurrentConsoleFontEx error\n");
    }
}
#else
#   define ExChangeUTFConsoleFont()
#endif

#if 0
//! [Example declaration wreaddir CallBack]
static void __dir_default_cb(unsigned int ino, access_e etype, long long size, string_ws *name, void *data)
{
    (void) data;
    fprintf(stdout, "\t\t- ino [%ld] -> type [%d] size [%lld] -> [%ls][%u]\n",
            ino, etype, size, name->str, name->sz
           );
}
//! [Example declaration wreaddir CallBack]
#endif

//! [Example use waccess errorcode]
static const char * __access_error(access_e x)
{
    return (const char *)((x == ISERR) ? "Error check" :
                          ((x == ISFIL) ? "is a Regular file" :
                           ((x == ISLNK) ? "is a Symbolic link" :
                            ((x == ISDIR) ? "is a Directory" : "Unknown result"))));
}
//! [Example use waccess errorcode]

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
    //! [Example use waccess declare]
    wchar_t pathmkd[] = L"this\\path\\to\\file";
    //! [Example use waccess declare]
    string_ws dst = { NULL, 0U },
              a   = { L"_one_string_", 0U},
              aa  = { L"_two_string_", 0U },
              aaa  = { L".", 0U };
    const char *c = "_one_string_",
                *cc = "_two_string_";
    //! [Example use ws-cs convert]
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

    /* Console variant set to UTF8 */
    /*
        setlocale(LC_ALL, ".OCP");
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        system("chcp 65001 > nul");
    */
#   if (defined(__MINGW32__) || defined(__MINGW64__))
    setlocale(LC_ALL, ".OCP");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#   endif

    ExChangeUTFConsoleFont();

    printf("\n\t* sizeof wchar_t [%zu]\n", sizeof(wchar_t));

#   if (defined(__MINGW32__) || defined(__MINGW64__))
    /*
        Not needed test for MSVC/MVCS, function wcprint() used putwchar() default.
        UTF-8 characters (d080 - d3bf) RU: https://www.utf8-chartable.de/unicode-utf8-table.pl?start=1024
        UTF-8 characters (00 - c3bf)  ENG: https://www.utf8-chartable.de/unicode-utf8-table.pl
    */
    wchar_t wc_prn_hex[] =
    {
        0x041A, 0x041E, 0x0428, 0x041A, 0x0410, 0x20, 0x00A9, 0x00AE, 0x0
    };
    printf("\n\t*(%d) wcprint: ", __LINE__);
    wcprint(L"Test UTF8 console: ");
    wcprint(L"Это просто UTF8 ТЕКСТ - длинный :)");
    printf("\n\t*(%d) wcprint HEX: ", __LINE__);
    wcprint(wc_prn_hex);
#   endif

    /* low-level Function test */

    wmemset((void*)&wout, 0, wsizeof(wout));
    memset((void*)&cout, 0,  sizeof(cout));

    ret = wcstocscmp(c, a.str, wcslen(a.str));
    printf("\n\n\t*(%d) wcstocscmp: [%ls][%d]\n", __LINE__, a.str, ret);

    ret = wcstocscmp(cc, aa.str, wcslen(aa.str));
    printf("\n\t*(%d) wcstocscmp: [%ls][%d]\n", __LINE__, aa.str, ret);

    ret = wcstocscmp(c, aa.str, wcslen(aa.str));
    printf("\n\t*(%d) wcstocscmp: [%s] -> [%ls][%d]\n", __LINE__, c, aa.str, ret);

    ret = wstring_cstows(wout, wsizeof(wout), (const char*)wtext, 0);
    printf("\n\t*(%d) wstring_cstows: [%ls][%d]\n", __LINE__, wout, ret);

    ret = wstring_wstocs(cout, sizeof(cout), (const wchar_t*)wout, 0);
    printf("\n\t*(%d) wstring_wstocs: [%s][%d]\n", __LINE__, cout, ret);
    //! [Example use ws-cs convert]

    //! [Example use wstring_appends code]
    // cppcheck-suppress varFuncNullUB
    sz = wstring_appends_(&dst, (wchar_t*)a.str, (wchar_t*)aaa.str, (wchar_t*)aa.str, NULL);
    printf("\n\t*(%d) wstring_appends: [%ls][%zu] -> [%zu]\n", __LINE__, dst.str, dst.sz, sz);
    wstring_free(&dst);
    //! [Example use wstring_appends code]

    //! [Example use wstring_append code]
    sz = wstring_append(&dst, (wchar_t*)aa.str, 0);
    printf("\n\t*(%d) wstring_append: [%ls][%zu] -> [%zu]\n", __LINE__, dst.str, dst.sz, sz);
    wstring_free(&dst);
    //! [Example use wstring_append code]

    //! [Example use wstring_format code]
    sz = wstring_format(&dst, L"%ls%ls%ls", a.str, aaa.str, aa.str);
    printf("\n\t*(%d) wstring_format: [%ls][%zu] -> [%zu]\n", __LINE__, dst.str, dst.sz, sz);
    //! [Example use wstring_format code]

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

    //! [Example use waccess code]
    ret = waccess(pathmkd, F_OK);
    printf("\n\t*(%d) waccess: [%ls] -> [%d][%s]\n", __LINE__, pathmkd, ret, __access_error(ret));
    //! [Example use waccess code]

    ret = wmkdir(pathmkd);
    printf("\n\t*(%d) wmkdir: [create] [%ls] -> [%d/%d][%s]\n", __LINE__, pathmkd, ret, errno, __get_error(errstr, errno));

    ret = waccess(pathmkd, F_OK);
    printf("\n\t*(%d) waccess: [%ls] -> [%d][%s]\n", __LINE__, pathmkd, ret, __access_error(ret));

    ret = wmkdir(pathmkd);
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
        //! [Example use wcsftime]
        time_t t;
        struct tm *tmi, tms = {0};
        wchar_t buffer [180] = {0};

        t = time(NULL);

#       if defined(_MSC_VER)
        if (localtime_s(&tms, &t))
            break;

        tmi = &tms;
#       else
        // cppcheck-suppress redundantAssignment
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
        //! [Example use wcsftime]
    }
    while (0);

    do
    {
        //! [Example use wstring_timeformat]
        wchar_t *tout = NULL, tstr[] = L"2018-07-24T19:03:18Z";

        if ((tout = wstring_timeformat(tstr, 0, L"%Y-%m-%dT%H:%M:%S%Ez", L"%I:%M%p")) == NULL)
            break;

        printf("\n\t*(%d) wstring_timeformat -> [%ls] -> [%ls]\n", __LINE__, tstr, tout);
        free(tout);
        //! [Example use wstring_timeformat]
        tout = NULL;
    }
    while (0);

    do
    {
        //! [Example use wreaddir_cb]
        int ret;
        long opt = 0L;
#       if defined(_MSC_VER)
        wchar_t path[] = L"..\\*";
#       else
        wchar_t path[] = L"../";
#       endif

        opt = wreaddir_cb_opt(opt, DIRNOROOT);
        printf("\n\tTest _wreaddir_cb:%d\t\t->\n", __LINE__);
        ret = _wreaddir_cb(path, opt, NULL, NULL);
        printf("\n\t*(%d) _wreaddir_cb end -> return:[%d] error:[%d] path:[%ls] -> opt: DIRNOROOT\n", __LINE__, ret, errno, path);
        //! [Example use wreaddir_cb]
    }
    while (0);

    do
    {
        //! [Example use wmkstemp]
        wchar_t mkstemplate[] = L"my-tmpfileXXXXXX";
        ret = wmkstemp(mkstemplate);
        printf("\n\t*(%d) wmkstemp -> [%ls] open fd -> [%d]\n", __LINE__, mkstemplate, ret);
        if (ret > 0)
        {
            __close(ret);
            wremove(mkstemplate);
        }
        //! [Example use wmkstemp]
    }
    while (0);

    (void) getchar();
    return 0;
}
