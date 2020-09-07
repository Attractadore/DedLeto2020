#pragma once
#include <stdio.h>

#define ENC_SORT_SUCCESS 0
#define ENC_SORT_READ_ERROR -1
#define ENC_SORT_WRITE_ERROR -2
#define RHY_SORT_SUCCESS 0
#define RHY_SORT_READ_ERROR -1
#define RHY_SORT_REV_ERROR -2
#define RHY_SORT_WRITE_ERROR -3

int enc_sort(FILE* input_file, FILE* output_file);
int rhy_sort(FILE* input_file, FILE* output_file);
void print_enc_sort_error(int err);
void print_rhy_sort_error(int err);
void print_help(const char* program_name);
