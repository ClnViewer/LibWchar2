
AC_PREREQ([2.63])
AC_INIT([libwchar2], [0.0.9], [])
AC_CONFIG_SRCDIR([src/libwchar.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build/m4])
AC_PREFIX_DEFAULT([/usr])
AC_PREFIX_PROGRAM([/usr])

AC_CANONICAL_BUILD
AC_CANONICAL_TARGET
AC_CANONICAL_SYSTEM
AC_USE_SYSTEM_EXTENSIONS

AM_MAINTAINER_MODE([disable])
AM_SANITY_CHECK
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
LT_INIT([static disable-shared])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
m4_ifdef([PKG_PROG_PKG_CONFIG], [PKG_PROG_PKG_CONFIG])
PKG_CHECK_MODULES([CHECK], [check])
m4_pattern_allow(PKG_CONFIG_LIBDIR)

m4_include([build/m4/ax_compiler_vendor.m4])
m4_include([build/m4/ax_check_compile_flag.m4])
m4_include([build/m4/ax_append_flag.m4])

AC_LANG_PUSH([C])
AX_COMPILER_VENDOR
AC_PROG_CC
AC_PROG_CC_C99
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_RANLIB
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AC_CHECK_HEADERS([wchar.h wctype.h], [], [
  AC_MSG_ERROR([unable to find header wchar.h or wctype.h])
])
AC_CHECK_HEADERS([inttypes.h stdint.h stdarg.h string.h errno.h ctype.h check.h libgen.h sys/stat.h limits.h locale.h unistd.h sys/resource.h])

AC_TYPE_MODE_T
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_CHECK_TYPES([ptrdiff_t])
AC_CHECK_SIZEOF(wchar_t, 4)
AC_C_RESTRICT

AS_IF([test "$ac_cv_sizeof_wchar_t" == "2"],[
    AC_MSG_ERROR([size wchar_t is $ac_cv_sizeof_wchar_t - not needed this library.])
])

BUILD_WC2="0"

AX_CHECK_COMPILE_FLAG([-fshort-wchar],[
    AX_APPEND_FLAG([-fshort-wchar])
    BUILD_WC2="1"
])
AX_CHECK_COMPILE_FLAG([-fwchar-type=short],[
    AX_APPEND_FLAG([-fwchar-type=short])
    BUILD_WC2="1"
])
AX_CHECK_COMPILE_FLAG([-fno-signed-wchar],[
    AX_APPEND_FLAG([-fno-signed-wchar])
    BUILD_WC2="1"
])
AS_IF([test "$BUILD_WC2" == "0"],[
  AC_MSG_ERROR([short wchar_t not supported, only gcc or clang compiler capabilities.])
])

AX_CHECK_COMPILE_FLAG([-Wall],[AX_APPEND_FLAG([-Wall])])
AX_CHECK_COMPILE_FLAG([-pedantic],[AX_APPEND_FLAG([-pedantic])])
AX_CHECK_COMPILE_FLAG([-Wstrict-prototypes],[AX_APPEND_FLAG([-Wstrict-prototypes])])
AX_CHECK_COMPILE_FLAG([-Wstrict-aliasing],[AX_APPEND_FLAG([-Wstrict-aliasing])])
AX_CHECK_COMPILE_FLAG([-Wmissing-declarations],[AX_APPEND_FLAG([-Wmissing-declarations])])
AX_CHECK_COMPILE_FLAG([-Wmissing-prototypes],[AX_APPEND_FLAG([-Wmissing-prototypes])])
AX_CHECK_COMPILE_FLAG([-Wconversion],[AX_APPEND_FLAG([-Wconversion])])
AX_CHECK_COMPILE_FLAG([-Wsign-conversion],[AX_APPEND_FLAG([-Wsign-conversion])])
AX_CHECK_COMPILE_FLAG([-Wsign-compare],[AX_APPEND_FLAG([-Wsign-compare])])
AX_CHECK_COMPILE_FLAG([-Winit-self],[AX_APPEND_FLAG([-Winit-self])])
AX_CHECK_COMPILE_FLAG([-Wunreachable-code],[AX_APPEND_FLAG([-Wunreachable-code])])
AX_CHECK_COMPILE_FLAG([-Wformat],[AX_APPEND_FLAG([-Wformat])])
AX_CHECK_COMPILE_FLAG([-Wpointer-arith],[AX_APPEND_FLAG([-Wpointer-arith])])
AX_CHECK_COMPILE_FLAG([-Wreturn-type],[AX_APPEND_FLAG([-Wreturn-type])])
AX_CHECK_COMPILE_FLAG([-Wuninitialized],[AX_APPEND_FLAG([-Wuninitialized])])
AX_CHECK_COMPILE_FLAG([-Wunused-variable],[AX_APPEND_FLAG([-Wunused-variable])])
AX_CHECK_COMPILE_FLAG([-Wno-unknown-pragmas],[AX_APPEND_FLAG([-Wno-unknown-pragmas])])
AX_CHECK_COMPILE_FLAG([-Wswitch],[AX_APPEND_FLAG([-Wswitch])])
AX_CHECK_COMPILE_FLAG([-Wswitch-default],[AX_APPEND_FLAG([-Wswitch-default])])
AX_CHECK_COMPILE_FLAG([-Wswitch-enum],[AX_APPEND_FLAG([-Wswitch-enum])])
AX_CHECK_COMPILE_FLAG([-Wredundant-decls],[AX_APPEND_FLAG([-Wredundant-decls])])

