
[![Git HOME](https://img.shields.io/badge/Home-Git-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)
[![Readme RU](https://img.shields.io/badge/Readme-RU-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README.RU.md)
[![Documentation](https://img.shields.io/badge/Documentation-DOC-brightgreen.svg?style=flat)](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html)
[![License MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=flat)](https://github.com/ClnViewer/LibWchar2/blob/master/LICENSE)
[![Build Travis](https://travis-ci.com/ClnViewer/LibWchar2.svg)](https://travis-ci.com/ClnViewer/LibWchar2)
[![Build Appveyor](https://ci.appveyor.com/api/projects/status/5s47u3irthu3icqo?svg=true)](https://ci.appveyor.com/project/ClnViewer/libwchar2)
[![Job Status](https://inspecode.rocro.com/badges/github.com/ClnViewer/LibWchar2/status?token=EjhrEOus5kCYzf9OVjBAPrjGFe23VmAQertYJc6gSDM)](https://inspecode.rocro.com/jobs/github.com/ClnViewer/LibWchar2/latest?completed=true)


[![Repo size](https://img.shields.io/github/repo-size/ClnViewer/LibWchar2.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)
[![Code size](https://img.shields.io/github/languages/code-size/ClnViewer/LibWchar2.svg?style=flat)](https://github.com/ClnViewer/LibWchar2)


# LibWchar2
----------

A wrapper library for compatibility with projects written for the `Windows API`, where `wchar_t` size == 2 bytes on *nix platforms.
Replaces `libc`, `glibc` functions using the `wchar_t` type.

### What is this for:
----------

When porting software using the internal type `wchar_t` from the `Windows API` platform, a `wchar_t` size equal to two bytes (16 bit) is required for normal operation. In *nix systems, by default the `wchar_t` type size corresponds to 4 bytes (32 bit).

But, it is possible to compile a program with the type `wchar_t` equal to 2 bytes. This feature is available when using `GCC` or `clang` compilers.
To ensure the efficiency of these collected programs, it is necessary that libc and as a consequence all other libraries be assembled with `wchar_t` support equal to 2 bytes. This condition is usually impracticable..

### Compiler keys:

Using compilation keys to build your program with this library.
Enable assembly with `wchar_t` type equal to 2 bytes.

CC  | key
--- | --- |
`GCC` | `-fshort-wchar`
`clang` | `-fwchar-type=short` `-fno-signed-wchar`

### Features of the library:

- The library has no dependencies.
- It was tested under `Linux`, on other *nix platforms the behavior is not guaranteed.
- It is not intended for assembly in the `Windows API` environment, because it is not needed on this platform.
- The library includes both the main functions from the `libc`, `glibc` libraries, for working with the `wchar_t` type, and third-party developments and other extensions.
- An additional [library of extensions](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README-WINAPIEXT.md) based on `LibWchar2` for `Windows API` platforms is available.
- There are [files](https://github.com/ClnViewer/LibWchar2/blob/master/docs/cppcheck/libwchar2.cfg) for the [`cppcheck`](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README-CPPCHECK.md) code analyzer settings for testing programs using this library.
- **Attention**, not all [functions](https://github.com/ClnViewer/LibWchar2/blob/master/docs/WCHAR2-LIST-MAP.md) are properly tested, if you help with tests and search for inconsistencies, this will make the library better and more reliable.
 
### Standart ISO/IEC 9899:2011 + stddef.h

A short free translation of the essence of what is stated in the standards concerning `wchar_t` and related types.

1. `wchar_t` which is an integer type whose range of values can be different codes for all members of the largest extended character set specified among the supported local encodings. A null character must have a zero code value. Each member of the base character set must have a code value equal to its value when used as a single character in an integer symbolic constant if the implementation does not specify `STDC_MB_MIGHT_NEQ_WC`.
2. `wint_t` - which is an integer type that is unchanged by default, since it can contain any value that corresponds to members of the extended character set, as well as at least one value that does not correspond to any extended character set.
3. `mbstate_t` - which is the complete type of the object, other than the type of the array, which can contain the conversion state information needed to convert between the sequences of many byte characters and wide characters.


### Explanations of the developers of the implementation of the functional `wchar_t`

- I use the compiler flags to provide the size of 2 bytes for the `wchar_t` type, you are doing this on your own responsibility. Using this, you lose the ability to work efficiently with external libraries assembled without these flags. Standard libraries are assembled by default with `wchar_t` support of 32 bits for * nix systems.
- The situations in which `wchar_t` is 2 bytes in size are very limited and probably relate mainly to standalone implementations along with changing the code of all libraries using wide characters.
- Some *nix systems define `wchar_t` as a 16-bit type and thus strictly follow `Unicode`. This definition perfectly corresponds to the standard, but it also means that to represent all characters from `Unicode` and `ISO 10646` it is necessary to use the surrogate characters `UTF-16`, which in fact is an encoding with several wide-format symbols. But, the reference to a wide character encoding is contrary to the purpose of this `wchar_t` type.
- It is not recommended to mix `input/output` functions of wide character and byte array. The functions `printf/fprintf/putchar` are the output of bytes, regardless of whether it includes formats for wide characters in the same thread. The functions `wprintf/vfwprintf/putwchar` on the contrary, are intended for the output of wide characters, although it is also able to print byte arrays.
- Another problem with `glibc`, `libc` is the difference between the types of variables `wchar_t` and `wint_t`, `unsigned` and `signed`, respectively. Some of the functions `glibc`,` libc` associated with wide characters take as input parameters the type `wint_t` which is a certain problem associated with the compiler warnings about the different types of signatures of the variable.  
- An interesting historical note [wchar_t: Unsafe at any size](http://losingfight.com/blog/2006/07/28/wchar_t-unsafe-at-any-size/) from [Andy Finnell](http://losingfight.com/blog/contact/)  


### Ideological changes:


> Library **LibWchar2** removes these restrictions, and does not require reassembly of all libraries, while allowing you to create applications with two byte type `wchar_t`.
        
> In the library **LibWchar2** the variable with the type `mbstate_t` is ignored, and even if you do not set this variable, it removes the intermediate states that are stored and prevent the mutual execution of ` input/output` in one thread.
>
> Also, work with the orientation of the stream is deleted in the `input/output` functions, its necessity is a very controversial issue, but this also affects the stability of the functions associated with the `input/output` operations.
        
> In the library **LibWchar2** the problem of types is solved, all functions that work in one way or another with wide characters are reduced to a single type `wchar_t`.

### Assembly and Installation:

Assembling a *nix platform is performed in a typical way, using the [autotool](https://ru.wikipedia.org/wiki/Autotools "Autotools") package.

Run the `configure` installation script from the project's root directory.
In addition to typical keys, the script understands the following options:

* `--enable-werror`  - collect the library and tests with the `-Werror` key.
* `--enable-devel`    - collect the library and tests with the `-Wextra` key.
* `--disable-testlib` - do not collect library tests.
* `--enable-debug`    - collect a library with debugging information.

 Next, you need to compile the library with the standard commands:

    ./configure --prefix=/usr
    make
    make check
    make install

Also, you can use the script `build.sh` from the root directory, this will allow you not to enter these commands with your hands.

If there is a need to rebuild the script `./configure`, execute:

    ./autogen.sh

### Library extensions for Windows API

- Installing [extension `LibWchar2` Library](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README-WINAPIEXT.md) for `Windows API`.


### API

- Header file: [wchar2.h](https://github.com/ClnViewer/LibWchar2/blob/master/include/wchar2.h)  
- OnLine docs: [libwchar2](https://clnviewer.github.io/LibWchar2/docs/html/wchar2.html)  
- Function list: [map](https://github.com/ClnViewer/LibWchar2/blob/master/docs/WCHAR2-LIST-MAP.md), [man](https://github.com/ClnViewer/LibWchar2/blob/master/docs/wchar2.3)
- Actual changes: [ChangeLog](https://github.com/ClnViewer/LibWchar2/blob/master/docs/CHANGELOG-master.md)


To use the library in the project, connect the header last, after all system headers, while `wchar.h` and `wctype.h` can be omitted, they are already included.

    #include <stdio.h>
    #include <string.h>
    #include ...
    #include <wchar2.h>

The library itself is connected in the standard way:

`Makefile:`

    CFLAGS = -I. -fshort-wchar /* GCC */
    CFLAGS = -I. -fwchar-type=short -fno-signed-wchar /* clang */
    LDFLAGS = -L. -lwchar2

Definitely convenient is the redefinition of standard functions working with the file system, such as: `mkdir`, `remove`, `rename`, `stat`, `access`, `basename`, `dirname`, `fopen`, `fputc`, `fputs`.

For this, before including the header, define the following definitions:

    #define WS_FS_REDEFINE 1
    #include <wchar2.h>

or, if there is a need to use only `UTF-8` encoding:

    #define WS_FS_REDEFINE 1
    #define WS_FS_UTF8 1
    #include <wchar2.h>

**Attention**, the `WS_FS_UTF8` key will not work separately.

Example [code snippets](https://github.com/ClnViewer/LibWchar2/blob/master/example/fs-redifine.c)

In the `WS_FS_UTF8` definition mode, functions` mkdir`, `remove`, `rename`, `stat`, `fopen`, `access` only accept input data in `wchar_t` format, otherwise the input data can be in the formats shown in the table, in this case the determination is made automatically.

See: [wchar2.h](https://github.com/ClnViewer/LibWchar2/blob/f884fcf232e483759b827a53cc2333332d2cda27/include/wchar2.h#L342) macro `__wchar_type_id(..)`

Type | const | array | const array
--- | --- | --- | --- |
char* | const char* | char[] | const char[]
wchar_t* | const wchar_t* | wchar_t[] | const wchar_t[]
string_ws* | const string_ws* ||


### Test & Testing

- By checking your code with analysis programs, you make it more reliable, if you use [cppcheck](https://en.wikipedia.org/wiki/Cppcheck) you may be useful [configuration files](https://github.com/ClnViewer/LibWchar2/blob/master/docs/README-CPPCHECK.md) with a description of library functions for the  `cppcheck` analysis.
- If you have the time and the desire or the opportunity to help make the library better, you can take part in writing tests for library functions.
This way you will take part in the testing.

### Projects adapted to the library

- [libexpat](https://github.com/libexpat/libexpat) - Fast streaming XML parser written in `C`. Author: [Expat development team](https://libexpat.github.io/)  
- [tinydir](https://github.com/ClnViewer/tinydir/tree/libwchar2support) - [patch v.1.2.3](https://github.com/ClnViewer/tinydir/blob/master/tinydir-release-1.2.3.diff) - Lightweight, portable and easy to integrate C directory and file reader. Author: [cxong](https://github.com/cxong) 

### Source & Materials used:

The project uses the revised code of the authors:

- [Tim J. Robbins](https://packetstormsecurity.com/files/author/1683/)
- [Nexenta Systems, Inc](https://en.wikipedia.org/wiki/Nexenta_Systems)
- [Fredrik Fornwall/Rich Felker](https://github.com/fornwall)
- [Angel Ortega](http://triptico.com/)
- [Mayu Laierlence](https://github.com/minacle)
- [Nodir Temirkhodjaev](https://github.com/tnodir)

for which they have a special thank you :)

## License

_MIT_

