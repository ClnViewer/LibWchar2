
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

/* Original code:
   Copyright (C) 2005-2012 Rich Felker

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sub license, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  Modified in 2013 for the Android Open Source Project.
 */


#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include "libwchar.h"

#if 1
// A wrapper around either a FILE* or a string buffer, used to output
// the result of formatted expansion.
typedef struct {
  FILE*    file;
  char*    buffer;
  size_t   buffer_pos;
  size_t   buffer_size;
} Out;

static void out_init_file(Out* o, FILE* f) {
  memset(o, 0, sizeof(*o));
  o->file = f;
}

static void out_init_buffer(Out* o, char* buffer, size_t buffer_size) {
  memset(o, 0, sizeof(*o));
  o->buffer = buffer;
  o->buffer_pos = 0;
  o->buffer_size = buffer_size;
}

static void out(Out* o, const char* text, size_t length)
{
  if (length <= 0)
    return;
  if (o->file != NULL) {
    fwrite(text, 1, length, o->file);
  } else {
    // Write into a bounded buffer.
    size_t avail = o->buffer_size - o->buffer_pos;
    if (length > avail)
      length = avail;
    memcpy((char*)(o->buffer + o->buffer_pos),
           (const char*)text,
           length
    );
    o->buffer_pos += length;
  }
}

#endif

/* State machine to accept length modifiers + conversion specifiers.
 * Result is 0 on failure, or an argument type to pop on success. */

enum {
	BARE, LPRE, LLPRE, HPRE, HHPRE, BIGLPRE,
	ZTPRE, JPRE,
	STOP,
	PTR, INT, UINT, ULLONG,
#ifndef __LONG_IS_INT
	LONG, ULONG,
#else
#define LONG INT
#define ULONG UINT
#endif
	SHORT, USHORT, CHAR, UCHAR,
#ifdef __ODD_TYPES
	LLONG, SIZET, IMAX, UMAX, PDIFF, UIPTR,
#else
#define LLONG ULLONG
#define SIZET ULONG
#define IMAX LLONG
#define UMAX ULLONG
#define PDIFF LONG
#define UIPTR ULONG
#endif
	DBL, LDBL,
	NOARG,
	MAXSTATE
};

#define S(x) [(x)-'A']

static const unsigned char states[]['z'-'A'+1] = {
	{ /* 0: bare types */
		S('d') = INT, S('i') = INT,
		S('o') = UINT, S('u') = UINT, S('x') = UINT, S('X') = UINT,
		S('e') = DBL, S('f') = DBL, S('g') = DBL, S('a') = DBL,
		S('E') = DBL, S('F') = DBL, S('G') = DBL, S('A') = DBL,
		S('c') = CHAR, S('C') = INT,
		S('s') = PTR, S('S') = PTR, S('p') = UIPTR, S('n') = PTR,
		S('m') = NOARG,
		S('l') = LPRE, S('h') = HPRE, S('L') = BIGLPRE,
		S('z') = ZTPRE, S('j') = JPRE, S('t') = ZTPRE,
	}, { /* 1: l-prefixed */
		S('d') = LONG, S('i') = LONG,
		S('o') = ULONG, S('u') = ULONG, S('x') = ULONG, S('X') = ULONG,
		S('e') = DBL, S('f') = DBL, S('g') = DBL, S('a') = DBL,
		S('E') = DBL, S('F') = DBL, S('G') = DBL, S('A') = DBL,
		S('c') = INT, S('s') = PTR, S('n') = PTR,
		S('l') = LLPRE,
	}, { /* 2: ll-prefixed */
		S('d') = LLONG, S('i') = LLONG,
		S('o') = ULLONG, S('u') = ULLONG,
		S('x') = ULLONG, S('X') = ULLONG,
		S('n') = PTR,
	}, { /* 3: h-prefixed */
		S('d') = SHORT, S('i') = SHORT,
		S('o') = USHORT, S('u') = USHORT,
		S('x') = USHORT, S('X') = USHORT,
		S('n') = PTR,
		S('h') = HHPRE,
	}, { /* 4: hh-prefixed */
		S('d') = CHAR, S('i') = CHAR,
		S('o') = UCHAR, S('u') = UCHAR,
		S('x') = UCHAR, S('X') = UCHAR,
		S('n') = PTR,
	}, { /* 5: L-prefixed */
		S('e') = LDBL, S('f') = LDBL, S('g') = LDBL, S('a') = LDBL,
		S('E') = LDBL, S('F') = LDBL, S('G') = LDBL, S('A') = LDBL,
		S('n') = PTR,
	}, { /* 6: z- or t-prefixed (assumed to be same size) */
		S('d') = PDIFF, S('i') = PDIFF,
		S('o') = SIZET, S('u') = SIZET,
		S('x') = SIZET, S('X') = SIZET,
		S('n') = PTR,
	}, { /* 7: j-prefixed */
		S('d') = IMAX, S('i') = IMAX,
		S('o') = UMAX, S('u') = UMAX,
		S('x') = UMAX, S('X') = UMAX,
		S('n') = PTR,
	}
};

