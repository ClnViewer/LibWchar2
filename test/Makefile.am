
CHECK_CFLAGS = @CHECK_CFLAGS@
CHECK_LIBS = @CHECK_LIBS@

bin_PROGRAMS = wchar2test
wchar2test_SOURCES = t.c $(top_srcdir)/include/wchar2.h
wchar2test_CFLAGS = $(AM_CFLAGS) $(CHECK_CFLAGS)
wchar2test_CPPFLAGS = -I$(top_srcdir)/include
wchar2test_LDFLAGS = -L$(top_srcdir)/src/.libs/ $(LDFLAGS)
wchar2test_LDADD = $(top_srcdir)/src/.libs/libwchar2.a $(CHECK_LIBS)

TESTS = check_wchar2
noinst_PROGRAMS = check_wchar2
check_wchar2_SOURCES = check_wchar2.c $(top_srcdir)/include/wchar2.h
check_wchar2_CFLAGS = $(CFLAGS) $(CHECK_CFLAGS)
check_wchar2_LDFLAGS = -L$(top_srcdir)/src/.libs/ $(LDFLAGS)
check_wchar2_LDADD = $(top_srcdir)/src/.libs/libwchar2.a $(CHECK_LIBS)

clean-local:
	@rm -f core.* test-*.txt
	@rm -rf thisdir
