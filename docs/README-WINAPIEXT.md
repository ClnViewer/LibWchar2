[![Git HOME](https://img.shields.io/badge/Home-Git-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)
[![Web HOME](https://img.shields.io/badge/Home-Web-brightgreen.svg?style=flat)](https://clnviewer.github.io/LibWchar2)
[![Documentation](https://img.shields.io/badge/Documentation-DOC-brightgreen.svg?style=flat)](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html)
[![License MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2/blob/master/LICENSE)
[![Build Travis](https://travis-ci.com/ClnViewer/LibWchar2.svg)](https://travis-ci.com/ClnViewer/LibWchar2)
[![Build Appveyor](https://ci.appveyor.com/api/projects/status/5s47u3irthu3icqo?svg=true)](https://ci.appveyor.com/project/ClnViewer/libwchar2)

# LibWchar2 - for Windows API
----------

The extension includes a set of library functions not included in the standard `Windows API`.

For backwards compatibility with the `*nix` version of the library, non-standard functions are placed in a separate assembly, which allows to use these functions in applications collected on the `Windows` platform.

### List of features of the extension library

- With the list of functions included in the library extensions `LibWchar2` can be found in the header file [`wchar2ext.h`](https://github.com/ClnViewer/LibWchar2/blob/master/include/wchar2ext.h).  
- More details are described in the [documentation](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html).  
- The current results of the test builds of the extension library `LibWchar2` on [appveyor.com](https://ci.appveyor.com/project/ClnViewer/libwchar2).

### Installing LibWchar2 extension library

The libwchar2 extension library build is designed for the `MSVC`/`MSVS` or `MinGW`, `MSYS` compilation environment. Preparation for the assembly is done using the  `cmake` script.

The sequence of steps for building an extension library if your version of `Visual Studio` or `Visual C++` is using the external utility `cmake`:

#### Executing the `cmake` script for the command line

- go to the `winext/build` directory in the repository.
- execute the command `cmake` with the -G key, where the key parameter is the [version](https://cmake.org/cmake/help/v3.4/manual/cmake-generators.7.html#visual-studio-generators) of `Visual Studio` or `Visual C ++`, or predefined build-name string to `MinGW`, `MSYS`:

        cd winext/build

        // to Visual Studio project
        cmake -G"Visual Studio 14"  .. 
        // or MinGW
        cmake -G "MinGW Makefiles"  ..
        // or MinGW CodeBlocks
        cmake -G "CodeBlocks - MinGW Makefiles"  ..

        cmake --build . --target "ALL_BUILD" --config "Release"

- Library output files after successful assembly and installation should be in the directory `winext/lib`.

You can also select `winext/build/libwchar2ext.sln` in `Visual Studio`, or to `CodeBlocks` `winext/build/libwchar2ext.cbp`, and compile it in the standard way.


#### Executing the `cmake` script for `CMake GUI`

- run `CMake GUI`
- specify the ways:
 - `Where is the source code` - the full path to the `winext` folder in the repository.
 - `Where to build the binaries` - the full path to the `winext / build` folder in the repository, the project files will be generated there.
- press the `Configure` button and select the version of `Visual Studio` or `MinGW Makefiles`, in case of error, click again :)
- Press the button `Generate`.
- we press the button `Open Project`, it is supported from the version ` CMake GUI` `> =` `3.12`.
- in `Visual Studio`, choose the type of assembly `Release` or `Debug`.
- Press `F7`, we compile the project.
- library output files after successful assembly and installation should be in the directory `winext/lib`

> In case of errors when creating `CMake` configuration files for `MinGW Makefiles` or `CodeBlocks - MinGW Makefiles` - rename the directory:
`<path>\MinGW\mingw32` for example in `<path>\MinGW\mingw32old`.
>
>In the case of `CodeBlocks`, `MinGW` is inside, with `<path>\CodeBlocks\MinGW\mingw32` fully installed.

### Additional assembly keys

- `OS_WIN_EXCEPTION_CONSOLE` - collect with support for displaying fatal exceptions in the console.
- `OS_WIN_FOPEN_MIXED_CHAR` - collect the `wfopen` function with a mixed data type:

        wfopen(const wchar_t*, const char*);
instead of the default declaration:

        wfopen(const wchar_t*, const wchar_t*);

How to add compiler keys:

        cmake -G "..."  .. -DOS_WIN_EXCEPTION_CONSOLE -DOS_WIN_FOPEN_MIXED_CHAR


### LibWchar2 extension library tests

With the library of extensions `LibWchar2` attached a small program to test the functions included in the library.

In the `Visual Studio` project, it is added automatically, if you want to test the result after the build from the command line, execute the following script:

    cd winext/build
    ctest --verbose -C "Debug"

The source code of the test can be found in the file [`test/check_wchar2_MSVC.c`](https://github.com/ClnViewer/LibWchar2/blob/master/test/check_wchar2_MSVC.c).

### Example use

    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <wchar.h>
    /*
      pragma include lib char2ext.lib already in wchar2ext.h,
      not needed other method link this lib.
    */
    #include "wchar2ext.h"

     int main(int argc, char *argv[])
     {
        int ret;
        string_ws dst = { NULL, 0U };

        ret = wstring_append(&dst, __WS("my one"), 0);
        printf("\n\t*(%d) wstring_appends: [%ls][%u]\n", __LINE__,
          dst.str, dst.sz
        );

        ret = wstring_append(&dst, __WS(", next string"), 0);
        printf("\n\t*(%d) wstring_appends: [%ls][%u]\n", __LINE__,
          dst.str, dst.sz
        );

        wstring_free(&dst);

        (void) getchar();
        return 0;
      }


## License

_MIT_

