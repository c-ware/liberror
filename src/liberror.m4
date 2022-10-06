dnl C-Ware License
dnl 
dnl Copyright (c) 2022, C-Ware
dnl All rights reserved.
dnl 
dnl Redistribution and use in source and binary forms, with or without
dnl modification, are permitted provided that the following conditions are met:
dnl 
dnl 1. Redistributions of source code must retain the above copyright notice, this
dnl    list of conditions and the following disclaimer.
dnl 
dnl 2. Redistributions in binary form must reproduce the above copyright notice,
dnl    this list of conditions and the following disclaimer in the documentation
dnl    and/or other materials provided with the distribution.
dnl 
dnl 3. Redistributions of modified source code must append a copyright notice in
dnl    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
dnl    copyright notice, and the standalone license file if one exists.
dnl 
dnl A "redistribution" can be constituted as any version of the source code
dnl that is intended to comprise some other derivative work of this code. A
dnl fork created for the purpose of contributing to any version of the source
dnl does not constitute a truly "derivative work" and does not require listing.
dnl 
dnl THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
dnl AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
dnl IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
dnl DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
dnl FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
dnl DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
dnl SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
dnl CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
dnl OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
dnl OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

dnl
dnl This implementation of liberror is the exact same as the CPP implementation,
dnl except with the "M4_" suffix. The APIs are the same, so if you need to lookup a
dnl manual page, just remove the "M4_" suffix. In the case of this library, the checks
dnl will still generate regardless of whether or not LIBERROR_ENABLED is defined, however,
dnl they will be wrapped in an ifdef, so it will still respect it during compilation. The
dnl same logic applies to LIBERROR_STREAM.
dnl

dnl liberror portability macros
#if defined(__ULTRIX__) || defined(__QuasiBSD__)
#   if !defined(CWUTILS_GENERIC)
#       define CWUTILS_GENERIC char *
#   endif
#   if !defined(CWUTILS_NULL)
#       define CWUTILS_NULL    ((char *) 0)
#   endif
#else
#   if !defined(CWUTILS_GENERIC)
#      define CWUTILS_GENERIC void *
#   endif
#   if !defined(CWUTILS_NULL)
#      define CWUTILS_NULL    ((void *) 0)
#   endif
#endif

define(`LIBERROR_IS_NULL_M4', `
    do {
        if(((CWUTILS_GENERIC) $1) != (CWUTILS_NULL))
            break;

        fprintf(LIBERROR_STREAM, "%s cannot be NULL (%s:%i)\n", $2, __FILE__, __LINE__);
        abort();
    } while(0)
')

define(`LIBERROR_IS_OOB_M4', `
    do {
        if((($1) >= 0) && (($1) < ($2)))
            break;

        fprintf(LIBERROR_STREAM, "index %i is out of the bounds of 0 and %i (%s:%i)\n", ($1), ($2), __FILE__, __LINE__);
        abort();
    } while(0)
')

define(`LIBERROR_IS_NEGATIVE_M4', `
    do {
        if(($1) >= 0)
            break;

        fprintf(LIBERROR_STREAM, "number %s cannot be negative (%s:%i)\n", ($2), __FILE__, __LINE__);
        abort();
    } while(0)
')

define(`LIBERROR_IS_POSITIVE_M4', `
    do {
        if(($1) <= 0)
            break;

        fprintf(LIBERROR_STREAM, "number %s is cannot be positive (%s:%i)\n", ($2), __FILE__, __LINE__);
        abort();
    } while(0)
')

define(`LIBERROR_IS_VALUE_M4', `
    do {
        if(($1) != ($2))
            break;

        fprintf(LIBERROR_STREAM, "%s cannot equal %s (%s:%i)\n", ($3), ($4), __FILE__, __LINE__);
        abort();
    } while(0)
')

define(`LIBERROR_MALLOC_FAILURE_M4', `
    do {
        if(((CWUTILS_GENERIC) ($1)) != CWUTILS_NULL)
            break;

        fprintf(LIBERROR_STREAM, "call to malloc for variable \"%s\" failed (%s:%i)\n", ($2), __FILE__, __LINE__);
        abort();
    } while(0)
')

define(`LIBERROR_FILE_OPEN_FAILURE_M4', `
    do {
        if(((CWUTILS_GENERIC) ($1)) != NULL)
           break;

        fprintf(LIBERROR_STREAM, "failed to open file stored in variable \"%s\" at path \"%s\" (%s:%i)", ($2), ($3), __FILE__, __LINE__);
        abort();
    } while(0)
')
