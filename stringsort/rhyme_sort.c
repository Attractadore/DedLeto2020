#include "file.h"
#include "program.h"

#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        print_help(argc > 0 ? argv[0] : "[program_name]");
        return EXIT_SUCCESS;
    }

    char const* input_file_name = argv[1];
    FILE* input_file = open_file(input_file_name, "rb");
    if (!input_file) {
        printf("Failed to open %s for reading\n", input_file_name);
        return EXIT_FAILURE;
    }

    char const* output_file_name = argv[2];
    FILE* output_file = open_file(output_file_name, "wb");
    if (!output_file) {
        printf("Failed to open %s for writing\n", output_file_name);
        close_file(input_file);
        return EXIT_FAILURE;
    }

    int err = rhy_sort(input_file, output_file);
    print_rhy_sort_error(err);

    close_file(input_file);
    close_file(output_file);

    if (err != RHY_SORT_SUCCESS) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
