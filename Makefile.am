
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
    README.md

EXTRA_HEADERS = \
    config.h \
    config.h.in \
    src/libwchar.h \
    src/table-alpha.h \
    src/table-nonspacing.h \
    src/table-punct.h \
    src/table-wide.h

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

man: mandoxy doxyclean
doc: wwwdoxy doxyclean