union arg
{
	uintmax_t i;
	long double f;
	void *p;
};

static void pop_arg(union arg *arg, int type, va_list *ap)
{
	/* Give the compiler a hint for optimizing the switch. */
	if ((unsigned)type > MAXSTATE) return;
	switch (type) {
	       case PTR:	arg->p = va_arg(*ap, void *);
	break; case INT:	arg->i = va_arg(*ap, int);
	break; case UINT:	arg->i = va_arg(*ap, unsigned int);
#ifndef __LONG_IS_INT
	break; case LONG:	arg->i = va_arg(*ap, long);
	break; case ULONG:	arg->i = va_arg(*ap, unsigned long);
#endif
	break; case ULLONG:	arg->i = va_arg(*ap, unsigned long long);
	break; case SHORT:	arg->i = (short)va_arg(*ap, int);
	break; case USHORT:	arg->i = (unsigned short)va_arg(*ap, int);
	break; case CHAR:	arg->i = (signed char)va_arg(*ap, int);
	break; case UCHAR:	arg->i = (unsigned char)va_arg(*ap, int);
#ifdef __ODD_TYPES
	break; case LLONG:	arg->i = va_arg(*ap, long long);
	break; case SIZET:	arg->i = va_arg(*ap, size_t);
	break; case IMAX:	arg->i = va_arg(*ap, intmax_t);
	break; case UMAX:	arg->i = va_arg(*ap, uintmax_t);
	break; case PDIFF:	arg->i = va_arg(*ap, ptrdiff_t);
	break; case UIPTR:	arg->i = (uintptr_t)va_arg(*ap, void *);
#endif
	break; case DBL:	arg->f = va_arg(*ap, double);
	break; case LDBL:	arg->f = va_arg(*ap, long double);
	}
}

#if 0
static void out(FILE *f, const char *s, size_t l)
{
	__fwritex((void *)s, l, f);
}
#endif

static void pad(Out* f, char c, int w, int l, int fl)
{
    char _pad[256];
    const int _psz = (int)(sizeof(_pad));

    if ((fl & (__LEFT_ADJ | __ZERO_PAD)) || (l >= w)) return;
    l = (w - l);
    memset(_pad, c, ((l > _psz) ? _psz : l));
    for (; (l >= _psz); l -= _psz)
    {
        out(f, _pad, _psz);
    }
    out(f, _pad, l);
}

static const char xdigits[16] = {
    "0123456789ABCDEF"
};

static char *fmt_x(uintmax_t x, char *s, int lower)
{
    for (; x; x>>=4) *--s = xdigits[(x&15)]|lower;
    return s;
}

static char *fmt_o(uintmax_t x, char *s)
{
	for (; x; x>>=3) *--s = '0' + (x&7);
	return s;
}

static char *fmt_u(uintmax_t x, char *s)
{
	unsigned long y;
	for (   ; x>ULONG_MAX; x/=10) *--s = '0' + x%10;
	for (y=x;           y; y/=10) *--s = '0' + y%10;
	return s;
}

