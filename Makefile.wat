# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.











# Define the implicit rules









# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.











# Define the implicit rules









# Makefile for Watcom

M4=m4

CC=wcc386
LD=wlink
CFLAGS=-dLIBERROR_ENABLED -dLIBERROR_STREAM=stderr
TESTS=tests\m4compil.exe tests\compile.exe 

all: $(TESTS) .symbolic

clean: .symbolic
	rm -f $(TESTS)

tests\m4compil.obj: tests\m4compil.c 
	$(CC) tests\m4compil.c -fo=tests\m4compil.obj $(CFLAGS)
tests\compile.obj: tests\compile.c 
	$(CC) tests\compile.c -fo=tests\compile.obj $(CFLAGS)

tests\m4compil.exe: tests\m4compil.obj 
	$(LD) FILE tests\m4compil.obj NAME tests\m4compil.exe
tests\compile.exe: tests\compile.obj 
	$(LD) FILE tests\compile.obj NAME tests\compile.exe


.SUFFIXES:

