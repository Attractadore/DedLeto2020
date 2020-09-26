#include "string_helper.h"

#include <check.h>

#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

START_TEST(test_wstrrev_non_pali_1) {
    wchar_t src_wstr[] = L"Hello world";
    wchar_t const exp_wstr[] = L"dlrow olleH";
    wstrrev(src_wstr);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
            "Failed to reverse string: expected \"%ls\", got \"%ls\"",
            exp_wstr, src_wstr
    );
}
END_TEST

START_TEST(test_wstrrev_non_pali_2) {
    wchar_t src_wstr[] = L"Привет мир";
    wchar_t const exp_wstr[] = L"рим тевирП";
    wstrrev(src_wstr);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
            "Failed to reverse string: expected \"%ls\", got \"%ls\"",
            exp_wstr, src_wstr
    );
}
END_TEST

START_TEST(test_wstrrev_non_pali_3) {
    wchar_t src_wstr[] = L"Hello мир";
    wchar_t const exp_wstr[] = L"рим olleH";
    wstrrev(src_wstr);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
            "Failed to reverse string: expected \"%ls\", got \"%ls\"",
            exp_wstr, src_wstr
    );

}
END_TEST

START_TEST(test_wstrrev_pali_1) {
    wchar_t src_wstr[] = L"enggne";
    wchar_t const exp_wstr[] = L"enggne";
    wstrrev(src_wstr);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
            "Failed to reverse string: expected \"%ls\", got \"%ls\"",
            exp_wstr, src_wstr
    );
}
END_TEST

START_TEST(test_wstrrev_pali_2) {
    wchar_t src_wstr[] = L"топот";
    wchar_t const exp_wstr[] = L"топот";
    wstrrev(src_wstr);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
            "Failed to reverse string: expected \"%ls\", got \"%ls\"",
            exp_wstr, src_wstr
    );
}
END_TEST

START_TEST(test_wstrrev_pali_3) {
    wchar_t src_wstr[] = L"engтопотgne";
    wchar_t const exp_wstr[] = L"engтопотgne";
    wstrrev(src_wstr);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
            "Failed to reverse string: expected \"%ls\", got \"%ls\"",
            exp_wstr, src_wstr
    );
}
END_TEST

START_TEST(test_wstrrev_empty) {
    wchar_t src_wstr[] = L"";
    wchar_t const exp_wstr[] = L"";
    wstrrev(src_wstr);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
            "Failed to reverse string: expected \"%ls\", got \"%ls\"",
            exp_wstr, src_wstr
    );
}
END_TEST

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

START_TEST(test_wstrrep_1_num) {
    wchar_t src_wstr[] = L"I am indisposed";
    wchar_t fwc = L'i';
    wchar_t twc = L' ';
    size_t exp_rep = 2;
    size_t rep = wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(rep == exp_rep,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ld, got %ld",
                  fwc, twc, exp_rep, rep);
}
END_TEST

START_TEST(test_wstrrep_1_val) {
    wchar_t src_wstr[] = L"I am indisposed";
    wchar_t const exp_wstr[] = L"I am  nd sposed";
    wchar_t fwc = L'i';
    wchar_t twc = L' ';
    wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ls, got %ls",
                  fwc, twc, exp_wstr, src_wstr);
}
END_TEST

START_TEST(test_wstrrep_2_num) {
    wchar_t src_wstr[] = L"in this string you will find many i's";
    wchar_t fwc = L'i';
    wchar_t twc = L' ';
    size_t exp_rep = 6;
    size_t rep = wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(rep == exp_rep,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ld, got %ld",
                  fwc, twc, exp_rep, rep);
}
END_TEST

START_TEST(test_wstrrep_2_val) {
    wchar_t src_wstr[] = L"in this string you will find many i's";
    wchar_t const exp_wstr[] = L" n th s str ng you w ll f nd many  's";
    wchar_t fwc = L'i';
    wchar_t twc = L' ';
    wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ls, got %ls",
                  fwc, twc, exp_wstr, src_wstr);
}
END_TEST

START_TEST(test_wstrrep_3_num) {
    wchar_t src_wstr[] = L"no letters here";
    wchar_t fwc = L'i';
    wchar_t twc = L' ';
    size_t exp_rep = 0;
    size_t rep = wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(rep == exp_rep,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ld, got %ld",
                  fwc, twc, exp_rep, rep);
}
END_TEST

START_TEST(test_wstrrep_3_val) {
    wchar_t src_wstr[] = L"no letters here";
    wchar_t const exp_wstr[] = L"no letters here";
    wchar_t fwc = L'i';
    wchar_t twc = L' ';
    wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ls, got %ls",
                  fwc, twc, exp_wstr, src_wstr);
}
END_TEST

