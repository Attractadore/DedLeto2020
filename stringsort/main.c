#include "lines.h"
#include "sort.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("This program sorts an input file's lines and stores the result in an output file\n");
        printf("To use this program, run %s [input file name] [output file name]\n", argc ? argv[0] : "[this program]");
        printf("If you want to read from stdin, [input file name] should be \"stdin\"\n");
        printf("If you want to write to stdout, [output file name] should be \"stdout\"\n");
        return EXIT_SUCCESS;
    }

    char const* input_file_name = argv[1];
    FILE* input_stream = NULL;
    if (strcmp(input_file_name, "stdin") == 0) {
        input_stream = stdin;
    } else {
        if (!(input_stream = fopen(input_file_name, "r"))) {
            printf("Failed to open %s for reading\n", input_file_name);
            return EXIT_FAILURE;
        }
    }

    char const* output_file_name = argv[2];
    FILE* output_stream = NULL;
    if (strcmp(output_file_name, "stdout") == 0) {
        output_stream = stdout;
    } else {
        if (!(output_stream = fopen(output_file_name, "w"))) {
            printf("Failed to open %s for writing\n", output_file_name);
            if (input_stream != stdin) {
                fclose(input_stream);
            }
            return EXIT_FAILURE;
        }
    }

    char** lines = NULL;
    size_t num_read_lines = read_lines(input_stream, &lines);

    sort_lines(lines, num_read_lines);

    for (size_t i = 0; i < num_read_lines; i++) {
        fprintf(output_stream, "%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);

    if (input_stream != stdin) {
        fclose(input_stream);
    }
    if (output_stream != stdout) {
        fclose(output_stream);
    }

    return EXIT_SUCCESS;
}
