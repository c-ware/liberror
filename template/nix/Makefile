# Makefile for gemeral UNIX operating systems

M4=m4

CC=cc
CFLAGS=-DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr
PREFIX=/usr/local
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