START_TEST(test_wstrrep_4_num) {
    wchar_t src_wstr[] = L"ыы тесты ыы";
    wchar_t fwc = L'ы';
    wchar_t twc = L' ';
    size_t exp_rep = 5;
    size_t rep = wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(rep == exp_rep,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ld, got %ld",
                  fwc, twc, exp_rep, rep);
}
END_TEST

START_TEST(test_wstrrep_4_val) {
    wchar_t src_wstr[] = L"ыы тесты ыы";
    wchar_t const exp_wstr[] = L"   тест    ";
    wchar_t fwc = L'ы';
    wchar_t twc = L' ';
    wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ls, got %ls",
                  fwc, twc, exp_wstr, src_wstr);
}
END_TEST

START_TEST(test_wstrrep_empty_num) {
    wchar_t src_wstr[] = L"";
    wchar_t fwc = L'i';
    wchar_t twc = L' ';
    size_t exp_rep = 0;
    size_t rep = wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(rep == exp_rep,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ld, got %ld",
                  fwc, twc, exp_rep, rep);
}
END_TEST

START_TEST(test_wstrrep_empty_val) {
    wchar_t src_wstr[] = L"";
    wchar_t const exp_wstr[] = L"";
    wchar_t fwc = L'i';
    wchar_t twc = L' ';
    wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ls, got %ls",
                  fwc, twc, exp_wstr, src_wstr);
}
END_TEST

START_TEST(test_wstrrep_null_num) {
    wchar_t src_wstr[] = L"string with no null in it";
    wchar_t fwc = L'\0';
    wchar_t twc = L' ';
    size_t exp_rep = 0;
    size_t rep = wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(rep == exp_rep,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ld, got %ld",
                  fwc, twc, exp_rep, rep);
}
END_TEST

START_TEST(test_wstrrep_null_val) {
    wchar_t src_wstr[] = L"string with no null in it";
    wchar_t const exp_wstr[] = L"string with no null in it";
    wchar_t fwc = L'\0';
    wchar_t twc = L' ';
    wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ls, got %ls",
                  fwc, twc, exp_wstr, src_wstr);
}
END_TEST

START_TEST(test_wstrrep_same_val) {
    wchar_t src_wstr[] = L"string with different characters";
    wchar_t const exp_wstr[] = L"string with different characters";
    wchar_t fwc = L'e';
    wchar_t twc = fwc;
    wstrrep(src_wstr, fwc, twc);
    ck_assert_msg(wcscmp(src_wstr, exp_wstr) == 0,
                  "Failed to replace all occurances of '%lc' with '%lc': "
                  "expected %ls, got %ls",
                  fwc, twc, exp_wstr, src_wstr);
}
END_TEST

START_TEST(test_wstrcmp_alpha_equal_1) {
    wchar_t const str1[] = L"abc";
    wchar_t const str2[] = L"abc";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_equal_2) {
    wchar_t const str1[] = L"абв";
    wchar_t const str2[] = L"абв";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_equal_on_alpha) {
    wchar_t const str1[] = L"!@#$%^&*() abc !@#$%^&*()";
    wchar_t const str2[] = L"abc";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res,
                  "Failed to compare equal strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_not_equal_less) {
    wchar_t const str1[] = L"abc";
    wchar_t const str2[] = L"bcd";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_not_equal_less_on_alpha) {
    wchar_t const str1[] = L"!@#$%^&*() abc !@#$%^&*()";
    wchar_t const str2[] = L"bcd";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_not_equal_greater) {
    wchar_t const str1[] = L"abc";
    wchar_t const str2[] = L"bcd";
    int res = wstrcmp_alpha(str2, str1);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_not_equal_greater_on_alpha) {
    wchar_t const str1[] = L"!@#$%^&*() abc !@#$%^&*()";
    wchar_t const str2[] = L"bcd";
    int res = wstrcmp_alpha(str2, str1);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_prefix) {
    wchar_t const str1[] = L"abc";
    wchar_t const str2[] = L"abcdef";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_prefix_on_alpha) {
    wchar_t const str1[] = L"!@#$%^&*() abc !@#$%^&*()";
    wchar_t const str2[] = L"abcdef";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_empty) {
    wchar_t const str1[] = L"";
    wchar_t const str2[] = L"abc";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

START_TEST(test_wstrcmp_alpha_empty_on_alpha) {
    wchar_t const str1[] = L" !@#$%^&*() ";
    wchar_t const str2[] = L"abc";
    int res = wstrcmp_alpha(str1, str2);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res,
                  "Failed to compare strings \"%ls\" and \"%ls\": "
                  "expected comparison result to be %d, got %d",
                  str1, str2, expected_res, res);
}
END_TEST

