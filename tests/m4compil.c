/* Verify that all the macros compile (from liberror's m4 implementation) */

#include <stdio.h>

#if !defined(__QuasiBSD__)
#include <stdlib.h>
#endif



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
















int main() {
    char *x = "foo";
    int y = 9;
    char *z = CWUTILS_NULL;

    
    do {
        if(((CWUTILS_GENERIC) x) != (CWUTILS_NULL))
            break;

        fprintf(LIBERROR_STREAM, "%s cannot be NULL (%s:%i)\n", "foo", __FILE__, __LINE__);
        abort();
    } while(0)
;
    
    do {
        if(((3) >= 0) && ((3) < (10)))
            break;

        fprintf(LIBERROR_STREAM, "index %i is out of the bounds of 0 and %i (%s:%i)\n", (3), (10), __FILE__, __LINE__);
        abort();
    } while(0)
;
    
    do {
        if(((y) >= 0) && ((y) < (10)))
            break;

        fprintf(LIBERROR_STREAM, "index %i is out of the bounds of 0 and %i (%s:%i)\n", (y), (10), __FILE__, __LINE__);
        abort();
    } while(0)
;
    
    do {
        if((y) >= 0)
            break;

        fprintf(LIBERROR_STREAM, "number %s cannot be negative (%s:%i)\n", ("y"), __FILE__, __LINE__);
        abort();
    } while(0)
;
    
    do {
        if((y) <= 0)
            break;

        fprintf(LIBERROR_STREAM, "number %s is cannot be positive (%s:%i)\n", ("y"), __FILE__, __LINE__);
        abort();
    } while(0)
;
    
    do {
        if((y) != (5))
            break;

        fprintf(LIBERROR_STREAM, "%s cannot equal %s (%s:%i)\n", ("y"), ("5"), __FILE__, __LINE__);
        abort();
    } while(0)
;
    
    do {
        if((z) != CWUTILS_NULL)
            break;

        fprintf(LIBERROR_STREAM, "call to malloc for variable \"%s\" failed (%s:%i)\n", ("z"), __FILE__, __LINE__);
        abort();
    } while(0)
;
    
    do {
        if((z) != NULL)
           break;

        fprintf(LIBERROR_STREAM, "failed to open file stored in variable \"%s\" at path \"%s\" (%s:%i)", ("z"), ("test.txt"), __FILE__, __LINE__);
        abort();
    } while(0)
;
    

    return 0;
}
