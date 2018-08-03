
CFLAGS = -std=gnu99 -Wall -Wextra -pedantic -ggdb3 -O1
CFLAGSW2 = -fshort-wchar -DUSE_WCHAR2LIB -I../../include
CFLAGSCD = -DUSE_COREDUMP
LDDFLAGSW2 = -L../../src/.libs -Wl,-rpath=../../src/.libs -lwchar2

all: clean exelibc exewchar2

exelibc:
	gcc $(CFLAGS) $(CFLAGSCD) tinydir-test.c -o tinydir-test-wchar2lib.libc

exewchar2:
	gcc $(CFLAGS) $(CFLAGSCD) $(CFLAGSW2) $(LDDFLAGSW2) tinydir-test.c -o tinydir-test-wchar2lib.wchar2

clean:
	@rm -f tinydir-test-wchar2lib.libc tinydir-test-wchar2lib.wchar2 ./core.*

.PHONY: clean exelibc exewchar2