Suite* setup_wstrrev_suite() {
    Suite* s = suite_create("wstrrev");

    TCase* wstrrev_non_pali = tcase_create("wstrrev on non-palindromes");
    tcase_add_test(wstrrev_non_pali, test_wstrrev_non_pali_1);
    tcase_add_test(wstrrev_non_pali, test_wstrrev_non_pali_2);
    tcase_add_test(wstrrev_non_pali, test_wstrrev_non_pali_3);

    TCase* wstrrev_pali = tcase_create("wstrrev on palindromes");
    tcase_add_test(wstrrev_pali, test_wstrrev_pali_1);
    tcase_add_test(wstrrev_pali, test_wstrrev_pali_2);
    tcase_add_test(wstrrev_pali, test_wstrrev_pali_3);

    TCase* wstrrev_empty = tcase_create("wstrrev on empty string");
    tcase_add_test(wstrrev_empty, test_wstrrev_empty);

    suite_add_tcase(s, wstrrev_non_pali);
    suite_add_tcase(s, wstrrev_pali);
    suite_add_tcase(s, wstrrev_empty);

    return s;
}

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

Suite* setup_wstrrep_suite() {
    Suite* s = suite_create("wstrrep");

    TCase* wstrrep_base = tcase_create("basic usage of wstrrep");
    tcase_add_test(wstrrep_base, test_wstrrep_1_num);
    tcase_add_test(wstrrep_base, test_wstrrep_1_val);
    tcase_add_test(wstrrep_base, test_wstrrep_2_num);
    tcase_add_test(wstrrep_base, test_wstrrep_2_val);
    tcase_add_test(wstrrep_base, test_wstrrep_3_num);
    tcase_add_test(wstrrep_base, test_wstrrep_3_val);
    tcase_add_test(wstrrep_base, test_wstrrep_4_num);
    tcase_add_test(wstrrep_base, test_wstrrep_4_val);

    TCase* wstrrep_empty = tcase_create("wstrrep on empty string");
    tcase_add_test(wstrrep_empty, test_wstrrep_empty_num);
    tcase_add_test(wstrrep_empty, test_wstrrep_empty_val);

    TCase* wstrrep_null = tcase_create("wstrrep on null character");
    tcase_add_test(wstrrep_null, test_wstrrep_null_num);
    tcase_add_test(wstrrep_null, test_wstrrep_null_val);

    TCase* wstrrep_same = tcase_create("wstrrep with same character");
    tcase_add_test(wstrrep_same, test_wstrrep_same_val);

    suite_add_tcase(s, wstrrep_base);
    suite_add_tcase(s, wstrrep_empty);
    suite_add_tcase(s, wstrrep_null);
    suite_add_tcase(s, wstrrep_same);

    return s;
}

Suite* setup_wstrcmp_alpha_suite() {
    Suite* s = suite_create("wstrcmp_alpha");

    TCase* wstrcmp_alpha_equal = tcase_create("wstrcmp_alpha on equal strings");
    tcase_add_test(wstrcmp_alpha_equal, test_wstrcmp_alpha_equal_1);
    tcase_add_test(wstrcmp_alpha_equal, test_wstrcmp_alpha_equal_2);
    tcase_add_test(wstrcmp_alpha_equal, test_wstrcmp_alpha_equal_on_alpha);

    TCase* wstrcmp_alpha_unequal = tcase_create("wstrcmp_alpha on unequal strings");
    tcase_add_test(wstrcmp_alpha_unequal, test_wstrcmp_alpha_not_equal_less);
    tcase_add_test(wstrcmp_alpha_unequal, test_wstrcmp_alpha_not_equal_less_on_alpha);
    tcase_add_test(wstrcmp_alpha_unequal, test_wstrcmp_alpha_not_equal_greater);
    tcase_add_test(wstrcmp_alpha_unequal, test_wstrcmp_alpha_not_equal_greater_on_alpha);

    TCase* wstrcmp_alpha_prefix = tcase_create("wstrcmp_alpha when one string is a prefix of another");
    tcase_add_test(wstrcmp_alpha_prefix, test_wstrcmp_alpha_prefix);
    tcase_add_test(wstrcmp_alpha_prefix, test_wstrcmp_alpha_prefix_on_alpha);

    TCase* wstrcmp_alpha_empty = tcase_create("wstrcmp_alpha when one string is empty");
    tcase_add_test(wstrcmp_alpha_empty, test_wstrcmp_alpha_empty);
    tcase_add_test(wstrcmp_alpha_empty, test_wstrcmp_alpha_empty_on_alpha);

    suite_add_tcase(s, wstrcmp_alpha_equal);
    suite_add_tcase(s, wstrcmp_alpha_unequal);
    suite_add_tcase(s, wstrcmp_alpha_prefix);
    suite_add_tcase(s, wstrcmp_alpha_empty);

    return s;
}

int main() {
    setlocale(LC_ALL, "");

    SRunner* sr = srunner_create(NULL);
    srunner_add_suite(sr, setup_wstrrev_suite());
    srunner_add_suite(sr, setup_wstrcnt_suite());
    srunner_add_suite(sr, setup_wstrrep_suite());
    srunner_add_suite(sr, setup_wstrcmp_alpha_suite());

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    if (num_failed) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
