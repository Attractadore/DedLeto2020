#include "program.h"
#include "lines.h"

#include <assert.h>
#include <locale.h>

int enc_sort(FILE* input_file, FILE* output_file) {
    assert(input_file);
    assert(output_file);

    setlocale(LC_ALL, "");

    LINES* lines = read_lines(input_file);
    if (!lines) {
        return ENC_SORT_READ_ERROR;
    }
    sort_lines(lines, qsort_cmp);
    if (write_lines(lines, output_file) != WRITE_LINES_SUCCESS) {
        return ENC_SORT_WRITE_ERROR;
    }
    free_lines(lines);
    return ENC_SORT_SUCCESS;
}

int rhy_sort(FILE* input_file, FILE* output_file) {
    assert(input_file);
    assert(output_file);

    setlocale(LC_ALL, "");

    LINES* lines = read_lines(input_file);
    if (!lines) {
        return RHY_SORT_READ_ERROR;
    }
    sort_lines(lines, qsort_cmp_reverse);
    if (write_lines(lines, output_file) != WRITE_LINES_SUCCESS) {
        return RHY_SORT_WRITE_ERROR;
    }
    free_lines(lines);
    return RHY_SORT_SUCCESS;
}

void print_enc_sort_error(int err) {
    switch (err) {
        case RHY_SORT_SUCCESS:
            break;
        case ENC_SORT_READ_ERROR:
            fprintf(stderr, "Runtime error: failed to get input\n");
            break;
        case ENC_SORT_WRITE_ERROR:
            fprintf(stderr, "Runtime error: failed to write output\n");
            break;
        default:
            fprintf(stderr, "Runtime error: unknown error\n");
            break;
    }
}

void print_rhy_sort_error(int err) {
    switch (err) {
        case RHY_SORT_SUCCESS:
            break;
        case RHY_SORT_READ_ERROR:
            fprintf(stderr, "Runtime error: failed to get input\n");
            break;
        case RHY_SORT_REV_ERROR:
            fprintf(stderr, "Runtime error: algorithm execution error\n");
            break;
        case RHY_SORT_WRITE_ERROR:
            fprintf(stderr, "Runtime error: failed to write output\n");
            break;
        default:
            fprintf(stderr, "Runtime error: unknown error\n");
            break;
    }
}

void print_help(char const* program_name) {
    printf("This program sorts an input file's lines and stores the result in an output file\n"
           "To use this program, run %s [input file name] [output file name]\n"
           "If you want to read from stdin, [input file name] should be \"stdin\"\n"
           "If you want to write to stdout, [output file name] should be \"stdout\"\n",
           program_name);
}
