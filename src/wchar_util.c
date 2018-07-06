
#include "libwchar.h"

// Returns 1 if 'wc' is in the 'delim' string, 0 otherwise.
static int __wc_indelim(wchar_t wc, const wchar_t* delim) {
    while (*delim) {
        if (wc == *delim)
            return 1;
        delim++;
    }
    return 0;
}

wchar_t *_wcpcpy(wchar_t *to, const wchar_t *from) {
    size_t n = 0;
    for (;;) {
        wchar_t wc = from[n];
        to[n] = wc;
        if (wc == L'\0')
            break;
        n++;
    }
    return to + n;
}

wchar_t *_wcpncpy(wchar_t *dst, const wchar_t *src, size_t n) {
    size_t i;
    for (i = 0; i < n; ++i) {
        wchar_t wc = src[i];
        dst[i] = wc;
        if (wc == L'\0')
            break;
    }
    while (i < n) {
        dst[i] = L'\0';
        ++i;
    }
    return &dst[n-1];
}

int _wcscasecmp(const wchar_t *s1, const wchar_t *s2) {
    size_t n = 0;
    for (;;) {
        wchar_t wc1 = _towlower(s1[n]);
        wchar_t wc2 = _towlower(s2[n]);
        if (wc1 != wc2)
            return (wc1 > wc2) ? +1 : -1;
        if (wc1 == L'\0')
            return 0;
        n++;
    }
}

wchar_t *_wcscat(wchar_t *s1, const wchar_t *s2) {
    size_t n = 0;
    while (s1[n] != L'\0')
        n++;

    size_t i = 0;
    for (;;) {
        wchar_t wc = s2[i];
        s1[n+i] = wc;
        if (wc == L'\0')
            break;
        i++;
    }
    return s1;
}

size_t _wcslcat(wchar_t *dst, const wchar_t *src, size_t siz) {
    // Sanity check simplifies code below
    if (siz == 0)
        return 0;

    // Skip dst characters.
    size_t n = 0;
    while (n < siz && dst[n] != L'\0')
      n++;

    if (n == siz)
      return n + _wcslen(src);

    // Copy as much source characters as they fit into siz-1 bytes.
    size_t i;
    for (i = 0; n+i+1 < siz && src[i] != L'\0'; ++i)
        dst[n+i] = src[i];

    // Always zero terminate destination
    dst[n+i] = L'\0';

    // Skip remaining source characters
    while (src[i] != L'\0')
        i++;

    return n+i;
}

size_t _wcslcpy(wchar_t *dst, const wchar_t *src, size_t siz) {
    size_t i;

    // Copy all non-zero bytes that fit into siz-1 destination bytes
    for (i = 0; i + 1 < siz && src[i] != L'\0'; ++i)
        dst[i] = src[i];

    // Always zero-terminate destination buffer
    dst[i] = L'\0';

    // Skip other source characters.
    while (src[i] != L'\0')
        ++i;

    return i;
}

size_t _wcslen(const wchar_t *s) {
    size_t n = 0;
    for (;;) {
        wchar_t wc = s[n];
        if (wc == L'\0')
            return n;
        n++;
    }
}

int _wcsncasecmp(const wchar_t *s1, const wchar_t *s2, size_t n) {
    size_t i;
    for (i = 0; i < n; ++i) {
        wchar_t wc1 = _towlower(s1[i]);
        wchar_t wc2 = _towlower(s2[i]);
        if (wc1 != wc2)
            return (wc1 > wc2) ? +1 : -1;
    }
    return 0;
}

wchar_t *_wcsncat(wchar_t *s1, const wchar_t *s2, size_t n) {
    size_t start = 0;
    while (s1[start] != L'\0')
        start++;

    // Append s2.
    size_t i;
    for (i = 0; i < n; ++i) {
        wchar_t wc = s2[i];
        s1[start + i] = wc;
        if (wc == L'\0')
            break;
    }
    return (wchar_t*)s1;
}

int _wcscmp(const wchar_t *s1, const wchar_t *s2)
{
    wchar_t c1, c2;

    if ((!s1) || (!s2)) return -1;

    do
    {
        c1 = *s1++;
        c2 = *s2++;
        if (c2 == L'\0') return c1 - c2;

    } while (c1 == c2);

    return c1 < c2 ? -1 : 1;
}

int _wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t n) {
    size_t i;
    for (i = 0; i < n; ++i) {
        wchar_t wc = s1[i];
        if (wc != s2[i])
            return (wc > s2[i]) ? +1 : -1;
        if (wc == L'\0')
            break;
    }
    return 0;
}

