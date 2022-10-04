dnl Header of the Makefile. This is included in every pass
dnl of m4.

# Define the implicit rules
NEW_IMPLICIT_RULE(.c, ,`	$(CC) $1 $(CFLAGS) -o $2')
