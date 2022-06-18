# This Makefile is the output of a template Makefile that was
# processed by the m4 macro preprocessor. It is not intended
# to be human readable.

CC=cc
PREFIX=/usr/local
CFLAGS=
OBJS=
TESTS=tests/general.out 
DOCS=./doc/liberror.cware 
MANNAMES=liberror.cware 
DEBUGGER=

all: $(OBJS) $(TESTS)

clean:
	rm -f $(TESTS)
	rm -f $(OBJS)

check:
	./scripts/check.sh $(DEBUGGER)

install:
	for manual in $(MANNAMES); do					  \
		cp doc/$$manual $(PREFIX)/share/man/mancware; \
	done

uninstall:
	for manual in $(MANNAMES); do					 \
		rm -f $(PREFIX)/share/man/mancware/$$manual; \
    done

.c.out:
	$(CC) $< $(OBJS) $(CFLAGS) -o $@