static int fmt_fp(Out* f, long double y, int w, int p, int fl, int t)
{
	uint32_t big[(LDBL_MAX_EXP+LDBL_MANT_DIG)/9+1];
	uint32_t *a, *d, *r, *z;
	int e2 = 0, e, i, j, l, pl;
	const char *prefix="-0X+0X 0X-0x+0x 0x";
	char ebuf0[(3 * sizeof(int))],
            *ebuf = &ebuf0[(3 *sizeof(int))],
             buf[(9 + LDBL_MANT_DIG / 4)],
            *estr,
            *s;

	pl = 1;
	if (signbit(y)) {
		y=-y;
	} else if (fl & __MARK_POS) {
		prefix+=3;
	} else if (fl & __PAD_POS) {
		prefix+=6;
	} else prefix++, pl=0;

	if (!isfinite(y)) {
		char *s = ((t & 32)   ? "inf" : "INF");
		if (y != y) { s = ((t & 32) ? "nan" : "NAN"); pl=0; }
		pad(f, ' ', w, 3 + pl, fl &~ __ZERO_PAD);
		out(f, prefix, pl);
		out(f, s, 3);
		pad(f, ' ', w, 3 + pl, fl ^ __LEFT_ADJ);
		return __MAX(w, 3 + pl);
	}

	y = frexpl(y, &e2) * 2;
	if (y) e2--;

	if ((t|32)=='a') {
		long double round = 8.0;
		int re;

		if (t&32) prefix += 9;
		pl += 2;

		if (p < 0 || p >= (LDBL_MANT_DIG/4 - 1)) re = 0;
		else re=LDBL_MANT_DIG/4-1-p;

		if (re) {
			while (re--) round*=16;
			if (*prefix=='-') {
				y=-y;
				y-=round;
				y+=round;
				y=-y;
			} else {
				y+=round;
				y-=round;
			}
		}

		estr=fmt_u(e2<0 ? -e2 : e2, ebuf);
		if (estr==ebuf) *--estr='0';
		*--estr = (e2<0 ? '-' : '+');
		*--estr = t+('p'-'a');

		s=buf;
		do {
			int x = y;
			*s++=xdigits[x]|(t&32);
			y=16*(y-x);
			if (s-buf==1 && (y||p>0||(fl&__ALT_FORM))) *s++='.';
		} while (y);

		if (p && s-buf-2 < p)
			l = (p+2) + (ebuf-estr);
		else
			l = (s-buf) + (ebuf-estr);

		pad(f, ' ', w, pl+l, fl);
		out(f, prefix, pl);
		pad(f, '0', w, pl+l, fl ^ __ZERO_PAD);
		out(f, buf, s-buf);
		pad(f, '0', (l - (ebuf - estr) - (s - buf)), 0, 0);
		out(f, estr, ebuf-estr);
		pad(f, ' ', w, pl+l, fl ^ __LEFT_ADJ);
		return __MAX(w, pl+l);
	}
	if (p < 0)  { p = 6; }
	if (y)      { y *= 0x1p28, e2 -= 28; }
	if (e2 < 0) { a = r = z = big; }
	else        { a = r = z = (big + sizeof(big)/sizeof(*big) - LDBL_MANT_DIG - 1); }

	do {
		*z = y;
		y = 1000000000*(y-*z++);
	} while (y);

	while (e2 > 0) {
		uint32_t carry=0;
		int sh = __MIN(29,e2);
		for (d=z-1; d>=a; d--) {
			uint64_t x = ((uint64_t)*d<<sh)+carry;
			*d = x % 1000000000;
			carry = x / 1000000000;
		}
		if (!z[-1] && z>a) z--;
		if (carry) *--a = carry;
		e2-=sh;
	}
	while (e2 < 0) {
		uint32_t carry = 0, *b;
		int sh = __MIN(9,-e2);
		for (d=a; d<z; d++) {
			uint32_t rm = *d & ((1 << sh) - 1);
			*d = (*d>>sh) + carry;
			carry = (1000000000>>sh) * rm;
		}
		if (!*a) a++;
		if (carry) *z++ = carry;
		/* Avoid (slow!) computation past requested precision */
		b = (t|32)=='f' ? r : a;
		if (z-b > 2+p/9) z = b+2+p/9;
		e2+=sh;
	}

	if (a<z) {
            for (i = 10, e = (9 * (r - a)); *a >= (uint32_t)i; i*= 10, e++);
	} else { e = 0; }

	/* Perform rounding: j is precision after the radix (possibly neg) */
	j = p - ((t|32)!='f')*e - ((t|32)=='g' && p);
	if (j < 9*(z-r-1)) {
		uint32_t x;
		/* We avoid C's broken division of negative numbers */
		d = r + 1 + ((j+9*LDBL_MAX_EXP)/9 - LDBL_MAX_EXP);
		j += 9*LDBL_MAX_EXP;
		j %= 9;
		for (i=10, j++; j<9; i*=10, j++);
		x = *d % i;
		/* Are there any significant digits past j? */
		if (x || d+1!=z) {
			long double round = __WEV(0x1p,LDBL_MANT_DIG);
			long double small;
			if ((*d / i) & 1) round += 2;
			if (x < (uint32_t)(i / 2))  small = 0x0.8p0;
			else if ((x == (uint32_t)(i / 2)) && ((d + 1) == z)) small=0x1.0p0;
			else small=0x1.8p0;
			if (pl && *prefix=='-') round*=-1, small*=-1;
			*d -= x;
			/* Decide whether to round by probing round+small */
			if (round+small != round) {
				*d = *d + i;
				while (*d == 0xFFFF) // == 65535 // Fix? (*d > 999999999)
				{
					*d--=0;
					(*d)++;
				}
				if (d<a) a=d;
				for (i = 10, e = (9 * (r-a)); *a >= (uint32_t)i; i *= 10, e++);
			}
		}
		if (z>d+1) z=d+1;
		for (; !z[-1] && z>a; z--);
	}
	
	if ((t|32)=='g') {
		if (!p) p++;
		if (p>e && e>=-4) {
			t--;
			p-=e+1;
		} else {
			t-=2;
			p--;
		}
		if (!(fl&__ALT_FORM)) {
			/* Count trailing zeros in last place */
			if (z > a && z[-1]) for (i=10, j=0; z[-1]%i==0; i*=10, j++);
			else j=9;
			if ((t | 32)=='f')
				p = __MIN(p,__MAX(0,9*(z-r-1)-j));
			else
				p = __MIN(p,__MAX(0,9*(z-r-1)+e-j));
		}
	}
	l = 1 + p + (p || (fl&__ALT_FORM));
	if ((t|32)=='f') {
		if (e>0) l+=e;
	} else {
		estr=fmt_u(e<0 ? -e : e, ebuf);
		while(ebuf-estr<2) *--estr='0';
		*--estr = (e<0 ? '-' : '+');
		*--estr = t;
		l += ebuf-estr;
	}

	pad(f, ' ', w, pl+l, fl);
	out(f, prefix, pl);
	pad(f, '0', w, pl+l, fl ^ __ZERO_PAD);

	if ((t|32)=='f') {
		if (a>r) a=r;
		for (d=a; d<=r; d++) {
			char *s = fmt_u(*d, buf+9);
			if (d!=a) while (s>buf) *--s='0';
			else if (s==buf+9) *--s='0';
			out(f, s, buf+9-s);
		}
		if (p || (fl & __ALT_FORM)) out(f, ".", 1);
		for (; d<z && p>0; d++, p-=9) {
			char *s = fmt_u(*d, buf+9);
			while (s>buf) *--s='0';
			out(f, s, __MIN(9,p));
		}
		pad(f, '0', p+9, 9, 0);
	} else {
		if (z<=a) z=a+1;
		for (d=a; d<z && p>=0; d++) {
			char *s = fmt_u(*d, buf+9);
			if (s==buf+9) *--s='0';
			if (d!=a) while (s>buf) *--s='0';
			else {
				out(f, s++, 1);
				if (p>0||(fl & __ALT_FORM)) out(f, ".", 1);
			}
			out(f, s, __MIN(buf+9-s, p));
			p -= buf+9-s;
		}
		pad(f, '0', p+18, 18, 0);
		out(f, estr, ebuf-estr);
	}

	pad(f, ' ', w, pl+l, fl ^ __LEFT_ADJ);

	return __MAX(w, pl+l);
}

