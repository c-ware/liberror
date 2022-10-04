dnl Header of the Makefile. This is included in every pass
dnl of m4.

# Define the implicit rules
NEW_IMPLICIT_RULE(.m4, .c, `	$(M4) $1 > $2')
NEW_IMPLICIT_RULE(.c, .obj,`	$(CC) $1 -fo=$2 $(CFLAGS)')
NEW_IMPLICIT_RULE(.obj, .exe,`	$(LD) FILE $1 NAME $2')
