# Makefile for 4.3 BSD

M4=m4

CC=cc
CPP=/lib/cpp
CFLAGS=
CPPFLAGS=-I/usr/include -DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr
TESTS=CONVERT_FILES(tests, .c)
DOCS=CONVERT_FILES(doc, .cware, .cware)

all: $(TESTS)

install: maninstall

maninstall:
	mkdir -p $(PREFIX)/share/man/mancware
	cp $(DOCS) $(PREFIX)/share/man/mancware

clean:
	rm -f $(TESTS)
	rm -f $(EXAMPLES)

.SUFFIXES:

GENERATE_RULES(tests, .c,)

.PHONY: all clean install maninstall
