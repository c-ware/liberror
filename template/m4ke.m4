# A collection of m4 macros to make writing Makefiles easier.
# Recommended for a two-pass m4 system.

dnl Convert all files of a certain file extension in a
dnl directory to another extension, except for, or a
dnl blacklist of files with the MAIN_FILENAME name if
dnl provided.
dnl
dnl $1 the directory
dnl $2 the input file extension
dnl $3 the output file extension
dnl $4 the name of files to filter
dnl $5 not provided if its a blacklist, provided if its a whitelist
define(`CONVERT_FILES', `ifelse($4, `', `syscmd(find $1 -type f | grep "\$2\$" | sed "s/\$2\$/$3/g" | tr "\\n" " ")',
                                        `ifelse($5, `', `syscmd(find $1 -type f | grep -v $4 | grep "\$2\$" | sed "s/\$2\$/$3/g" | tr "\\n" " ")',
                                                        `syscmd(find $1 -type f | grep $4 | grep "\$2\$" | sed "s/\$2\$/$3/g" | tr "\\n" " ")')')')

dnl Convert all files of a certain file extension in a
dnl directory to another extension, except for, or a
dnl blacklist of files with the MAIN_FILENAME name if
dnl provided. The files will be in a comma-delimited list, as
dnl opposed to a space-delimited one.
dnl
dnl $1 the directory
dnl $2 the input file extension
dnl $3 the output file extension
dnl $4 the name of files to filter
dnl $5 not provided if its a blacklist, provided if its a whitelist
define(`CONVERT_FILES_TO_COMMA', `ifelse($4, `', `syscmd(find $1 -type f | grep "\$2\$" | sed "s/\$2\$/$3/g" | tr "\\n" "`,'" | sed "s/.\$//g")', `ifelse($5, `', `syscmd(find $1 -type f | grep -v $4 | grep "\$2\$" | sed "s/\$2\$/$3/g" | tr "\\n" "`,'" | sed "s/.\$//g")', `syscmd(find $1 -type f | grep $4 | grep "\$2\$" | sed "s/\$2\$/$3/g" | tr "\\n" "`,'" | sed "s/.\$//g")')')')

dnl Declare a new implicit rule that will be expanded for
dnl each input and output extension. The input file should
dnl be expected as $1, and the output file $2
dnl
dnl $1 the input file extension
dnl $2 the output file extension
dnl $3 the body to expand
define(`NEW_IMPLICIT_RULE', `
	define(translit(IMPLICIT_RULE$1$2, ., _), `$3')
')

dnl Create a new rule with the filename, the input suffix,
dnl an output suffix. Uses the implicit macro rule defined
dnl with the file extensions
dnl
dnl $1 the name of the file, without extensions
dnl $2 the input extension
dnl $3 the output extension
dnl $4 extra dependencies
define(`NEW_RULE', `$1$3: $1$2 $4
translit(IMPLICIT_RULE$2$3, ., _)($1$2, $1$3)')

dnl Generate calls to NEW_RULE based off of an input
dnl file extension, and an output file extension.
dnl
dnl $1 the directory
dnl $2 the input file extension
dnl $3 the output file extension
dnl $4 the input file extension to change to (useful for multi-stage compilation)
define(`GENERATE_RULES', `ifelse($4, `', `syscmd(`find $1 -type f -name "*$2" | sed "s/\..*//g" | sed "s/^/NEW_RULE(/g" | sed "s/$/, $2, $3)/g"')',
                                         `syscmd(`find $1 -type f -name "*$2" | sed "s/\..*//g" | sed "s/^/NEW_RULE(/g" | sed "s/$/, $2, $3)/g" | sed "s/\$2/$4/g"')')')
