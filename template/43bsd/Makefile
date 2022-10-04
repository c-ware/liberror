# Makefile for 4.3 BSD

M4=m4

CC=cc
CFLAGS=-D__QuasiBSD__ -DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr
TESTS=CONVERT_FILES(tests, .c)

all: $(TESTS)

clean:
	rm -f $(TESTS)

.SUFFIXES:

GENERATE_RULES(tests, .c,)

.PHONY: all clean
