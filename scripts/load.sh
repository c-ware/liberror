#!/bin/sh
# Process all files with m4 and output them to their respective directories.
# This should be called from the root directory of the project.

# Load a Makefile. This performs a two-pass roll of m4.
#
# $1: the name of the Makefile (dist, 43bsd, etc)
# $2: whether or not to use DOS path separators
process_makefile() {
    if [ "$2" = "" ]; then
        cat template/m4ke.m4 ./template/$1/header.m4 ./template/$1/Makefile | \
            m4                                                              | \
            cat template/m4ke.m4 ./template/$1/header.m4 -                  | \
            m4                                                              | \
            sed 's/^[[:space:]]*$//g'
    else 
        cat template/m4ke.m4 ./template/$1/header.m4 ./template/$1/Makefile | \
            m4                                                              | \
            cat template/m4ke.m4 ./template/$1/header.m4 -                  | \
            m4                                                              | \
            sed 's/^[[:space:]]*$//g' | sed 's/\//\\/g'
    fi
}

# Process the Makefiles
process_makefile dist       > Makefile.dist
process_makefile 43bsd      > Makefile.43bsd
process_makefile nix        > Makefile.nix
process_makefile ult        > Makefile.ult
process_makefile next       > Makefile.next
process_makefile wat    1   > Makefile.wat

# Load documentation
cat src/liberror.h | docgen-extractor-c | docgen-compiler-c | docgen-backend-manpage --section 'cware' --title 'C-Ware Manuals' --date "`date +'%b %d, %Y'`"