wchar_t *_wcsncpy(wchar_t *dst, const wchar_t *src, size_t n) {
    // Copy initial characters.
    size_t i;
    for (i = 0; i < n; ++i) {
        wchar_t wc = src[i];
        if (wc == L'\0')
            break;
        dst[i] = wc;
    }
    // zero-pad the remainder.
    for ( ; i < n; ++i)
        dst[i] = L'\0';

    return dst;
}

size_t _wcsnlen(const wchar_t *s, size_t maxlen) {
    size_t n;
    for (n = 0; n < maxlen; ++n) {
        if (s[n] == L'\0')
            break;
    }
    return n;
}

wchar_t *_wcspbrk(const wchar_t *s, const wchar_t *set) {
    size_t n = 0;
    for (;;) {
        wchar_t wc = s[n];
        if (!wc)
            return NULL;
        if (__wc_indelim(wc, set))
            return (wchar_t*)&s[n];
        n++;
    }
}

wchar_t *_wcschr(const wchar_t *s, wchar_t c) {
  // ??? What!? char dummy[1 - 2*(sizeof(wchar_t) != 4)];
  size_t n = 0;
  for (;;) {
    wchar_t wc = s[n];
    if (wc == c)
      return (wchar_t*)s + n;
    if (wc == L'\0')
      return NULL;
    n++;
  }
}

wchar_t *_wcsrchr(const wchar_t *s, wchar_t c) {
    size_t n = 0;
    wchar_t* last = NULL;
    for (;;) {
        wchar_t wc = s[n];
        if (wc == c)
            last = (wchar_t*)s + n;
        if (wc == L'\0')
            break;
        n++;
    }
    return last;
}

size_t _wcsspn(const wchar_t *s, const wchar_t *set) {
    size_t n = 0;
    for (;;) {
        wchar_t wc = s[n];
        if (wc == L'\0')
            break;
        if (!__wc_indelim(wc, set))
            break;
        ++n;
    }
    return n;
}

wchar_t *_wcsstr(const wchar_t *s, const wchar_t *find) {

    unsigned int i;

    if (!s)
        return NULL;

    // Always find the empty string
    if ((!find) || (!find[0]))
        return (wchar_t*)s;

    size_t flen = _wcslen(find);

    for (i = 0; i < flen; i++) {
        wchar_t* p = _wcschr(s, find[i]);
        if (p == NULL)
            return NULL;

        if (!_wmemcmp(p, find, flen))
            return p;

        s = p + 1;
    }
    return NULL;
}

wchar_t *_wcstok(wchar_t *s, const wchar_t *delim, wchar_t **last) {
    if (s == NULL) {
        s = *last;
        if (s == NULL)
            return NULL;
    }

    // Skip leading delimiters first.
    size_t i = 0;
    wchar_t wc;
    for (;;) {
        wc = s[i];
        if (wc && __wc_indelim(wc, delim)) {
            i++;
            continue;
        }
        break;
    }

    if (!wc) {
        // Nothing left.
        *last = NULL;
        return NULL;
    }

    size_t tok_start = i;

    // Skip non delimiters now.
    for (;;) {
        wc = s[i];
        if (wc && !__wc_indelim(wc, delim)) {
            i++;
            continue;
        }
        break;
    }

    if (!wc) {
        *last = NULL;
    } else {
        s[i] = L'\0';
        *last = &s[i+1];
    }
    return &s[tok_start];
}

wchar_t *_wmemchr(const wchar_t *s, wchar_t c, size_t n) {
    size_t i;
    for (i = 0; i < n; ++i) {
        if (s[i] == c)
            return (wchar_t*)&s[i];
    }
    return NULL;
}

int _wmemcmp(const wchar_t *s1, const wchar_t *s2, size_t n) {
    size_t i;
    for (i = 0; i < n; ++i) {
        if (s1[i] == s2[i])
            continue;
        if (s1[i] > s2[i])
            return 1;
        else
            return -1;
    }
    return 0;
}

wchar_t *_wmemcpy(wchar_t *d, const wchar_t *s, size_t n) {
    return (wchar_t *)memcpy((char*)d,
                             (const char*)s,
                             n * sizeof(wchar_t));
}

wchar_t *_wmemmove(wchar_t* d, const wchar_t* s, size_t n) {
    return (wchar_t* )memmove((char*)d,
                              (const char*)s,
                              n * sizeof(wchar_t));
}

wchar_t *_wmemset(wchar_t* s, wchar_t c, size_t n) {
    size_t i;
    for (i = 0; i < n; ++i)
        s[i] = c;
    return s;
}
