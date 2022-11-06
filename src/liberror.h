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
 * @docgen_start
 * @type: project
 * @name: liberror
 * @brief: macros used for runtime safety checks
 *
 * @embed: LIBERROR_IS_NULL
 * @show_brief: 0
 * 
 * @embed: LIBERROR_IS_OOB
 * @show_brief: 0
 *
 * @embed: LIBERROR_IS_NEGATIVE
 * @show_brief: 0
 *
 * @embed: LIBERROR_IS_POSITIVE
 * @show_brief: 0
 *
 * @embed: LIBERROR_IS_VALUE
 * @show_brief: 0
 *
 * @embed: LIBERROR_IS_GREATER
 * @show_brief: 0
 *
 * @embed: LIBERROR_IS_READONLY
 * @show_brief: 0
 *
 * @embed: LIBERROR_STATE
 * @show_brief: 0
 *
 * @embed: LIBERROR_STATE_INIT
 * @show_brief: 0
 *
 * @embed: LIBERROR_STATE_SET
 * @show_brief: 0
 *
 * @description
 * @A collection of macros used for runtime safety checks, like checking if a
 * @pointer is NULL, if an index is out of the bounds, as well as context-specific
 * @macros like file opening failure, and malloc failure. It can even be used
 * @to prevent the programmer from using read-only data with the state system.
 * @
 * @Since safety checks can take a toll on higher-performance applications, so
 * @the macros provided by \Bliberror\B(cware) are togglable at compile time
 * @by defining the \BLIBERROR_ENABLED\B macro.
 * @
 * @If you want to use liberror, you will want to define the following macros
 * @at compile time, or in some central header:\N
 * @
 * @\B#define LIBERROR_STREAM   stderr\B\N
 * @\B#define LIBERROR_ENABLED\B
 * @
 * @Each of the macros shown in the synopsis have their own corresponding
 * @manual page.
 * @description
 *
 * @reference: cware(cware)
 *
 * @docgen_end
*/

#ifndef CWARE_LIBERROR_H
#define CWARE_LIBERROR_H

/* The various error states a structure can be in */
#define LIBERROR_STATE_OK       0
#define LIBERROR_STATE_READONLY 1

/* The file stream to write to */
#if !defined(LIBERROR_STREAM)
#   define LIBERROR_STREAM  stderr
#endif

#if defined(LIBERROR_ENABLED)

