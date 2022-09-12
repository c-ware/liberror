/*
 * C-Ware License
 * 
 * Copyright (c) 2022, C-Ware
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Redistributions of modified source code must append a copyright notice in
 *    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
 *    copyright notice, and the standalone license file if one exists.
 *
 * A "redistribution" can be constituted as any version of the source code
 * that is intended to comprise some other derivative work of this code. A
 * fork created for the purpose of contributing to any version of the source
 * does not constitute a truly "derivative work" and does not require listing.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * liberror is a C library for helping you help yourself make your code safer.
 * Some notes about this library:
 *  - Every occurrence of 'raising an error' implies writing an error
 *    message to LIBERROR_STREAM, and expanding the LIBERROR_ERROR_CALLBACK
 *    macro, which defaults to aborting the program.
 *
 * There are also two main macros to control some parts of error handling. These
 * two are LIBERROR_ENABLED, and LIBERROR_FREE_SAFETY.
 *
 * LIBERROR_ENABLED, when defined, enables all liberror checks and will cause
 * all the macros to expand to actual error checks. Without this macro defined,
 * all of the error checking macros will expand to empty lines.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * @docgen: constant
 * @brief: the stream to write errors to
 * @name: LIBERROR_STREAM
 * @value: stderr
*/
#define LIBERROR_STREAM     stderr

/*
 * @docgen: macrro_function
 * @brief: handle an error condition
 * @name: LIBERROR_ERROR_CALLBACK
 *
 * @include: liberror.h
 *
 * @description
 * @This macro will be invoked in the scenario of an error condition being
 * @met. It is expanded after the error message is written to LIBERROR_STREAM.
 * @It defaults to flushing the stderr and aborting the progranm, although it
 * @can also perform error-specific code based off the type of error that is
 * @being handled.
 * @description
 *
 * @param type: the type of error being handdled
*/
#define LIBERROR_ERROR_CALLBACK(type) \
    fflush(stderr);                   \
    abort()

/* The types of errors that can be raised */
#define LIBERROR_TYPE_NULL          0
#define LIBERROR_TYPE_BOUNDS        1
#define LIBERROR_TYPE_FILE          2
#define LIBERROR_TYPE_MALLOC        3
#define LIBERROR_TYPE_NEGATIVE      4
#define LIBERROR_TYPE_DOUBLE_FREE   5
#define LIBERROR_TYPE_UNFREEABLE    6

/*
 * @docgen: macro_function
 * @brief: initialize a variable
 * @name: LIBERROR_INIT
 *
 * @include: liberror.h
 * @sinclude: string.h
 *
 * @description
 * @This macro will take a variable, and initialize it with all zero's with the
 * @memset function.
 * @description
 *
 * @param v: the variable to initialize
*/
#define LIBERROR_INIT(v) \
    memset(&(v), 0, sizeof((v)))

#if LIBERROR_ENABLED == 1

/*
 * @docgen: macro_function
 * @brief: generate a structure that contains debug information
 * @name: LIBERROR_BOOKKEEPING
 *
 * @include: liberror.h
 *
 * @description
 * @This macro is intended to be used inside the body of another
 * @structure. It generates a structure which is used by liberror
 * @for debugging, like detecting double frees.
 * @description
*/
#define LIBERROR_BOOKKEEPING() \
    struct {                   \
        int freed;             \
        int freeable;          \
    } liberror

/*
 * @docgen: macro_function
 * @brief: toggle the object's freed field
 * @name: LIBERROR_TOGGLE_FREED
 *
 * @description
 * @This macro will toggle the pointer given to it as freed or unfreed.
 * @Intended to be used in *_free() functions.
 * @description
 *
 * @param ptr: the pointer to toggle
*/
#define LIBERROR_TOGGLE_FREED(ptr) \
    (ptr)->liberror.freed = !ptr->liberror.freed

/*
 * @docgen: macro_function
 * @brief: initialize the book keeping structure in a pointer
 * @name: LIBERROR_INIT_BOOKKEEPING
 *
 * @description
 * @This macro function will initialize book keeping data inside
 * @of the provided pointer.
 * @description
*/
#define LIBERROR_INIT_BOOKKEEPING(ptr) \
    (ptr)->liberror.freed = 0

