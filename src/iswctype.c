
#include "libwchar.h"

#define WCTYPE_ALNUM  1
#define WCTYPE_ALPHA  2
#define WCTYPE_BLANK  3
#define WCTYPE_CNTRL  4
#define WCTYPE_DIGIT  5
#define WCTYPE_GRAPH  6
#define WCTYPE_LOWER  7
#define WCTYPE_PRINT  8
#define WCTYPE_PUNCT  9
#define WCTYPE_SPACE  10
#define WCTYPE_UPPER  11
#define WCTYPE_XDIGIT 12

int _iswctype(wchar_t wc, wctype_t type)
{
	switch (type) {
	case WCTYPE_ALNUM:
		return _iswalnum(wc);
	case WCTYPE_ALPHA:
		return _iswalpha(wc);
	case WCTYPE_BLANK:
		return _iswblank(wc);
	case WCTYPE_CNTRL:
		return _iswcntrl(wc);
	case WCTYPE_DIGIT:
		return _iswdigit(wc);
	case WCTYPE_GRAPH:
		return _iswgraph(wc);
	case WCTYPE_LOWER:
		return _iswlower(wc);
	case WCTYPE_PRINT:
		return _iswprint(wc);
	case WCTYPE_PUNCT:
		return _iswpunct(wc);
	case WCTYPE_SPACE:
		return _iswspace(wc);
	case WCTYPE_UPPER:
		return _iswupper(wc);
	case WCTYPE_XDIGIT:
		return _iswxdigit(wc);
	}
	return 0;
}

wctype_t _wctype(const char *s)
{
	int i;
	const char *p;
	/* order must match! */
	static const char names[] =
		"alnum\0" "alpha\0" "blank\0"
		"cntrl\0" "digit\0" "graph\0"
		"lower\0" "print\0" "punct\0"
		"space\0" "upper\0" "xdigit";
	for (i=1, p=names; *p; i++, p+=6)
		if (*s == *p && !strcmp(s, p))
			return i;
	return 0;
}
