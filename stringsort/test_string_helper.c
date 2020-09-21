#include "string_helper.h"

#include <check.h>

#include <stdlib.h>

int main() {
    SRunner* sr = srunner_create(NULL);

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    if (num_failed) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
