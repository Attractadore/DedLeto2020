#include "string_helper.h"

#include <check.h>

#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
START_TEST(test_wstrcnt_1) {
    wchar_t const wstr[] = L"I am indisposed";
    wchar_t wc = L'i';
    size_t exp_cnt = 2;
    size_t cnt = wstrcnt(wstr, wc);
    ck_assert_msg(cnt == exp_cnt,
                  "Failed to count occurances of '%lc' in \"%ls\": "
                  "expected %ld, got %ld",
                  wc, wstr, exp_cnt, cnt);
}
END_TEST

START_TEST(test_wstrcnt_2) {
    wchar_t const wstr[] = L"in this string you will find many i's";
    wchar_t wc = L'i';
    size_t exp_cnt = 6;
    size_t cnt = wstrcnt(wstr, wc);
    ck_assert_msg(cnt == exp_cnt,
                  "Failed to count occurances of '%lc' in \"%ls\": "
                  "expected %ld, got %ld",
                  wc, wstr, exp_cnt, cnt);
}
END_TEST

START_TEST(test_wstrcnt_3) {
    wchar_t const wstr[] = L"no letters here";
    wchar_t wc = L'i';
    size_t exp_cnt = 0;
    size_t cnt = wstrcnt(wstr, wc);
    ck_assert_msg(cnt == exp_cnt,
                  "Failed to count occurances of '%lc' in \"%ls\": "
                  "expected %ld, got %ld",
                  wc, wstr, exp_cnt, cnt);
}
END_TEST

START_TEST(test_wstrcnt_4) {
    wchar_t const wstr[] = L"ыы тесты ыы";
    wchar_t wc = L'ы';
    size_t exp_cnt = 5;
    size_t cnt = wstrcnt(wstr, wc);
    ck_assert_msg(cnt == exp_cnt,
                  "Failed to count occurances of '%lc' in \"%ls\": "
                  "expected %ld, got %ld",
                  wc, wstr, exp_cnt, cnt);
}

START_TEST(test_wstrcnt_empty) {
    wchar_t const wstr[] = L"";
    wchar_t wc = L'i';
    size_t exp_cnt = 0;
    size_t cnt = wstrcnt(wstr, wc);
    ck_assert_msg(cnt == exp_cnt,
                  "Failed to count occurances of '%lc' in \"%ls\": "
                  "expected %ld, got %ld",
                  wc, wstr, exp_cnt, cnt);
}
END_TEST

