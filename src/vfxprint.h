
#ifndef WCHAR2_INT_WPRINT_H
#define WCHAR2_INT_WPRINT_H

#if !defined(_GNU_SOURCE)
#   define _GNU_SOURCE
#endif

union arg
{
    uintmax_t i;
    long double f;
    void *p;
};

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

static inline void pop_arg(union arg *arg, int type, va_list *ap)
{
    /* Give the compiler a hint for optimizing the switch. */
    if ((unsigned)type > MAXSTATE) { return; }
        switch (type)
        {
                case PTR:    arg->p = va_arg(*ap, void *);
        break;  case INT:    arg->i = (uintmax_t)((int)va_arg(*ap, int));
        break;  case UINT:   arg->i = (uintmax_t)((unsigned int)va_arg(*ap, unsigned int));
#ifndef __LONG_IS_INT
        break;  case LONG:   arg->i = (uintmax_t)((long)va_arg(*ap, long));
        break;  case ULONG:  arg->i = (uintmax_t)((unsigned long)va_arg(*ap, unsigned long));
#endif
        break;  case ULLONG: arg->i = (uintmax_t)((unsigned long long)va_arg(*ap, unsigned long long));
        break;  case SHORT:  arg->i = (uintmax_t)((short)va_arg(*ap, int));
        break;  case USHORT: arg->i = (uintmax_t)((unsigned short)va_arg(*ap, int));
        break;  case CHAR:   arg->i = (uintmax_t)((signed char)va_arg(*ap, int));
        break;  case UCHAR:  arg->i = (uintmax_t)((unsigned char)va_arg(*ap, int));
#ifdef __ODD_TYPES
        break;  case LLONG:  arg->i = (uintmax_t)((long long)va_arg(*ap, long long);
        break;  case SIZET:  arg->i = (uintmax_t)((size_t)va_arg(*ap, size_t));
        break;  case IMAX:   arg->i = (uintmax_t)((intmax_t)va_arg(*ap, intmax_t));
        break;  case UMAX:   arg->i = (uintmax_t)((uintmax_t)va_arg(*ap, uintmax_t));
        break;  case PDIFF:  arg->i = (uintmax_t)((ptrdiff_t)va_arg(*ap, ptrdiff_t));
        break;  case UIPTR:  arg->i = (uintptr_t)((void*)va_arg(*ap, void*));
#endif
        break;  case DBL:    arg->f = (long double)((double)va_arg(*ap, double));
        break;  case LDBL:   arg->f = (long double)va_arg(*ap, long double);
    }
}

#endif