#define LIBERROR_FREEABLE(ptr)                                                                         \
    do {                                                                                               \
        if((ptr)->liberror.freeable == 1)                                                              \
           break;                                                                                      \
                                                                                                       \
        fprintf(LIBERROR_STREAM, "value " #ptr " cannot be freed (%s:%i)\n", __FILE__, __LINE__); \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_UNFREEABLE);                                             \
    } while(0)

#define LIBERROR_FREED(ptr)                                                                    \
    do {                                                                                          \
        if((ptr)->liberror.freed == 1)                                                                \
           break;                                                                                 \
                                                                                                  \
        fprintf(LIBERROR_STREAM, "attempt to use freed value " #ptr " (%s:%i)\n", __FILE__, __LINE__); \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_UNFREEABLE);                                        \
    } while(0)

/*
 * @docgen: macro_function
 * @brief: raise an error if a value is NULL
 * @name: LIBERROR_IS_NULL
 *
 * @include: liberror.h
 *
 * @description
 * @This macro will take a value to check for being NULL, and raises an error
 * @if the value is NULL.
 * @description
 *
 * @param value: the value to check for NULL
*/
#define LIBERROR_IS_NULL(value)                                                                    \
    do {                                                                                           \
        if((value) != NULL)                                                                        \
            break;                                                                                 \
                                                                                                   \
        fprintf(LIBERROR_STREAM, "value " #value " cannot be NULL (%s:%i)\n", __FILE__, __LINE__); \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_NULL);                                               \
    } while(0)


/*
 * @docgen: macro_function
 * @brief: raise an error if an index is out of bounds
 * @name: LIBERROR_OUT_OF_BOUNDS
 *
 * @include: liberror.h
 *
 * @description
 * @This macro will take an index, and raise an error if the index is outside
 * @of the bounds of 0 and the length provided.
 * @description
 *
 * @param vindex: the index to check
 * @param length: the maximum length
*/
#define LIBERROR_OUT_OF_BOUNDS(vindex, length)                                                              \
    do {                                                                                                    \
        if(((vindex) >= 0) && ((vindex) < (length)))                                                        \
            break;                                                                                          \
                                                                                                            \
        fprintf(LIBERROR_STREAM, "index %i is not within the bounds of 0 and %i (%s:%i)\n", vindex, length, \
                __FILE__, __LINE__);                                                                        \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_BOUNDS);                                                      \
    } while(0)

/*
 * @docgen: macro_function
 * @brief: raise an error if a value is something it should not be 
 * @name: LIBERROR_VALUE
 *
 * @include: liberror.h
 *
 * @description
 * @This macro will take a value, and if it is equal to something it should not be,
 * @it will raise an error.
 * @description
 *
 * @param value: the value to check
 * @param cannot_be: the value it cannot be
*/
#define LIBERROR_VALUE(value, cannot_be) \
    do {                                                                                                     \
        if((value) != (cannot_be))                                                                           \
            break;                                                                                           \
                                                                                                             \
        fprintf(LIBERROR_STREAM, "value " #value " cannot be " #cannot_be " (%s:%i)\n", __FILE__, __LINE__); \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_BOUNDS);                                                       \
    } while(0)

/*
 * @docgen: macro_function
 * @brief: raise an error if a value is negative
 * @name: LIBERROR_IS_NEGATIVE
 *
 * @include: liberror.h
 *
 * @description
 * @This macrro will raise an error if the value provided to it is negative.
 * @This is intended to be used on parameters, but can be used on any value.
 * @The index is casted to a signed long if its negative.
 * @description
 *
 * @param value: the value to check
*/
#define LIBERROR_IS_NEGATIVE(value)                                                     \
    do {                                                                                \
        if((value) >= 0)                                                                \
            break;                                                                      \
                                                                                        \
        fprintf(LIBERROR_STREAM, #value " (%li) is negative (%s:%i)\n", ((long) value), \
                __FILE__, __LINE__);                                                    \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_NEGATIVE);                                \
    } while(0)

/* More specific error generation macros. These exist to produce
 * more helpful error messages when the context for the scenario
 * is more known. */

/*
 * @docgen: macro_function
 * @brief: raise an error if a malloc failed
 * @name: LIBERROR_MALLOC_FAILURE
 *
 * @include: liberror.h
 *
 * @description
 * @This macro will raise an error if a pointer is NULL, with the assumption that
 * @it is being called immediately after a call to malloc, calloc, or realloc.
 * @description
 *
 * @param ptr: the variable with the pointer to check
*/
#define LIBERROR_MALLOC_FAILURE(ptr)                                                         \
    do {                                                                                     \
        if((ptr) != NULL)                                                                    \
            break;                                                                           \
                                                                                             \
        fprintf(LIBERROR_STREAM, "memory allocation failure for pointer " #ptr " (%s:%i)\n", \
                __FILE__, __LINE__);                                                         \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_MALLOC);                                       \
    } while(0)

/*
 * @docgen: macro_function
 * @brief: raise an error if a pointer was already freed.
 * @name: LIBERROR_DOUBLE_FREE
 *
 * @include liberror.h
 *
 * @description
 * @This macro will raise an error if the pointer contains a field called
 * @liberror_freed that is toggled on. It is used to mark a structure as
 * @released from memory.
 * @description
 *
 * @param ptr: the pointer to check
*/
#define LIBERROR_DOUBLE_FREE(ptr)                                                              \
    do {                                                                                       \
        if((ptr)->liberror.freed == 0)                                                         \
            break;                                                                             \
                                                                                               \
        fprintf(LIBERROR_STREAM, "attempt to release already freed pointer" #ptr " (%s:%i)\n", \
                __FILE__, __LINE__);                                                           \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_MALLOC);                                         \
    } while(0)

/*
 * @docgen: macro_function
 * @brief: raise an error if a file failed to open
 * @name: LIBERROR_FILE_OPEN_FAILURE
 *
 * @include: liberror.h
 *
 * @description
 * @This macro will take what it expects to be a file pointer, and raise an
 * @error if it was NULL. If it is NULL, the error reported contains additional
 * @data to report to the output.
 * @description
 *
 * @param file: the file pointer to check
 * @param path: the expected path to the file
*/
#define LIBERROR_FILE_OPEN_FAILURE(file, path)                                                      \
    do {                                                                                            \
        if((file) != NULL)                                                                          \
            break;                                                                                  \
                                                                                                    \
        fprintf(LIBERROR_STREAM, "failed to open file '%s' (%s) (%s:%i)\n", path, strerror(errno),  \
                __FILE__, __LINE__);                                                                \
        LIBERROR_ERROR_CALLBACK(LIBERROR_TYPE_FILE);                                   \
    } while(0)

#endif