static int getint(char **s) {
	int i;
	for (i=0; isdigit(**s); (*s)++)
		i = 10*i + (**s-'0');
	return i;
}

static int printf_core(Out* f, const char *fmt, va_list *ap, union arg *nl_arg, int *nl_type)
{
    char buf[(sizeof(uintmax_t) * 3 + 3 + (LDBL_MANT_DIG / 4))],
         mb[4],
        *a, *z, *s = (char *)fmt;
    const char *prefix;
    wchar_t wc[2], *ws;

    int i, w, p, t, pl, argpos, cnt = 0, l = 0;
    unsigned int st, ps, fl, l10n = 0;
    union arg arg;

	for (;;) {
		/* Update output count, end loop when fmt is exhausted */
		if (cnt >= 0) {
			if (l > INT_MAX - cnt) {
				errno = EOVERFLOW;
				cnt = -1;
			} else cnt += l;
		}
		if (!*s) break;

		/* Handle literal text and %% format specifiers */
		for (a=s; *s && *s!='%'; s++);
		for (z=s; s[0]=='%' && s[1]=='%'; z++, s+=2);
		l = z-a;
		if (f) out(f, a, l);
		if (l) continue;

		if (isdigit(s[1]) && s[2]=='$') {
			l10n=1;
			argpos = s[1]-'0';
			s+=3;
		} else {
			argpos = -1;
			s++;
		}

		/* Read modifier flags */
		for (fl = 0; (((unsigned)*s - ' ') < 32) && (__FLAGMASK & (1U << (*s - ' '))); s++)
			fl |= (1U << (*s - ' '));

		/* Read field width */
		if (*s=='*') {
			if (isdigit(s[1]) && s[2]=='$') {
				l10n=1;
				nl_type[s[1]-'0'] = INT;
				w = nl_arg[s[1]-'0'].i;
				s+=3;
			} else if (!l10n) {
				w = f ? va_arg(*ap, int) : 0;
				s++;
			} else return -1;
			if (w < 0) fl |= __LEFT_ADJ, w =-w;
		} else if ((w = getint(&s)) < 0) return -1;

		/* Read precision */
		if (*s=='.' && s[1]=='*') {
			if (isdigit(s[2]) && s[3]=='$') {
				nl_type[s[2]-'0'] = INT;
				p = nl_arg[s[2]-'0'].i;
				s+=4;
			} else if (!l10n) {
				p = f ? va_arg(*ap, int) : 0;
				s+=2;
			} else return -1;
		} else if (*s=='.') {
			s++;
			p = getint(&s);
		} else p = -1;

		/* Format specifier state machine */
		st=0;
		do {
			if (__OOP(*s)) return -1;
			ps=st;
			st=states[st]S(*s++);
		} while ((st - 1) < STOP);
		if (!st) return -1;

		/* Check validity of argument type (nl/normal) */
		if (st==NOARG) {
			if (argpos>=0) return -1;
			else if (!f) continue;
		} else {
			if (argpos>=0) nl_type[argpos]=st, arg=nl_arg[argpos];
			else if (f) pop_arg(&arg, st, ap);
			else return 0;
		}

		if (!f) continue;

		z = buf + sizeof(buf);
		prefix = "-+   0X0x";
		pl = 0;
		t = s[-1];

		/* Transform ls,lc -> S,C */
		if (ps && (t&15)==3) t&=~32;

		/* - and 0 flags are mutually exclusive */
		if (fl & __LEFT_ADJ) fl &= ~ __ZERO_PAD;

		switch(t) {
		case 'n':
			switch(ps) {
			case BARE: *(int *)arg.p = cnt; break;
			case LPRE: *(long *)arg.p = cnt; break;
			case LLPRE: *(long long *)arg.p = cnt; break;
			case HPRE: *(unsigned short *)arg.p = cnt; break;
			case HHPRE: *(unsigned char *)arg.p = cnt; break;
			case ZTPRE: *(size_t *)arg.p = cnt; break;
			case JPRE: *(uintmax_t *)arg.p = cnt; break;
			}
			continue;
		case 'p':
			p = __MAX(p, (int)(2 * sizeof(void*)));
			t = 'x';
			fl |= __ALT_FORM;
		case 'x': case 'X':
			a = fmt_x(arg.i, z, t&32);
			if (arg.i && (fl & __ALT_FORM)) prefix+=(t>>4), pl=2;
			if (0) {
		case 'o':
			a = fmt_o(arg.i, z);
			if ((fl&__ALT_FORM) && arg.i) prefix+=5, pl=1;
			} if (0) {
		case 'd': case 'i':
			pl=1;
			if (arg.i > INTMAX_MAX) {
				arg.i=-arg.i;
			} else if (fl & __MARK_POS) {
				prefix++;
			} else if (fl & __PAD_POS) {
				prefix+=2;
			} else pl=0;
		case 'u':
			a = fmt_u(arg.i, z);
			}
			if (p >= 0) fl &= ~__ZERO_PAD;
			if (!arg.i && !p) {
				a = z;
				break;
			}
			p = __MAX(p, z-a + !arg.i);
			break;
		case 'c':
			*(a=z-(p=1))=arg.i;
			fl &= ~__ZERO_PAD;
			break;
		case 'm':
			if (1) a = strerror(errno); else
		case 's':
			a = arg.p ? arg.p : "(null)";
#if 1
                        /* On Android, memchr() will return NULL for
                         * out-of-bound requests, e.g. if |p == -1|. */
                        if (p >= 0) {
                          z = memchr(a, 0, p);
                          if (!z) z=a+p;
                          else p=z-a;
                        } else {
                          p=strlen(a);
                          z=a+p;
                        }
#else
			if (!z) z=a+p;
			else p=z-a;
#endif
			fl &= ~__ZERO_PAD;
			break;
		case 'C':
			wc[0] = arg.i;
			wc[1] = 0;
			arg.p = wc;
			p = -1;
		case 'S':
			ws = arg.p;
			for (i = l = 0;
                                (
                                    ((uint32_t)i < (0U + p))        &&
                                    *ws                             &&
                                    ((l = _wctomb(mb, *ws++)) >= 0) &&
                                    ((uint32_t)l <= (0U + (p - i)))
                                );
                        i += l);
			if (l<0) return -1;
			p = i;
			pad(f, ' ', w, p, fl);
			ws = arg.p;
			for (i = 0;
                                (
                                    ((uint32_t)i < (0U + p))        &&
                                    *ws                             &&
                                    (i + ((l = _wctomb(mb, *ws++))) <= p)
                                );
                        i += l) { out(f, mb, l); }
			pad(f, ' ', w, p, fl ^ __LEFT_ADJ);
			l = w>p ? w : p;
			continue;
		case 'e': case 'f': case 'g': case 'a':
		case 'E': case 'F': case 'G': case 'A':
			l = fmt_fp(f, arg.f, w, p, fl, t);
			continue;
		}

		if (p < z-a) p = z-a;
		if (w < pl+p) w = pl+p;

		pad(f, ' ', w, pl+p, fl);
		out(f, prefix, pl);
		pad(f, '0', w, pl+p, fl ^ __ZERO_PAD);
		pad(f, '0', p, z-a, 0);
		out(f, a, z-a);
		pad(f, ' ', w, pl+p, fl ^ __LEFT_ADJ);

		l = w;
	}

	if (f) return cnt;
	if (!l10n) return 0;

	for (i=1; i <= __ARGMAX && nl_type[i]; i++)
		pop_arg(nl_arg+i, nl_type[i], ap);
	for (; i <= __ARGMAX && !nl_type[i]; i++);
	if (i <= __ARGMAX) return -1;
	return 1;
}

