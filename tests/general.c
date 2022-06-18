/*
 * General-tests to make sure no compile-time errors occur.
*/

#include "../src/liberror.h"

int main(void) {
    void *x = NULL;
    int y = -1;
    char *format_string = "foo";
    int z = 5;

    liberror_is_null(main, x);
    liberror_in_range(main, y, 1, 10);
    liberror_buffer_is_full(main, format_string, 10, 3);
    liberror_is_number(main, z, "%i", 5);
    liberror_failure(main, printf);
    liberror_unhandled(main);
    liberror_is_negative(main, y);
    liberror_is_positive(main, z);

    return 0;
}
