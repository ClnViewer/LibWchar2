
/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */

    /* This MSVC/MSVS libwchar2 extension test, Windows API compatible */

#include <stdio.h>
// #include <conio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <wchar.h>

// devel include mode
// #include "../src/libbuild.h"
// #include "../src/libwcharext.h"

#include "../include/wchar2ext.h"

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )

    /*
       Not needed, pragma lib include in wchar2ext.h
       #pragma comment(lib, "libwchar2ext.lib")
     */

#define F_OK 0

static const char * __access_error(access_e x)
{
    return (const char *)((x == ISERROR) ? "Error check" :
            ((x == ISFIL) ? "is a Regular file" :
             ((x == ISLNK) ? "is a Symbolic link" :
              ((x == ISDIR) ? "is a Directory" : "Unknown result"))));
}

int main(int argc, char *argv[])
{
	wchar_t *outw, pathw[] = L"\\this\\path\\to\\file.zip";
	wchar_t pathmkd[] = L"this\\path\\to\\file";
	string_ws dst = { NULL, 0U },
		a   = { L"_one_string_", 0U},
		aa  = { L"_two_string_", 0U },
		aaa  = { L".", 0U };
	char errstr[256] = {0};
	size_t sz;
	int ret;

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
	if (outw) { free(outw); }

	outw = wbasedir(pathw, 1);
	printf("\n\t*(%d) wbasedir: [%ls]\n", __LINE__, outw);
	if (outw) { free(outw); }

	ret = waccess(pathmkd, F_OK);
	printf("\n\t*(%d) waccess: [%ls] -> [%d][%s]\n", __LINE__, pathmkd, ret, __access_error(ret));

	ret = wmkdir(pathmkd, 0);
	(void) strerror_s(errstr, sizeof(errstr), errno);
	printf("\n\t*(%d) wmkdir: [create] [%ls] -> [%d/%d][%s]\n", __LINE__, pathmkd, ret, errno, errstr);

	ret = waccess(pathmkd, F_OK);
	printf("\n\t*(%d) waccess: [%ls] -> [%d][%s]\n", __LINE__, pathmkd, ret, __access_error(ret));

	ret = wmkdir(pathmkd, 0);
	(void) strerror_s(errstr, sizeof(errstr), errno);
	printf("\n\t*(%d) wmkdir: [exist]  [%ls] -> [%d/%d][%s]\n", __LINE__, pathmkd, ret, errno, errstr);
	

  (void) getchar();
  return 0;
}