size_t _vfprintf(FILE *restrict f, const char *restrict fmt, va_list ap)
{
    va_list ap2;
    int ret, nl_type[(__ARGMAX + 1)] = {0};
    union arg nl_arg[__ARGMAX+1];
    Out out[1];
    out_init_file(out, f);

    va_copy(ap2, ap);
    ret = printf_core(0, fmt, &ap2, nl_arg, nl_type);
    va_end(ap2);
    if (0 < ret) return -1;

    va_copy(ap2, ap);
    ret = printf_core(out, fmt, &ap2, nl_arg, nl_type);
    va_end(ap2);
    return ret;
}

size_t _printf(const char *restrict fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    size_t ret = _vfprintf(stdout, fmt, ap);
    va_end(ap);
    return ret;
}

size_t _fprintf(FILE *restrict f, const char *restrict fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    size_t ret = _vfprintf(f, fmt, ap);
    va_end(ap);
    return ret;
}

size_t _vsnprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap)
{
        va_list ap2;
        int nl_type[__ARGMAX+1] = {0};
        union arg nl_arg[__ARGMAX+1];
        size_t t, r;
        char b;
        Out out[1];

        if (n-1 > INT_MAX-1) {
                if (n) {
                        errno = EOVERFLOW;
                        return -1;
                }
                s = &b;
                n = 1;
        }

        /* Ensure pointers don't wrap if "infinite" n is passed in */
        t = ((char*)0 + SIZE_MAX - s - 1);
        if (n > t) n = t;
        out_init_buffer(out, s, n);

        va_copy(ap2, ap);
        r = printf_core(out, fmt, &ap2, nl_arg, nl_type);
        va_end(ap2);

        if (r < n)
          s[r] = '\0';
        else
          s[n - 1] = '\0';

        return r;
}

size_t _snprintf(char *restrict s, size_t n, const char *restrict fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    size_t ret = _vsnprintf(s, n, fmt, ap);
    va_end(ap);
    return ret;
}

