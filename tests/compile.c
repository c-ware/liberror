/* Verify that all the macros compile */

#include <stdio.h>

#if !defined(__QuasiBSD__)
#include <stdlib.h>
#endif

#include "../src/liberror.h"

int main() {
    char *x = "foo";
    int y = 9;

    LIBERROR_IS_NULL(x, "foo");
    LIBERROR_IS_OOB(3, 10);
    LIBERROR_IS_OOB(y, 10);
    LIBERROR_IS_NEGATIVE(y, "y");
    LIBERROR_IS_POSITIVE(y, "y");
    LIBERROR_IS_VALUE(y, 5, "y", "5");

    return 0;
}
