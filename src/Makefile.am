
include_HEADERS = \
    ../include/wchar2.h \
    ../include/string_s.h \
    libbuild.h \
    libwchar.h \
    vfxprint.h

lib_LTLIBRARIES = libwchar2.la
libwchar2_la_LDFLAGS = -rpath '$(libdir)'
libwchar2_a = -version-info 0:0:1
libwchar2_la_CFLAGS = $(AM_CFLAGS)
libwchar2_la_CPPFLAGS = -I$(top_srcdir)/include
libwchar2_la_SOURCES = \
    libwchar.c \
    fputwc.c \
    fputws.c \
    wfopen.c \
    wmkdir.c \
    wremove.c \
    wrename.c \
    wstat.c \
    waccess.c \
    wbasename.c \
    wpathnormalize.c \
    wmkstemp.c \
    btowc.c \
    mblen.c \
    mbrlen.c \
    mbrtowc.c \
    mbsinit.c \
    mbsnrtowcs.c \
    mbsrtowcs.c \
    mbstowcs.c \
    mbtowc.c \
    wcrtomb.c \
    wcsnrtombs.c \
    wcsrtombs.c \
    wcstombs.c \
    wctob.c \
    wctomb.c \
    wcprint.c \
    wcstocscmp.c \
    wcsregexp.c \
    wcsftime.c \
    wcsptime.c \
    vfprintf.c \
    vfwprintf.c \
    iswalnum.c \
    iswalpha.c \
    iswblank.c \
    iswcntrl.c \
    iswctype.c \
    iswdigit.c \
    iswgraph.c \
    iswlower.c \
    iswprint.c \
    iswpunct.c \
    iswspace.c \
    iswupper.c \
    iswxdigit.c \
    towctrans.c \
    wcswidth.c \
    wctrans.c \
    wcwidth.c \
    wdir.c \
    wchar_utf8.c \
    wchar_util.c \
    wchar_tonum_util.c\
    wstring_util.c \
    string_s.c
