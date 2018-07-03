
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <locale.h>
#include <errno.h>

#include "../include/wchar2.h"
#include "check_wchar2_utf8.h"

int dm_string_equals_ascii(const char *c, wchar_t *w, int wsz)
{
    int            cnt  = 0;
    const wchar_t *wchr = w;
    const char    *cchr = c;

    while(*cchr)
    {
        if (cnt == wsz) { return 0; }
        if (wchr[cnt++] != *cchr++) { return 1; }
    }
    return 0;
}

void printf_w(wchar_t *pp)
{
    wchar_t *p = pp;
    while(*p)
    {
        putchar(*p++);
    }
}

int strlen_w(wchar_t *pp)
{
    int sz = 0;
    wchar_t *p = pp;
    while(*p)
    {
        sz++; p++;
    }
    return sz;
}

size_t __wcslen(const wchar_t *s) {
    size_t n = 0;
    for (;;) {
        wchar_t wc = s[n];
        if (wc == L'\0')
            return n;
        n++;
    }
}

int main(int argc, char *argv[])
{

    char    *c  = "Hello word!";
    wchar_t *w0 = L"Hello word!";
    wchar_t *w1 = L"Hello word!";
    wchar_t *t  = L"/this/path/to/file.zip";

    printf("\t(%d) strerror: [%s]\n", __LINE__, strerror(errno)); errno = 0;

    printf( "\t[%s] [%ls]\n", c, w0);
    printf( "\t[%d/%d/%d]\n",
        wcsncmp(w0, w1, 11),
        strncmp((char*)w0, c, strlen(c)),
        dm_string_equals_ascii(c, w0, _wcslen(w0))
    );
    printf("\t(%d) strerror: [%s]\n", __LINE__, strerror(errno)); errno = 0;

    printf( "\t[");
    printf_w(t);
    printf( "]\n\t -> [%d/%u]\n", strlen_w(t), _wcslen(t));
    printf("\t(%d) strerror: [%s]\n", __LINE__, strerror(errno)); errno = 0;

    int sz2, sz1 = (int)_wcslen(wcs1);
    printf("\t(%d) strerror: [%s]\n", __LINE__, strerror(errno)); errno = 0;

//    char b0[((sz1 + 1) * 2)];
//    sz2 = _wcstombs(b0, wcs1, ((sz1 + 1) * 4)); b0[sz2] = '\0';
//    printf( "\t[%s] [%d/%d]\n", b0, sz1, sz2);

    sz1 = strlen(c);
    sz2 = (int)_wcslen(wcs1);
    printf("\t(%d) strerror: [%s]\n", __LINE__, strerror(errno)); errno = 0;

    printf( "\t[%d/%d]\n", sz1, sz2);
    //wchar_t b1[(sz1 + 1)];
    //sz2 = _mbstowcs(b1, c, (sz1 + 1));
    //fprintf(stdout, "\t fprintf \t [%ls] [%d/%d]\n", b1, sz1, sz2);
    fprintf(stdout, "\t fprintf \t [%ls]\n", wcs1);
    fwprintf(stdout, L"\t fwprintf \t [%S] [%s] [%d/%d]\n", wcs1, c, sz1, sz2);
    printf("\t(%d) strerror: [%s]\n", __LINE__, strerror(errno)); errno = 0;

    wchar_t *wfile = L"./test-\x20AC-\x20AC.txt";
    char    *cfile = malloc(wcstou8s(NULL, wfile) + 1);
    int ret = wcstou8s(cfile, wfile),
        len = strlen(cfile);

    printf("[%s] [%d/%d]\n", cfile, len, ret);

    FILE *fp = fopen(cfile,"w");
    if (fp == NULL) { printf( "\tfp is null! [%s]\n", strerror(errno)); } else {
        fprintf(fp, "\t (fopen)(initial) fprintf \t [%ls]\n", wcs1);
        fclose(fp);
    }
    free(cfile);

    fp = wfopen(wfile,"w");
    if (fp == NULL) { printf( "\tfp is null! [%s]\n", strerror(errno)); } else {
        fprintf(fp, "\t (wfopen)(overwrite) fprintf \t [%ls]\n", wcs1);
        fclose(fp);
    }

    //char dest[256] = {0};
    //sz1 = (int)_wcslen(wcs1);
    //sz2 = _wcsrtombs(dest, &(const wchar_t *){wcs1}, (sz1 * 2 + 1), 0);
    //sz2 = _wcrtomb(dest, (const wchar_t)wcs1[0], 0);
    //printf( "\t[%d/%d] [%s]\n", sz1, sz2, dest);

    return 0;
}
