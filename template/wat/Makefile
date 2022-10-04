# Makefile for Watcom

M4=m4

CC=wcc386
LD=wlink
CFLAGS=-dLIBERROR_ENABLED -dLIBERROR_STREAM=stderr
TESTS=CONVERT_FILES(tests, .c, .exe)

all: $(TESTS) .symbolic

clean: .symbolic
	rm -f $(TESTS)

GENERATE_RULES(tests, .c, .obj)
GENERATE_RULES(tests, .c, .exe, .obj)

.SUFFIXES:

