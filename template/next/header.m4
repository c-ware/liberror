dnl Header of the Makefile. This is included in every pass
dnl of m4.

# Define the implicit rules
NEW_IMPLICIT_RULE(.m4, .c, `	$(M4) $1 > $2')
NEW_IMPLICIT_RULE(.c, ,`	$(CPP) $(CPPFLAGS) $1 > $1.i
	$(CC) $1.i $(CFLAGS) -o $2')
