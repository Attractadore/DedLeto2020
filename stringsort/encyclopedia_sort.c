#include "file.h"
#include "lines.h"
#include "print_help.h"

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

    LINES* lines = read_lines(input_file);
    sort_lines(lines);
    write_lines(lines, output_file);
    free_lines(lines);

    close_file(input_file);
    close_file(output_file);

    return EXIT_SUCCESS;
}
