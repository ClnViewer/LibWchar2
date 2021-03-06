/*
    MIT License

    Copyright (c) 2018 PS
    GitHub: https://github.com/ClnViewer/LibWchar2

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sub license, and/or sell
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

#include "libbuild.h"

#if (defined(OS_WIN) && defined(_MSC_VER))

// #      pragma warning(disable : 4206) // About empty code file
#   pragma comment(user, "libwchar2ext compiled on " __DATE__ " at " __TIME__)
#   include <stdio.h>
#   include <windows.h>
#   include <excpt.h>

static void __error_console(const char *str, unsigned int code, const char *file, unsigned int line, const char *func)
{
#   if defined(OS_WIN_EXCEPTION_CONSOLE)

    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
        fprintf(stderr,
                "\n! Exception: code: [%u]:\n\t-> source: [%s:%u]\n\t-> function: [%s]\n\t-> status: [%s]\n\n",
                code, file, line, func, str
               );
    }

#   else
    (void) str;
    (void) code;
    (void) file;
    (void) line;
    (void) func;
#   endif
}

int __seh_except_(unsigned int code, unsigned int line, const char *file, const char *func)
{
    const char *err = NULL;
    int ret;

    switch (code)
    {
    case EXCEPTION_ACCESS_VIOLATION:
    {
        err = "Read/Write access violation, abort";
        ret = EXCEPTION_EXECUTE_HANDLER;
        break;
    }

    case EXCEPTION_STACK_OVERFLOW:
    {
        err = "Stack overflow, abort";
        ret = EXCEPTION_EXECUTE_HANDLER;
        break;
    }

    case EXCEPTION_INT_OVERFLOW:
    {
        err = "Int overflow, abort";
        ret = EXCEPTION_EXECUTE_HANDLER;
        break;
    }

    case EXCEPTION_INT_DIVIDE_BY_ZERO:
    {
        err = "Int zero divide, abort";
        ret = EXCEPTION_EXECUTE_HANDLER;
        break;
    }

    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
    {
        err = "Array out of bounds, abort";
        ret = EXCEPTION_EXECUTE_HANDLER;
        break;
    }

    /*
    case EXCEPTION_xxx:
    {
        ret = EXCEPTION_CONTINUE_EXECUTION; break;
    }
    */
    default:
    {
        err = "Other exceptions, function ending";
        ret = EXCEPTION_CONTINUE_SEARCH;
        break;
    }
    }
    __error_console(err, code, file, line, func);
    return ret;
}

const char * wchar2version(void)
{
    static char libinfo[] = "libwchar2ext compiled on " __DATE__ " at " __TIME__;
    return (const char*)libinfo;
}

#else

char libinfo[]
#   if (defined(__APPLE__) || defined(__OSX__) || defined(__MACH__))
__attribute__((section("__SEGMENT,__LIBINFO")))
#   else
__attribute__ ((section ("LIBINFO")))
#   endif
    = "libwchar2ext compiled on " __DATE__ " at " __TIME__;

const char * wchar2version(void)
{
    return (const char*)libinfo;
}

#endif