AC_ARG_ENABLE([devel],
    [AS_HELP_STRING([--enable-devel], [enable -Wextra in all Makefiles])])

AS_IF([test "x$enable_devel" == "xyes"],[
    AX_CHECK_COMPILE_FLAG([-Wextra],[AX_APPEND_FLAG([-Wextra])])
    AX_CHECK_COMPILE_FLAG([-fsanitize=address],[AX_APPEND_FLAG([-fsanitize=address])])
    AX_CHECK_COMPILE_FLAG([-fsanitize=pointer-compare],[AX_APPEND_FLAG([-fsanitize=pointer-compare])])
    AX_CHECK_COMPILE_FLAG([-fsanitize=leak],[AX_APPEND_FLAG([-fsanitize=leak])])
    AX_CHECK_COMPILE_FLAG([-fsanitize=undefined],[AX_APPEND_FLAG([-fsanitize=undefined])])
    AX_CHECK_COMPILE_FLAG([-fsanitize=signed-integer-overflow],[AX_APPEND_FLAG([-fsanitize=signed-integer-overflow])])
    AX_CHECK_COMPILE_FLAG([-fsanitize=enum],[AX_APPEND_FLAG([-fsanitize=enum])])
    AX_CHECK_COMPILE_FLAG([-fsanitize=pointer-overflow],[AX_APPEND_FLAG([-fsanitize=pointer-overflow])])
    AX_CHECK_COMPILE_FLAG([-fstack-protector-strong],[AX_APPEND_FLAG([-fstack-protector-strong])])
])

AC_ARG_ENABLE([werror],
    [AS_HELP_STRING([--enable-werror], [enable -Werror in all Makefiles])])

AS_IF([test "x$enable_werror" == "xyes"],[
    AX_CHECK_COMPILE_FLAG([-Werror],[AX_APPEND_FLAG([-Werror])])
])

AC_ARG_ENABLE([testlib],
    [AS_HELP_STRING([--disable-testlib], [disable compile all library test])])

PKG_CHECK_MODULES([CHECK], [check >= 0.9.4],[
        enable_testlib="yes"
    ],[
        enable_testlib="no"
])
AM_CONDITIONAL([COND_BUILD_TEST], [test "x$enable_testlib" != "xno"])
AC_SUBST([CHECK_CFLAGS])
AC_SUBST([CHECK_LIBS])

AC_MSG_NOTICE(["Build devel:  $enable_devel"])
AC_MSG_NOTICE(["Build error:  $enable_werror"])
AC_MSG_NOTICE(["Build tests:  $enable_testlib"])
AC_MSG_NOTICE(["Build vendor: $ax_cv_c_compiler_vendor"])

mkdir -p build/obj

AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
AC_DEFUN([AC_DATAROOTDIR_CHECKED])
pkgconfigdir=$(echo $PKG_CONFIG_PATH)
if test "x$pkgconfigdir" == "x";
then
    pkgconfigdir="${libdir}/pkgconfig"
fi
AC_SUBST([pkgconfigdir], [$pkgconfigdir])

createdate=`date +"%a %b %d %Y"`
yeardate=`date +"%Y"`
AC_SUBST(CRDATE, "$createdate")
AC_SUBST(YDATE, "$yeardate")

AC_CONFIG_LIBOBJ_DIR([build/obj])
AC_CONFIG_FILES([
    Makefile
    test/Makefile
    src/Makefile
    docs/Doxyfile
    docs/man-license.dox
    libwchar2.pc
    package.json
])
AC_OUTPUT
