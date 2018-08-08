
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
#       if defined(__BUILD_vfprintf)
        S('e') = DBL, S('f') = DBL, S('g') = DBL, S('a') = DBL,
        S('E') = DBL, S('F') = DBL, S('G') = DBL, S('A') = DBL,
#       endif
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
