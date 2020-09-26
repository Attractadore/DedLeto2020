#include "file.h"

#include <check.h>

#include <stdlib.h>

START_TEST(test_open_file_stdin_r) {
    FILE* fp = open_file("stdin", "r");
    ck_assert_msg(fp == stdin, "Failed to open stdin with open_file in r mode: expected %p, got %p", stdin, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stdin_rb) {
    FILE* fp = open_file("stdin", "rb");
    ck_assert_msg(fp == stdin, "Failed to open stdin with open_file in rb mode: expected %p, got %p", stdin, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stdin_invalid_mode) {
    FILE* fp = open_file("stdin", "invalid mode");
    ck_assert_msg(fp == NULL, "open_file on stdin with invalid mode: expected %p, got %p", NULL, fp);
}
END_TEST

START_TEST(test_open_file_stdout_w) {
    FILE* fp = open_file("stdout", "w");
    ck_assert_msg(fp == stdout, "Failed to open stdout with open_file in w mode: expected %p, got %p", stdout, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stdout_wb) {
    FILE* fp = open_file("stdout", "wb");
    ck_assert_msg(fp == stdout, "Failed to open stdout with open_file in wb mode: expected %p, got %p", stdout, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stdout_a) {
    FILE* fp = open_file("stdout", "a");
    ck_assert_msg(fp == stdout, "Failed to open stdout with open_file in a mode: expected %p, got %p", stdout, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stdout_ab) {
    FILE* fp = open_file("stdout", "ab");
    ck_assert_msg(fp == stdout, "Failed to open stdout with open_file in ab mode: expected %p, got %p", stdout, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stdout_invalid_mode) {
    FILE* fp = open_file("stdout", "invalid mode");
    ck_assert_msg(fp == NULL, "open_file on stdout with invalid mode: expected %p, got %p", NULL, fp);
}
END_TEST

START_TEST(test_open_file_stderr_w) {
    FILE* fp = open_file("stderr", "w");
    ck_assert_msg(fp == stderr, "Failed to open stderr with open_file in w mode: expected %p, got %p", stderr, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stderr_wb) {
    FILE* fp = open_file("stderr", "wb");
    ck_assert_msg(fp == stderr, "Failed to open stderr with open_file in wb mode: expected %p, got %p", stderr, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stderr_a) {
    FILE* fp = open_file("stderr", "a");
    ck_assert_msg(fp == stderr, "Failed to open stderr with open_file in a mode: expected %p, got %p", stderr, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stderr_ab) {
    FILE* fp = open_file("stderr", "ab");
    ck_assert_msg(fp == stderr, "Failed to open stderr with open_file in ab mode: expected %p, got %p", stderr, fp);
    close_file(fp);
}
END_TEST

START_TEST(test_open_file_stderr_invalid_mode) {
    FILE* fp = open_file("stderr", "invalid mode");
    ck_assert_msg(fp == NULL, "open_file on stderr with invalid mode: expected %p, got %p", NULL, fp);
}
END_TEST

START_TEST(test_close_file_stdin) {
    int res = close_file(stdin);
    ck_assert_msg(res == EOF, "close_file on stdin: expected EOF (%d), got %d", EOF, res);
}
END_TEST

START_TEST(test_close_file_stdout) {
    int res = close_file(stdout);
    ck_assert_msg(res == EOF, "close_file on stdout: expected EOF (%d), got %d", EOF, res);
}
END_TEST

START_TEST(test_close_file_stderr) {
    int res = close_file(stderr);
    ck_assert_msg(res == EOF, "close_file on stderr: expected EOF (%d), got %d", EOF, res);
}
END_TEST

Suite* setup_open_file_suite() {
    Suite* s = suite_create("open_file");

    TCase* open_file_case_stdin = tcase_create("open_file on stdin valid mode");
    tcase_add_test(open_file_case_stdin, test_open_file_stdin_r);
    tcase_add_test(open_file_case_stdin, test_open_file_stdin_rb);
    TCase* open_file_case_stdin_invalid_mode = tcase_create("open_file on stdin invalid mode");
    tcase_add_test(open_file_case_stdin_invalid_mode, test_open_file_stdin_invalid_mode);

    TCase* open_file_case_stdout = tcase_create("open_file on stdout valid mode");
    tcase_add_test(open_file_case_stdout, test_open_file_stdout_w);
    tcase_add_test(open_file_case_stdout, test_open_file_stdout_wb);
    tcase_add_test(open_file_case_stdout, test_open_file_stdout_a);
    tcase_add_test(open_file_case_stdout, test_open_file_stdout_ab);
    TCase* open_file_case_stdout_invalid_mode = tcase_create("open_file on stdout invalid mode");
    tcase_add_test(open_file_case_stdout_invalid_mode, test_open_file_stdout_invalid_mode);

    TCase* open_file_case_stderr = tcase_create("open_file on stderr valid mode");
    tcase_add_test(open_file_case_stderr, test_open_file_stderr_w);
    tcase_add_test(open_file_case_stderr, test_open_file_stderr_wb);
    tcase_add_test(open_file_case_stderr, test_open_file_stderr_a);
    tcase_add_test(open_file_case_stderr, test_open_file_stderr_ab);
    TCase* open_file_case_stderr_invalid_mode = tcase_create("open_file on stderr invalid mode");
    tcase_add_test(open_file_case_stderr_invalid_mode, test_open_file_stderr_invalid_mode);

    suite_add_tcase(s, open_file_case_stdin);
    suite_add_tcase(s, open_file_case_stdin_invalid_mode);

    suite_add_tcase(s, open_file_case_stdout);
    suite_add_tcase(s, open_file_case_stdout_invalid_mode);

    suite_add_tcase(s, open_file_case_stderr);
    suite_add_tcase(s, open_file_case_stderr_invalid_mode);

    return s;
}

Suite* setup_close_file_suite() {
    Suite* s = suite_create("close_file");

    TCase* close_file_case_stdin = tcase_create("close_file on stdin");
    tcase_add_test(close_file_case_stdin, test_close_file_stdin);

    TCase* close_file_case_stdout = tcase_create("close_file on stdout");
    tcase_add_test(close_file_case_stdout, test_close_file_stdout);

    TCase* close_file_case_stderr = tcase_create("close_file on stderr");
    tcase_add_test(close_file_case_stderr, test_close_file_stderr);

    suite_add_tcase(s, close_file_case_stdin);
    suite_add_tcase(s, close_file_case_stdout);
    suite_add_tcase(s, close_file_case_stderr);

    return s;
}

int main() {
    SRunner* sr = srunner_create(NULL);
    srunner_add_suite(sr, setup_open_file_suite());
    srunner_add_suite(sr, setup_close_file_suite());

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    if (num_failed) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