START_TEST(test_wstrcnt_null) {
    wchar_t const wstr[] = L"string with no null in it";
    wchar_t wc = L'\0';
    size_t exp_cnt = 0;
    size_t cnt = wstrcnt(wstr, wc);
    ck_assert_msg(cnt == exp_cnt,
                  "Failed to count occurances of '%lc' in \"%ls\": "
                  "expected %ld, got %ld",
                  wc, wstr, exp_cnt, cnt);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_equal_1) {
    wide_string str1 = {
        L"abc",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abc",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_equal_2) {
    wide_string str1 = {
        L"абв",
        wcslen(str1.str)};
    wide_string str2 = {
        L"абв",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_equal_on_alpha) {
    wide_string str1 = {
        L"!@#$%^&*() abc !@#$%^&*()",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abc",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_not_equal_less) {
    wide_string str1 = {
        L"abc",
        wcslen(str1.str)};
    wide_string str2 = {
        L"bcd",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_not_equal_less_on_alpha) {
    wide_string str1 = {
        L"!@#$%^&*() abc !@#$%^&*()",
        wcslen(str1.str)};
    wide_string str2 = {
        L"bcd",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_not_equal_greater) {
    wide_string str1 = {
        L"abc",
        wcslen(str1.str)};
    wide_string str2 = {
        L"bcd",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str2, &str1);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_not_equal_greater_on_alpha) {
    wide_string str1 = {
        L"!@#$%^&*() abc !@#$%^&*()",
        wcslen(str1.str)};
    wide_string str2 = {
        L"bcd",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str2, &str1);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_prefix) {
    wide_string str1 = {
        L"abc",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abcdef",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_prefix_on_alpha) {
    wide_string str1 = {
        L"!@#$%^&*() abc !@#$%^&*()",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abcdef",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_empty) {
    wide_string str1 = {
        L"",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abc",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_fow_empty_on_alpha) {
    wide_string str1 = {
        L" !@#$%^&*() ",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abc",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_fow(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_equal_1) {
    wide_string str1 = {
        L"abc",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abc",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_equal_2) {
    wide_string str1 = {
        L"абв",
        wcslen(str1.str)};
    wide_string str2 = {
        L"абв",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_equal_on_alpha) {
    wide_string str1 = {
        L"!@#$%^&*() abc !@#$%^&*()",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abc",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_not_equal_less) {
    wide_string str1 = {
        L"abc",
        wcslen(str1.str)};
    wide_string str2 = {
        L"bcd",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_not_equal_less_on_alpha) {
    wide_string str1 = {
        L"!@#$%^&*() abc !@#$%^&*()",
        wcslen(str1.str)};
    wide_string str2 = {
        L"bcd",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_not_equal_greater) {
    wide_string str1 = {
        L"abc",
        wcslen(str1.str)};
    wide_string str2 = {
        L"bcd",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str2, &str1);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_not_equal_greater_on_alpha) {
    wide_string str1 = {
        L"!@#$%^&*() abc !@#$%^&*()",
        wcslen(str1.str)};
    wide_string str2 = {
        L"bcd",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str2, &str1);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_prefix) {
    wide_string str1 = {
        L"def",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abcdef",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_prefix_on_alpha) {
    wide_string str1 = {
        L"!@#$%^&*() def !@#$%^&*()",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abcdef",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_empty) {
    wide_string str1 = {
        L"",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abc",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_rev_empty_on_alpha) {
    wide_string str1 = {
        L" !@#$%^&*() ",
        wcslen(str1.str)};
    wide_string str2 = {
        L"abc",
        wcslen(str2.str)};
    int res = wstrcmp_alpha_rev(&str1, &str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1.str, str2.str, expected_res, res);
}
END_TEST

Suite* setup_wstrcnt_suite() {
    Suite* s = suite_create("wstrcnt");

    TCase* wstrcnt_base = tcase_create("basic usage of wstrcnt");
    tcase_add_test(wstrcnt_base, test_wstrcnt_1);
    tcase_add_test(wstrcnt_base, test_wstrcnt_2);
    tcase_add_test(wstrcnt_base, test_wstrcnt_3);
    tcase_add_test(wstrcnt_base, test_wstrcnt_4);

    TCase* wstrcnt_empty = tcase_create("wstrcnt on empty string");
    tcase_add_test(wstrcnt_empty, test_wstrcnt_empty);

    TCase* wstrcnt_null = tcase_create("wstrcnt on null character");
    tcase_add_test(wstrcnt_null, test_wstrcnt_null);

    suite_add_tcase(s, wstrcnt_base);
    suite_add_tcase(s, wstrcnt_empty);
    suite_add_tcase(s, wstrcnt_null);

    return s;
}

Suite* setup_wstrcmp_alpha_fow_suite() {
    Suite* s = suite_create("wstrcmp_alpha_fow");

    TCase* wstrcmp_alpha_fow_equal = tcase_create("wstrcmp_alpha_fow on equal strings");
    tcase_add_test(wstrcmp_alpha_fow_equal, test_wstrcmp_alpha_fow_equal_1);
    tcase_add_test(wstrcmp_alpha_fow_equal, test_wstrcmp_alpha_fow_equal_2);
    tcase_add_test(wstrcmp_alpha_fow_equal, test_wstrcmp_alpha_fow_equal_on_alpha);

    TCase* wstrcmp_alpha_fow_unequal = tcase_create("wstrcmp_alpha_fow on unequal strings");
    tcase_add_test(wstrcmp_alpha_fow_unequal, test_wstrcmp_alpha_fow_not_equal_less);
    tcase_add_test(wstrcmp_alpha_fow_unequal, test_wstrcmp_alpha_fow_not_equal_less_on_alpha);
    tcase_add_test(wstrcmp_alpha_fow_unequal, test_wstrcmp_alpha_fow_not_equal_greater);
    tcase_add_test(wstrcmp_alpha_fow_unequal, test_wstrcmp_alpha_fow_not_equal_greater_on_alpha);

    TCase* wstrcmp_alpha_fow_prefix = tcase_create("wstrcmp_alpha_fow when one string is a prefix of another");
    tcase_add_test(wstrcmp_alpha_fow_prefix, test_wstrcmp_alpha_fow_prefix);
    tcase_add_test(wstrcmp_alpha_fow_prefix, test_wstrcmp_alpha_fow_prefix_on_alpha);

    TCase* wstrcmp_alpha_fow_empty = tcase_create("wstrcmp_alpha_fow when one string is empty");
    tcase_add_test(wstrcmp_alpha_fow_empty, test_wstrcmp_alpha_fow_empty);
    tcase_add_test(wstrcmp_alpha_fow_empty, test_wstrcmp_alpha_fow_empty_on_alpha);

    suite_add_tcase(s, wstrcmp_alpha_fow_equal);
    suite_add_tcase(s, wstrcmp_alpha_fow_unequal);
    suite_add_tcase(s, wstrcmp_alpha_fow_prefix);
    suite_add_tcase(s, wstrcmp_alpha_fow_empty);

    return s;
}

Suite* setup_wstrcmp_alpha_rev_suite() {
    Suite* s = suite_create("wstrcmp_alpha_rev");

    TCase* wstrcmp_alpha_rev_equal = tcase_create("wstrcmp_alpha_rev on equal strings");
    tcase_add_test(wstrcmp_alpha_rev_equal, test_wstrcmp_alpha_rev_equal_1);
    tcase_add_test(wstrcmp_alpha_rev_equal, test_wstrcmp_alpha_rev_equal_2);
    tcase_add_test(wstrcmp_alpha_rev_equal, test_wstrcmp_alpha_rev_equal_on_alpha);

    TCase* wstrcmp_alpha_rev_unequal = tcase_create("wstrcmp_alpha_rev on unequal strings");
    tcase_add_test(wstrcmp_alpha_rev_unequal, test_wstrcmp_alpha_rev_not_equal_less);
    tcase_add_test(wstrcmp_alpha_rev_unequal, test_wstrcmp_alpha_rev_not_equal_less_on_alpha);
    tcase_add_test(wstrcmp_alpha_rev_unequal, test_wstrcmp_alpha_rev_not_equal_greater);
    tcase_add_test(wstrcmp_alpha_rev_unequal, test_wstrcmp_alpha_rev_not_equal_greater_on_alpha);

    TCase* wstrcmp_alpha_rev_prefix = tcase_create("wstrcmp_alpha_rev when one string is a prefix of another");
    tcase_add_test(wstrcmp_alpha_rev_prefix, test_wstrcmp_alpha_rev_prefix);
    tcase_add_test(wstrcmp_alpha_rev_prefix, test_wstrcmp_alpha_rev_prefix_on_alpha);

    TCase* wstrcmp_alpha_rev_empty = tcase_create("wstrcmp_alpha_rev when one string is empty");
    tcase_add_test(wstrcmp_alpha_rev_empty, test_wstrcmp_alpha_rev_empty);
    tcase_add_test(wstrcmp_alpha_rev_empty, test_wstrcmp_alpha_rev_empty_on_alpha);

    suite_add_tcase(s, wstrcmp_alpha_rev_equal);
    suite_add_tcase(s, wstrcmp_alpha_rev_unequal);
    suite_add_tcase(s, wstrcmp_alpha_rev_prefix);
    suite_add_tcase(s, wstrcmp_alpha_rev_empty);

    return s;
}

int main() {
    setlocale(LC_ALL, "");

    SRunner* sr = srunner_create(NULL);
    srunner_add_suite(sr, setup_wstrcnt_suite());
    srunner_add_suite(sr, setup_wstrcmp_alpha_fow_suite());
    srunner_add_suite(sr, setup_wstrcmp_alpha_rev_suite());

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    if (num_failed) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
