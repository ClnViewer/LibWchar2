
CFLAGS = -std=gnu99 -Wall -Wextra -pedantic
CFLAGSW2 = -fshort-wchar -DWS_FS_REDEFINE -I../include
LDDFLAGSW2 = -L../src/.libs -Wl,-rpath=../src/.libs -lwchar2

all: clean exelibc exewchar2

exelibc:
	gcc $(CFLAGS) fs-redifine.c -o fs-redifine.libc

exewchar2:
	gcc $(CFLAGS) $(CFLAGSW2) $(LDDFLAGSW2) fs-redifine.c -o fs-redifine.wchar2

clean:
	@rm -f fs-redifine.libc fs-redifine.wchar2 open-file-name.txt

.PHONY: clean exelibc exewchar2
