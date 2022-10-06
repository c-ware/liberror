# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.











# Define the implicit rules






# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.











# Define the implicit rules






# Makefile for gemeral UNIX operating systems

M4=m4

CC=cc
CFLAGS=-DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr
PREFIX=/usr/local
TESTS=tests/m4compil tests/compile 
DOCS=doc/LIBERROR_IS_VALUE.cware doc/LIBERROR_IS_NEGATIVE.cware doc/liberror.cware doc/LIBERROR_FILE_OPEN_FAILURE.cware doc/LIBERROR_IS_NULL.cware doc/LIBERROR_MALLOC_FAILURE.cware doc/LIBERROR_IS_POSITIVE.cware doc/LIBERROR_IS_OOB.cware 

all: $(TESTS)

install: maninstall

maninstall:
	mkdir -p $(PREFIX)/share/man/mancware
	cp $(DOCS) $(PREFIX)/share/man/mancware

clean:
	rm -f $(TESTS)
	rm -f $(EXAMPLES)

.SUFFIXES:

tests/m4compil: tests/m4compil.c 
	$(CC) tests/m4compil.c $(CFLAGS) -o tests/m4compil
tests/compile: tests/compile.c 
	$(CC) tests/compile.c $(CFLAGS) -o tests/compile


.PHONY: all clean install maninstall
