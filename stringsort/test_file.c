#include "file.h"

#include <check.h>

#include <stdlib.h>

START_TEST(test_open_file_stdin) {
    FILE* fp = open_file("stdin", "r");
    ck_assert_msg(fp == stdin, "Failed to open stdin with open_file: expected %p, got %p", stdin, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stdout) {
    FILE* fp = open_file("stdout", "w");
    ck_assert_msg(fp == stdout, "Failed to open stdout with open_file: expected %p, got %p", stdout, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stderr) {
    FILE* fp = open_file("stderr", "w");
    ck_assert_msg(fp == stderr, "Failed to open stdout with open_file: expected %p, got %p", stderr, fp);
    close_file(fp);
}
END_TEST

Suite* setup_open_file_suite() {
    Suite* s = suite_create("open_file");

    TCase* open_file_case_stdin = tcase_create("open_file on stdin");
    tcase_add_test(open_file_case_stdin, test_open_file_stdin);
    TCase* open_file_case_stdout = tcase_create("open_file on stdout");
    tcase_add_test(open_file_case_stdout, test_open_file_stdout);
    TCase* open_file_case_stderr = tcase_create("open_file on stderr");
    tcase_add_test(open_file_case_stderr, test_open_file_stderr);

    suite_add_tcase(s, open_file_case_stdin);
    suite_add_tcase(s, open_file_case_stdout);
    suite_add_tcase(s, open_file_case_stderr);
    
    return s;
}

int main() {
    SRunner* sr = srunner_create(NULL);
    srunner_add_suite(sr, setup_open_file_suite());

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    if (num_failed) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
