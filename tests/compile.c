/* Verify that all the macros compile */

#include <stdio.h>

#if !defined(__QuasiBSD__)
#include <stdlib.h>
#endif

#include "common.h"
#include "../src/liberror.h"

struct MyStructure {
    int x;
    int y;

    LIBERROR_STATE();
};

int main() {
    char *x = "foo";
    int y = 9;
    char *z = CWUTILS_NULL;
    struct MyStructure structure;

    LIBERROR_STATE_INIT(&structure);
    LIBERROR_STATE_SET(&structure, LIBERROR_STATE_READONLY);

    LIBERROR_IS_NULL(x, "foo");
    LIBERROR_IS_OOB(3, 10);
    LIBERROR_IS_OOB(y, 10);
    LIBERROR_IS_NEGATIVE(y, "y");
    LIBERROR_IS_POSITIVE(y, "y");
    LIBERROR_IS_VALUE(y, 5, "y", "5");
    LIBERROR_MALLOC_FAILURE(z, "z");
    LIBERROR_FILE_OPEN_FAILURE(z, "z", "test.txt");
    LIBERROR_IS_READONLY(structure, "structure");

    return 0;
}
