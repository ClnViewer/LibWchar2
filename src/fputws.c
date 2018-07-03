/*
 * Copyright 2010 Nexenta Systems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "libwchar.h"

static int __fputws(const wchar_t *restrict ws, FILE *restrict fp)
{
    char buf[BUFSIZ];
    int nwritten = 0;
    int nchars   = _wcslen(ws);

    while (nchars > 0) {
	int   nbytes = 0;
	char *ptr    = (char*)&buf;
	while ((nbytes < (BUFSIZ - (MB_LEN_MAX * 2))) && nchars) {
	    int n;
	    if ((n = _wctomb(ptr, *ws)) < 0)
            {
                errno = EILSEQ;
                return 0;
	    }
	    ws++;
	    ptr    += n;
	    nbytes += n;
	    nchars--;
	}
	*ptr = '\0';
	if (fputs(buf, fp) < nbytes) {
	    return 0;
	}
	nwritten += nbytes;
    }
    return (nwritten);
}

int _fputws(const wchar_t *restrict ws, FILE *restrict fp)
{
    return (__fputws(ws, fp));
}
