
AM_MAKEFLAGS = --no-print-directory
AUTOMAKE_OPTIONS = foreign subdir-objects color-tests no-dependencies
ACLOCAL_AMFLAGS = -I build/m4

pkgconfig_DATA = \
    libwchar2.pc

CLEANFILES = \
    libwchar2.pc \
    config.log

EXTRA_DIST = \
    autogen.sh \
    package.json \
    test/createtest.sh \
    test/check_wchar2_MSVC.c \
    src/vfxprint.c \
    src/libwcharext.c \
    src/strptime_w32.c \
    src/wdir_msvc.c \
    src/wdir_gnu.c \
    README.md

EXTRA_HEADERS = \
    config.h \
    config.h.in \
    src/libwchar.h \
    src/table-alpha.h \
    src/table-nonspacing.h \
    src/table-punct.h \
    src/table-wide.h \
    src/libwcharext.h \
    src/libbuild.h \
    include/wchar2ext.h

METASOURCES = AUTO

if COND_BUILD_TEST
    SUBDIRS = src test
else
    SUBDIRS = src
endif

check_valgrind:
	@libtool --mode=execute valgrind --show-reachable=yes --leak-check=full -v --tool=memcheck test/check_wchar2

test_valgrind:
	@libtool --mode=execute valgrind --show-reachable=yes --leak-check=full -v --tool=memcheck test/wchar2test

doxyclean:
	@mv -f docs/man/man3/wchar2.h.3 docs/wchar2.3
	@rm -rf docs/man
	@rm -f docs/doxygen-warning-log.txt docs/doxygen.tag

mandoxy:
	@(cat docs/Doxyfile ; echo "GENERATE_HTML=NO" ; echo "GENERATE_XML=NO") | doxygen -

wwwdoxy:
	@doxygen docs/Doxyfile

cppcheck:
	@cppcheck --quiet --enable=all --inconclusive --report-progress --force --check-library --library=build/STDCppCheck.cfg --suppressions-list=build/LibWchar2Suppressions.txt --inline-suppr --std=c99 --platform=unix32 -D__GNUC__ -DHAVE_CONFIG_H -I.. -I./include -I./src -I/usr/include ./src 2>./check-src.cppcheck

funlist:
	@cproto src/*.c -U__SIZEOF_WCHAR_T__ -D__SIZEOF_WCHAR_T__=2 -DHAVE_CONFIG_H -q

nuget:
	@if [[ -f build/NuGet.exe && -f docs/nuget/libwchar2ext.lib ]] ; then \
		rm -f docs/nuget/*.nupkg ; \
		cp -f docs/nuget/Package.nuspec ./ ; \
		mono build/NuGet.exe pack Package.nuspec -OutputDirectory docs/nuget -Prop Configuration=Release;Platform=AnyCPU ; \
		rm -f ./Package.nuspec ; \
		rm -f docs/nuget/libwchar2ext.lib ; \
	fi

man: mandoxy doxyclean
doc: wwwdoxy doxyclean

