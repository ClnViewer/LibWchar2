
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#if ( \
        defined(_WIN32) || defined(__WIN32__) || defined(_Windows) || \
        defined(_WIN64) || defined(__WIN64__) || \
        defined(__CYGWIN__) || defined(__MINGW32__) || defined(__MINGW64__))

#   if defined(WCHAR2EXT_MSVC_ORIGIN)
#      undef WCHAR2EXT_MSVC_ORIGIN
#   endif
#   include <wchar2ext.h>

#else

#   define WS_FS_REDEFINE 1
#   include <wchar2.h>

#endif

#if defined(_MSC_VER)
#   pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
#endif

static const char * __access_type(access_e x)
{
    return (const char *)((x == ISERR) ? "Type error" :
                          ((x == ISFIL) ? "Regular file" :
                           ((x == ISLNK) ? "Symbolic link" :
                            ((x == ISDIR) ? "Directory" : "unknown type"))));
}

static void __dir_file_count_cb(unsigned int ino, access_e etype, long long size, string_ws *name, void *data)
{
    (void) etype;
    (void) size;
    (void) name;

    *((unsigned int*)data) = ino;
}
static void __dir_dir_count_cb(unsigned int ino, access_e etype, long long size, string_ws *name, void *data)
{
    (void) ino;
    (void) size;
    (void) name;

    if (etype == ISDIR)
    {
        unsigned int *dcnt = (unsigned int*)data;
        *dcnt += 1;
    }
}
static void __dir_print_cb(unsigned int ino, access_e etype, long long size, string_ws *name, void *data)
{
    (void) data;
    fprintf(stdout, " - ino [%u] -> type [%d/%s] size [%lld] -> [%ls][%zu]\n",
            ino, etype, __access_type(etype), size, name->str, name->sz
           );
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
    int ret = 0, isalive = 1;
    long  opt;
    char c = 0;
    char *optstr = NULL;
#   if defined(_MSC_VER)
    char  errstr[256] = {0};
    wchar_t path[] = L"..\\*";
#   else
    char *errstr = NULL;
    wchar_t path[] = L"../";
#   endif

    (void) argc;
    (void) argv;

    while (isalive)
    {
        if (c != 0xa)
        {
            fprintf(stdout, "\n\t- [0] print directory not filtered\n" \
                    "\t- [1] print directory is a filtered: DIRNOROOT\n" \
                    "\t- [2] print directory is a filtered: DIRNOROOT, DIRENTRYSIZE\n" \
                    "\t- [3] print directory is a filtered: DIRNODIR,  DIRENTRYSIZE\n" \
                    "\t- [4] print directory files count\n" \
                    "\t- [5] print directory directory's count\n" \
                    "\t- [q] exit\n" \
                    "\t* [%c] select\n\n", c
                   );
        }
        switch((c = getchar()))
        {
        case 'X':
        case 'Q':
        case 'q':
        case 'x':
        {
            isalive = 0;
            continue;
        }
        case '0':
        {
            optstr = (char*)&"NONE";
            ret = _wreaddir_cb(path, 0L, __dir_print_cb, NULL);
            break;
        }
        case '1':
        {
            optstr = (char*)&"DIRNOROOT";
            opt = wreaddir_cb_opt(0L, DIRNOROOT);
            ret = _wreaddir_cb(path, opt, __dir_print_cb, NULL);
            break;
        }
        case '2':
        {
            optstr = (char*)&"DIRNOROOT, DIRENTRYSIZE";
            opt = wreaddir_cb_opt(
                      wreaddir_cb_opt(0L, DIRENTRYSIZE),
                      DIRNOROOT);
            ret = _wreaddir_cb(path, opt, __dir_print_cb, NULL);
            break;
        }
        case '3':
        {
            optstr = (char*)&"DIRNODIR, DIRENTRYSIZE";
            opt = wreaddir_cb_opt(
                      wreaddir_cb_opt(0L, DIRENTRYSIZE),
                      DIRNODIR);
            ret = _wreaddir_cb(path, opt, __dir_print_cb, NULL);
            break;
        }
        case '4':
        {
            unsigned int numfiles = 0;
            optstr = (char*)&"DIRNODIR";
            opt = wreaddir_cb_opt(0L, DIRNODIR);
            ret = _wreaddir_cb(path, opt, __dir_file_count_cb, (void*)&numfiles);
            printf("\n+ files count from directory [%ls]: -> [%u]\n", path, numfiles);
            break;
        }
        case '5':
        {
            unsigned int numfiles = 0;
            optstr = (char*)&"DIRNOROOT";
            opt = wreaddir_cb_opt(0L, DIRNOROOT);
            ret = _wreaddir_cb(path, opt, __dir_dir_count_cb, (void*)&numfiles);
            printf("\n+ directory's count from directory [%ls]: -> [%u]\n", path, numfiles);
            break;
        }
        default:
        {
            optstr = NULL;
            continue;
        }
        }
        printf("\n* wreaddir_cb end -> return:[%d] error:[%d/%s] path:[%ls] opt:[%s]\n",
               ret, errno,
               ((!errno) ? "" : __get_error(errstr, errno)),
               path,  optstr
              );
    }

    return 0;
}