/* 
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_STATE
 * @brief: generate the state object
 *
 * @description
 * @This macro function will generate an object which represents
 * @the state of a structure, like whether or not it is readonly,
 * @freed, etc.
 * @description
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @struct MyStructure {
 * @    int x;
 * @    int y;
 * @
 * @    LIBERROR_STATE();\N
 * @};
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_STATE() \
    int liberror_state

/* 
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_STATE_INIT
 * @brief: initialize the state object in a structure
 *
 * @description
 * @This macro function will initialize the state object in a structure
 * @to have a default value of LIBERROR_STATE_OK.
 * @description
 * 
 * @mparam: container
 * @brief: pointer to the structure to initialize
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @struct MyStructure {
 * @    int x;
 * @    int y;
 * @
 * @    LIBERROR_STATE();\N
 * @};
 * @
 * @int main(void) {
 * @    struct MyStructure structure;
 * @
 * @    structure.x = 1;
 * @    structure.y = 1;
 * @    LIBERROR_STATE_INIT(&structure);
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_STATE_INIT(container) \
    (container)->liberror_state = LIBERROR_STATE_OK

/* 
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_STATE_SET
 * @brief: set the state of a data structure
 *
 * @description
 * @This macro function will assign the state of the data structure.
 * @description
 * 
 * @mparam: container
 * @brief: pointer to the structure to set the state of
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @struct MyStructure {
 * @    int x;
 * @    int y;
 * @
 * @    LIBERROR_STATE();\N
 * @};
 * @
 * @int main(void) {
 * @    struct MyStructure structure;
 * @
 * @    structure.x = 1;
 * @    structure.y = 1;
 * @
 * @    // Initialize the state, setting it as read only.
 * @    LIBERROR_STATE_INIT(&structure);
 * @    LIBERROR_STATE_SET(&structure, LIBERROR_STATE_READONLY);
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_STATE_SET(container, state) \
    (container)->liberror_state = (state)

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_IS_NULL
 * @brief: error if a value is null
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error message if the value provided to it is
 * @NULL.
 * @description
 *
 * @mparam: value
 * @brief: the value to check for being NULL
 *
 * @mparam: repr
 * @brief: the string representation of the value
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @int main() {
 * @    char *x = "foo";
 * @
 * @    LIBERROR_IS_NULL(x, "foo");
 * @
 * @    return 0;
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_IS_NULL(value, repr)                                                      \
    do {                                                                                   \
        if(((CWUTILS_GENERIC) value) != (CWUTILS_NULL))                                    \
            break;                                                                         \
                                                                                           \
        fprintf(LIBERROR_STREAM, "%s cannot be NULL (%s:%i)\n", repr, __FILE__, __LINE__); \
        abort();                                                                           \
    } while(0)

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_IS_OOB
 * @brief: error if an index is out of bounds
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error message if the value provided to it is
 * @not within the bounds of 0, and a variable
 * @description
 *
 * @mparam: check
 * @brief: the value to check for being out of bounds
 *
 * @mparam: end
 * @brief: the length of the thing to index
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @int main() {
 * @    char x[16] = {0};
 * @
 * @    LIBERROR_IS_OOB(17, 16);
 * @
 * @    return 0;
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_IS_OOB(check, end)                                                                                      \
    do {                                                                                                                 \
        if((check >= 0) && (check < end))                                                                                \
            break;                                                                                                       \
                                                                                                                         \
        fprintf(LIBERROR_STREAM, "index %i is out of the bounds of 0 and %i (%s:%i)\n", check, end, __FILE__, __LINE__); \
        abort();                                                                                                         \
    } while(0)

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_IS_NEGATIVE
 * @brief: error if a value is negative
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error message if the value provided to it is negative.
 * @description
 *
 * @mparam: value
 * @brief: the value to check for being negative
 *
 * @mparam: repr
 * @brief: the string representation of the value
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @int main() {
 * @    int x = 3;
 * @
 * @    LIBERROR_IS_NEGATIVE(x, "3");
 * @
 * @    return 0;
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_IS_NEGATIVE(value, repr)                                                             \
    do {                                                                                              \
        if(value >= 0)                                                                                \
            break;                                                                                    \
                                                                                                      \
        fprintf(LIBERROR_STREAM, "number %s cannot be negative (%s:%i)\n", repr, __FILE__, __LINE__); \
        abort();                                                                                      \
    } while(0)

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_IS_POSITIVE
 * @brief: error if a value is positive
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error message if the value provided to it is positive.
 * @description
 *
 * @mparam: value
 * @brief: the value to check for being positive
 *
 * @mparam: repr
 * @brief: the string representation of the value
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @int main() {
 * @    int x = 3;
 * @
 * @    LIBERROR_IS_POSITIVE(x, "3");
 * @
 * @    return 0;
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_IS_POSITIVE(value, repr)                                                                \
    do {                                                                                                 \
        if(value <= 0)                                                                                    \
            break;                                                                                       \
                                                                                                         \
        fprintf(LIBERROR_STREAM, "number %s is cannot be positive (%s:%i)\n", repr, __FILE__, __LINE__); \
        abort();                                                                                         \
    } while(0)

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_IS_VALUE
 * @brief: error if a value is equal to another
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error message if the values provided to it
 * @are equal to each other
 * @description
 *
 * @mparam: value
 * @brief: the first value
 *
 * @mparam: is
 * @brief: the second value
 *
 * @mparam: repr_value
 * @brief: the string representation of the first value
 *
 * @mparam: repr_is
 * @brief: the string representation of the second value
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @int main() {
 * @    int x = 3;
 * @
 * @    LIBERROR_IS_VALUE(x, 3, "x", "3");
 * @
 * @    return 0;
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_IS_VALUE(value, is, repr_value, repr_is)                                                  \
    do {                                                                                                   \
        if((value) != (is))                                                                                \
            break;                                                                                         \
                                                                                                           \
        fprintf(LIBERROR_STREAM, "%s cannot equal %s (%s:%i)\n", repr_value, repr_is, __FILE__, __LINE__); \
        abort();                                                                                           \
    } while(0)
 
/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_IS_GREATER
 * @brief: error if a value is greater than another
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error message if a value provided to it is
 * @greater than another one.
 * @description
 *
 * @mparam: x
 * @brief: the value that should be smaller
 *
 * @mparam: y
 * @brief: the value that should be bigger
 *
 * @mparam: repr_x
 * @brief: the string representation of the first value
 *
 * @mparam: repr_y
 * @brief: the string representation of the second value
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @int main() {
 * @    int x = 3;
 * @
 * @    LIBERROR_IS_GREATER(x, 1, "x", "1");
 * @
 * @    return 0;\N
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_IS_GREATER(x, y, repr_x, repr_y)                                                          \
    do {                                                                                                   \
        if((x) < (y))                                                                                      \
            break;                                                                                         \
                                                                                                           \
        fprintf(LIBERROR_STREAM, "%s is greater than %s (%s:%i)\n", repr_x, repr_y, __FILE__, __LINE__);   \
        abort();                                                                                           \
    } while(0)

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_IS_READONLY
 * @brief: error if a value is read only
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error message if a value provided to it has a
 * @member called "liberror_state", and is set to LIBERROR_STATE_READONLY.
 * @description
 *
 * @mparam: value
 * @brief: the value to check
 *
 * @mparam: repr_value
 * @brief: the string representation of the value
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @struct MyStructure {
 * @    int x;
 * @    int y;
 * @
 * @    LIBERROR_STATE();
 * @};
 * @
 * @int main() {
 * @    struct MyStructure structure = {0, 0, 0};
 * @
 * @    LIBERROR_IS_READONLY(structure, "structure");
 * @
 * @    return 0;\N
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_IS_READONLY(value, repr_value)                                                                                  \
    do {                                                                                                                         \
        if((value).liberror_state == LIBERROR_STATE_READONLY)                                                                                       \
            break;                                                                                                               \
                                                                                                                                 \
        fprintf(LIBERROR_STREAM, "Attempt to use a pass a read-only value into '%s' (%s:%i)\n", repr_value, __FILE__, __LINE__); \
        abort();                                                                                                                 \
    } while(0)

/*
 * ==========================
 * # Domain specific errors #
 * ==========================
*/

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_MALLOC_FAILURE
 * @brief: error if a call to malloc failed
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error message if the variable provided to it
 * @is NULL. It assumes that this is because of the result of a call to malloc
 * @failing.
 * @description
 *
 * @mparam: value
 * @brief: the variable containing the pointer to check
 *
 * @mparam: repr
 * @brief: the string name of the variable
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @int main() {
 * @    void *x = malloc(sizeof(int) * 100);
 * @
 * @    LIBERROR_MALLOC_FAILURE(x, "x");
 * @
 * @    free(x);
 * @
 * @    return 0;\N
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_MALLOC_FAILURE(value, repr)                                                                     \
    do {                                                                                                         \
        if(((CWUTILS_GENERIC) (value)) != CWUTILS_NULL)                                                          \
            break;                                                                                               \
                                                                                                                 \
        fprintf(LIBERROR_STREAM, "call to malloc for variable '%s' failed (%s:%i)\n", repr, __FILE__, __LINE__); \
        abort();                                                                                                 \
    } while(0)

/*
 * @docgen_start
 * @type: macro_function
 * @name: LIBERROR_FILE_OPEN_FAILURE
 * @brief: error if a file failed to open
 *
 * @include: liberror/liberror.h
 *
 * @description
 * @This macro will produce an error if the variable given to it is NULL, with
 * @the assumption that if the variable is NULL, that it was because of a failure
 * @to open the file
 * @description
 *
 * @mparam: value
 * @brief: the variable containing the pointer to check
 *
 * @mparam: repr
 * @brief: the string name of the variable that was checked
 *
 * @mparam: file_path
 * @brief: the path to the file
 *
 * @examples
 * @#include "liberror/liberror.h"
 * @
 * @int main() {
 * @    FILE *a_file = fopen("test.txt", "r");
 * @
 * @    LIBERROR_FILE_OPEN_FAILURE(a_file, "a_file", "test.txt");
 * @
 * @    free(x);
 * @
 * @    return 0;\N
 * @}
 * @examples
 *
 * @reference: cware(cware)
 * @reference: liberror(cware)
 *
 * @docgen_end
*/
#define LIBERROR_FILE_OPEN_FAILURE(value, repr, file_path)                                                                                 \
    do {                                                                                                                                   \
        if(((CWUTILS_GENERIC) (value)) != NULL)                                                                                            \
           break;                                                                                                                          \
                                                                                                                                           \
        fprintf(LIBERROR_STREAM, "failed to open file stored in variable '%s' at path '%s' (%s:%i)", repr, file_path, __FILE__, __LINE__); \
        abort();                                                                                                                           \
    } while(0)

#else

/* State junk */
#define LIBERROR_STATE()
#define LIBERROR_STATE_INIT(container)
#define LIBERROR_STATE_SET(container, state)

/* Base error checks */
#define LIBERROR_IS_NULL(value, repr)
#define LIBERROR_IS_OOB(check, end)
#define LIBERROR_IS_NEGATIVE(value, repr)
#define LIBERROR_IS_POSITIVE(value, repr)
#define LIBERROR_IS_VALUE(value, is, repr_value, repr_is)
#define LIBERROR_IS_GREATER(x, y, repr_x, repr_y)
#define LIBERROR_IS_READONLY(value, repr_value)

/* Domain-specific checks */
#define LIBERROR_MALLOC_FAILURE(value, repr)
#define LIBERROR_FILE_OPEN_FAILURE(value, repr, file_path)

#endif
#endif
