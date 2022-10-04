dnl Makefile to be used for distribution. Compiles templates for source
dnl files, generates documentation, etc.

M4=m4

CC=cc
PREFIX=/usr/local
CFLAGS=-Wall -Wextra -Wpedantic -Wno-unused-but-set-variable -g -DLIBERROR_ENABLED -DLIBERROR_STREAM=stderr
TESTS=CONVERT_FILES(tests, .c)
DOCS=CONVERT_FILES(doc, .cware, .cware)

all: $(TESTS)

install: maninstall

clean:
	rm -f $(TESTS)
	rm -f $(EXAMPLES)

maninstall:
	mkdir -p $(PREFIX)/share/man/mancware
	cp $(DOCS) $(PREFIX)/share/man/mancware

GENERATE_RULES(tests, .c,)

.PHONY: all clean install maninstall
.SUFFIXES:
