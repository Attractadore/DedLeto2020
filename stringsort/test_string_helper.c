#include "string_helper.h"

#include <check.h>

#include <stdlib.h>

START_TEST(test_strrev_ascii_string_return) {
    char str[] = "hello world";
    int ret = strrev(str);
    ck_assert_msg(ret == STR_REV_SUCCESS, "Failed to reverse string: expected returned value to be %d, got %d", STR_REV_SUCCESS, ret);
}
END_TEST

START_TEST(test_strrev_ascii_string_value) {
    char str[] = "hello world";
    char const comp_str[] = "dlrow olleh";
    strrev(str);
    ck_assert_msg(strcmp(str, comp_str) == 0, "Failed to reverse string: expected string to be \"%s\", but it is \"%s\"", comp_str, str);
}
END_TEST

START_TEST(test_strrev_utf_8_string_return) {
    char str[] = "привет мир";
    int ret = strrev(str);
    ck_assert_msg(ret == STR_REV_SUCCESS, "Failed to reverse string: expected returned value to be %d, got %d", STR_REV_SUCCESS, ret);
}
END_TEST

START_TEST(test_strrev_utf_8_string_value) {
    char str[] = "привет мир";
    char const comp_str[] = "рим тевирп";
    strrev(str);
    ck_assert_msg(strcmp(str, comp_str) == 0, "Failed to reverse string: expected string to be \"%s\", but it is \"%s\"", comp_str, str);
}
END_TEST

START_TEST(test_strrev_broken_utf_8_string_return_1) {
    char str[] = "hello \x80world";
    int ret = strrev(str);
    ck_assert_msg(ret == STR_REV_ERROR, "Expected failure to reverse broken UTF-8 string: expected %d, got %d", STR_REV_ERROR, ret);
}
END_TEST

START_TEST(test_strrev_broken_utf_8_string_return_2) {
    char str[] = "hello world\xC0";
    int ret = strrev(str);
    ck_assert_msg(ret == STR_REV_ERROR, "Expected failure to reverse broken UTF-8 string: expected %d, got %d", STR_REV_ERROR, ret);
}
END_TEST

START_TEST(test_strrev_broken_utf_8_string_return_3) {
    char str[] = "привет \x80мир";
    int ret = strrev(str);
    ck_assert_msg(ret == STR_REV_ERROR, "Expected failure to reverse broken UTF-8 string: expected %d, got %d", STR_REV_ERROR, ret);
}
END_TEST

START_TEST(test_strrev_broken_utf_8_string_return_4) {
    char str[] = "привет мир\xC0";
    int ret = strrev(str);
    ck_assert_msg(ret == STR_REV_ERROR, "Expected failure to reverse broken UTF-8 string: expected %d, got %d", STR_REV_ERROR, ret);
}
END_TEST

START_TEST(test_strncnt_ascii_single_char) {
    char const str[] = "This string has a lot of i's in it";
    char const cnt_str[] = "i";
    size_t cnt = strncnt(str, strlen(str), cnt_str, strlen(cnt_str));
    size_t const expected_cnt = 5;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in string \"%s\": expected %ld, got %ld", cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_ascii_substring) {
    char const str[] = "Asd Asd Asd asd ASD asd asdasd";
    char const cnt_str[] = " asd";
    size_t cnt = strncnt(str, strlen(str), cnt_str, strlen(cnt_str));
    size_t expected_cnt = 3;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in string \"%s\": expected %ld, got %ld", cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_utf_8_single_symbol) {
    char const str[] = "В этый стрыке очень многы букыв ы";
    char const cnt_str[] = "ы";
    size_t cnt = strncnt(str, strlen(str), cnt_str, strlen(cnt_str));
    size_t expected_cnt = 5;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in string \"%s\": expected %ld, got %ld", cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_utf_8_substring) {
    char const str[] = "Фыв Фыв Фыв фыв ФЫВ фыв фывфыв";
    char const cnt_str[] = " фыв";
    size_t cnt = strncnt(str, strlen(str), cnt_str, strlen(cnt_str));
    size_t expected_cnt = 3;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in string \"%s\": expected %ld, got %ld", cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_ascii_overlap) {
    char const str[] = "iii iiii";
    char const cnt_str[] = "ii";
    size_t cnt = strncnt(str, strlen(str), cnt_str, strlen(cnt_str));
    size_t expected_cnt = 3;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in string \"%s\": expected %ld, got %ld", cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_utf_8_overlap) {
    char const str[] = "ыыы ыыыы";
    char const cnt_str[] = "ыы";
    size_t cnt = strncnt(str, strlen(str), cnt_str, strlen(cnt_str));
    size_t expected_cnt = 3;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in string \"%s\": expected %ld, got %ld", cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_part_of_str_less) {
    char const str[] = "iii iiii";
    char const cnt_str[] = "i";
    size_t str_num = 5;
    size_t cnt = strncnt(str, str_num, cnt_str, strlen(cnt_str));
    size_t expected_cnt = 4;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in at most %ld chars of string \"%s\": expected %ld, got %ld", cnt_str, str_num, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_part_of_str_more) {
    char const str[] = "iii iiii";
    char const cnt_str[] = "i";
    size_t str_num = strlen(str) + 1;
    size_t cnt = strncnt(str, str_num, cnt_str, strlen(cnt_str));
    size_t expected_cnt = 7;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in at most %ld chars of string \"%s\": expected %ld, got %ld", cnt_str, str_num, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_part_of_cnt_less) {
    char const str[] = "123 1234 1243";
    char const cnt_str[] = "123";
    size_t cnt_num = 2;
    size_t cnt = strncnt(str, strlen(str), cnt_str, cnt_num);
    size_t expected_cnt = 3;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of occurances of substring of at most %ld chars \"%s\" in string \"%s\": expected %ld, got %ld", cnt_num, cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_part_of_cnt_more) {
    char const str[] = "123 1234 1243";
    char const cnt_str[] = "123";
    size_t cnt_num = strlen(cnt_str) + 1;
    size_t cnt = strncnt(str, strlen(str), cnt_str, cnt_num);
    size_t expected_cnt = 2;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of occurances of substring of at most %ld chars \"%s\" in string \"%s\": expected %ld, got %ld", cnt_num, cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_empty_str) {
    char const str[] = "";
    char const cnt_str[] = "123";
    size_t cnt = strncnt(str, strlen(str), cnt_str, strlen(cnt_str));
    size_t expected_cnt = 0;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in string \"%s\": expected %ld, got %ld", cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strncnt_empty_cnt) {
    char const str[] = "123";
    char const cnt_str[] = "";
    size_t cnt = strncnt(str, strlen(str), cnt_str, strlen(cnt_str));
    size_t expected_cnt = 0;
    ck_assert_msg(cnt == expected_cnt, "Failed to count number of substring \"%s\" occurances in string \"%s\": expected %ld, got %ld", cnt_str, str, expected_cnt, cnt);
}
END_TEST

START_TEST(test_strnrep_res_smaller_len) {
    char str[] = "replace this in this string with dis";
    char const res_str[] = "replace dis in dis string with dis";
    char const rep_from[] = "this";
    char const rep_to[] = "dis";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_res_smaller_value) {
    char str[] = "replace this in this string with dis";
    char const res_str[] = "replace dis in dis string with dis";
    char const rep_from[] = "this";
    char const rep_to[] = "dis";
    strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_res_equal_len) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "2";
    char const rep_to[] = "1";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_res_equal_value) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "2";
    char const rep_to[] = "1";
    strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_res_greater_len) {
    char str[] = "12 12 ";
    char const res_str[] = "321 12";
    char const rep_from[] = "12";
    char const rep_to[] = "321";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_res_greater_value) {
    char str[] = "12 12 ";
    char const res_str[] = "321 32";
    char const rep_from[] = "12";
    char const rep_to[] = "321";
    strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_from_empty_len) {
    char str[] = "12 12 ";
    char const res_str[] = "12 12 ";
    char const rep_from[] = "";
    char const rep_to[] = "321";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_from_empty_value) {
    char str[] = "12 12 ";
    char const res_str[] = "12 12 ";
    char const rep_from[] = "";
    char const rep_to[] = "321";
    strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_to_empty_len) {
    char str[] = "12 12 ";
    char const res_str[] = "  ";
    char const rep_from[] = "12";
    char const rep_to[] = "";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_to_empty_value) {
    char str[] = "12 12 ";
    char const res_str[] = "  ";
    char const rep_from[] = "12";
    char const rep_to[] = "";
    strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_empty_len) {
    char str[] = "";
    char const res_str[] = "";
    char const rep_from[] = "12";
    char const rep_to[] = "32";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_empty_value) {
    char str[] = "";
    char const res_str[] = "";
    char const rep_from[] = "12";
    char const rep_to[] = "32";
    strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_rep_from_len_not_eq_rep_from_length_less_len) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "1234";
    size_t rep_from_len = 2;
    char const rep_to[] = "11";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, rep_from_len, rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_rep_from_len_not_eq_rep_from_length_less_value) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "1234";
    size_t rep_from_len = 2;
    char const rep_to[] = "11";
    strnrep(str, strlen(str), rep_from, rep_from_len, rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_rep_from_len_not_eq_rep_from_length_greater_len) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "12";
    size_t rep_from_len = strlen(rep_from) + 1;
    char const rep_to[] = "11";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, rep_from_len, rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_rep_from_len_not_eq_rep_from_length_greater_value) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "12";
    size_t rep_from_len = strlen(rep_from) + 1;
    char const rep_to[] = "11";
    strnrep(str, strlen(str), rep_from, rep_from_len, rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_rep_to_len_not_eq_rep_to_length_less_len) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "12";
    char const rep_to[] = "112";
    size_t rep_to_len = 2;
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, rep_to_len);
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_rep_to_len_not_eq_rep_to_length_less_value) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "12";
    char const rep_to[] = "112";
    size_t rep_to_len = 2;
    strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, rep_to_len);
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_rep_to_len_not_eq_rep_to_length_greater_len) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "12";
    char const rep_to[] = "11";
    size_t rep_to_len = strlen(rep_to) + 1;
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, rep_to_len);
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_rep_to_len_not_eq_rep_to_length_greater_value) {
    char str[] = "121212";
    char const res_str[] = "111111";
    char const rep_from[] = "12";
    char const rep_to[] = "11";
    size_t rep_to_len = strlen(rep_to) + 1;
    strnrep(str, strlen(str), rep_from, strlen(rep_from), rep_to, rep_to_len);
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_num_not_eq_str_length_less_len) {
    char str[] = "121212";
    size_t num = 4;
    char const rep_from[] = "12";
    char const rep_to[] = "11";
    size_t expected_len = num;
    size_t res_len = strnrep(str, num, rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_num_not_eq_str_length_less_value) {
    char str[] = "121212";
    size_t num = 4;
    char const res_str[] = "111112";
    char const rep_from[] = "12";
    char const rep_to[] = "11";
    strnrep(str, num, rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_strnrep_num_not_eq_str_length_greater_len) {
    char str[] = "121212";
    size_t num = strlen(str) + 1;
    char const res_str[] = "111111";
    char const rep_from[] = "12";
    char const rep_to[] = "11";
    size_t expected_len = strlen(res_str);
    size_t res_len = strnrep(str, num, rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(res_len == expected_len, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected new length to be %ld, got %ld", rep_from, rep_to, expected_len, res_len);
}

START_TEST(test_strnrep_num_not_eq_str_length_greater_value) {
    char str[] = "121212";
    size_t num = strlen(str) + 1;
    char const res_str[] = "111111";
    char const rep_from[] = "12";
    char const rep_to[] = "11";
    strnrep(str, num, rep_from, strlen(rep_from), rep_to, strlen(rep_to));
    ck_assert_msg(strcmp(str, res_str) == 0, "Failed to replace all occurances of substring \"%s\" with substring \"%s\" in string: expected \"%s\", got \"%s\"", rep_from, rep_to, res_str, str);
}

START_TEST(test_find_alnum_ascii) {
    char const str[] = "....asfa jashgvjajk     ?";
    char const* p = find_alnum(str);
    ptrdiff_t expected_diff = 4;
    ptrdiff_t diff = p - str;
    ck_assert_msg(diff == expected_diff, "Failed to find alnum char in string \"%s\": expected ptr diff to be %ld, got %ld", str, expected_diff, diff);
}
END_TEST

START_TEST(test_find_alnum_num_only) {
    char const str[] = "...?123";
    char const* p = find_alnum(str);
    ptrdiff_t expected_diff = 4;
    ptrdiff_t diff = p - str;
    ck_assert_msg(diff == expected_diff, "Failed to find alnum char in string \"%s\": expected ptr diff to be %ld, got %ld", str, expected_diff, diff);
}
END_TEST

START_TEST(test_find_alnum_utf_8) {
    char const str[] = "....ыфыфыа jkhjkhjk     ?";
    char const* p = find_alnum(str);
    ptrdiff_t expected_diff = 4;
    ptrdiff_t diff = p - str;
    ck_assert_msg(diff == expected_diff, "Failed to find alnum char in string \"%s\": expected ptr diff to be %ld, got %ld", str, expected_diff, diff);
}
END_TEST

START_TEST(test_find_alnum_no_alnum_in_str) {
    char const str[] = "    ? ! *    ";
    char const* p = find_alnum(str);
    ptrdiff_t expected_diff = strlen(str);
    ptrdiff_t diff = p - str;
    ck_assert_msg(diff == expected_diff, "Failed to find alnum char in string \"%s\": expected ptr diff to be %ld, got %ld", str, expected_diff, diff);
}
END_TEST

START_TEST(test_find_alnum_empty_str) {
    char const str[] = "";
    char const* p = find_alnum(str);
    ptrdiff_t expected_diff = strlen(str);
    ptrdiff_t diff = p - str;
    ck_assert_msg(diff == expected_diff, "Failed to find alnum char in string \"%s\": expected ptr diff to be %ld, got %ld", str, expected_diff, diff);
}
END_TEST

START_TEST(test_strcmp_alnum_equal) {
    char const str1[] = "123";
    char const str2[] = "123";
    int res = strcmp_alnum(str1, str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res, "Failed to compare equal strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_equal_punct) {
    char const str1[] = "123";
    char const str2[] = "  '.&*(^(*; 123 =-=!@#$%^&*(";
    int res = strcmp_alnum(str1, str2);
    int expected_res = 0;
    ck_assert_msg(res == expected_res, "Failed to compare equal strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_not_equal_less) {
    char const str1[] = "123";
    char const str2[] = "234";
    int res = strcmp_alnum(str1, str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res, "Failed to compare strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_not_equal_less_punct) {
    char const str1[] = "*&**(*&(* 123 *&*&(*  ";
    char const str2[] = "\t *(*(&(* 234 %#^#^";
    int res = strcmp_alnum(str1, str2);
    int expected_res = -1;
    ck_assert_msg(res <= expected_res, "Failed to compare strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_not_equal_greater) {
    char const str1[] = "123";
    char const str2[] = "234";
    int res = strcmp_alnum(str2, str1);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res, "Failed to compare strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_not_equal_greater_punct) {
    char const str1[] = "!@#$$^&**(())_+ 123 $%&(*%$";
    char const str2[] = "    234  ";
    int res = strcmp_alnum(str2, str1);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res, "Failed to compare strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_prefix) {
    char const str1[] = "123";
    char const str2[] = "123456";
    int res = strcmp_alnum(str1, str2);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res, "Failed to compare strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_prefix_punct) {
    char const str1[] = " &^&*^*& 123  ";
    char const str2[] = "   123456   ";
    int res = strcmp_alnum(str1, str2);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res, "Failed to compare strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_empty) {
    char const str1[] = "";
    char const str2[] = "123";
    int res = strcmp_alnum(str1, str2);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res, "Failed to compare strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

START_TEST(test_strcmp_alnum_empty_punct) {
    char const str1[] = "&*()^^&*(^";
    char const str2[] = "123";
    int res = strcmp_alnum(str1, str2);
    int expected_res = 1;
    ck_assert_msg(res >= expected_res, "Failed to compare strings \"%s\" and \"%s\": expected comparison result to be %d, got %d", str1, str2, expected_res, res);
}

Suite* setup_strrev_suite() {
    Suite* s = suite_create("strrev");

    TCase* strrev_valid_ascii_string = tcase_create("strrev on ascii string");
    tcase_add_test(strrev_valid_ascii_string, test_strrev_ascii_string_return);
    tcase_add_test(strrev_valid_ascii_string, test_strrev_ascii_string_value);

    TCase* strrev_valid_utf_8_string = tcase_create("strrev on UTF-8 string");
    tcase_add_test(strrev_valid_utf_8_string, test_strrev_utf_8_string_return);
    tcase_add_test(strrev_valid_utf_8_string, test_strrev_utf_8_string_value);

    TCase* strrev_broken_utf_8_string = tcase_create("strrev on broken UTF-8 string");
    tcase_add_test(strrev_broken_utf_8_string, test_strrev_broken_utf_8_string_return_1);
    tcase_add_test(strrev_broken_utf_8_string, test_strrev_broken_utf_8_string_return_2);
    tcase_add_test(strrev_broken_utf_8_string, test_strrev_broken_utf_8_string_return_3);
    tcase_add_test(strrev_broken_utf_8_string, test_strrev_broken_utf_8_string_return_4);

    suite_add_tcase(s, strrev_valid_ascii_string);
    suite_add_tcase(s, strrev_valid_utf_8_string);
    suite_add_tcase(s, strrev_broken_utf_8_string);

    return s;
}

Suite* setup_strncnt_suite() {
    Suite* s = suite_create("strncnt");

    TCase* strncnt_ascii_single_char = tcase_create("strncnt with single ascii char");
    tcase_add_test(strncnt_ascii_single_char, test_strncnt_ascii_single_char);

    TCase* strncnt_ascii_substring = tcase_create("strnct with ascii substring");
    tcase_add_test(strncnt_ascii_substring, test_strncnt_ascii_substring);

    TCase* strncnt_utf_8_single_char = tcase_create("strncnt with single UTF-8 symbol");
    tcase_add_test(strncnt_utf_8_single_char, test_strncnt_utf_8_single_symbol);

    TCase* strncnt_utf_8_substring = tcase_create("strnct with UTF-8 substring");
    tcase_add_test(strncnt_utf_8_substring, test_strncnt_utf_8_substring);

    TCase* strncnt_ascii_overlap = tcase_create("strnct with ascii substring on strinf with overlaps");
    tcase_add_test(strncnt_ascii_overlap, test_strncnt_ascii_overlap);

    TCase* strncnt_utf_8_overlap = tcase_create("strnct with UTF-8 substring on strinf with overlaps");
    tcase_add_test(strncnt_utf_8_overlap, test_strncnt_utf_8_overlap);

    TCase* strncnt_num_not_eq_str_length = tcase_create("strncnt with num != strlen(str)");
    tcase_add_test(strncnt_num_not_eq_str_length, test_strncnt_part_of_str_less);
    tcase_add_test(strncnt_num_not_eq_str_length, test_strncnt_part_of_str_more);

    TCase* strncnt_cnt_len_not_eq_cnt_length = tcase_create("strncnt with cnt_len != strlen(cnt)");
    tcase_add_test(strncnt_cnt_len_not_eq_cnt_length, test_strncnt_part_of_cnt_less);
    tcase_add_test(strncnt_cnt_len_not_eq_cnt_length, test_strncnt_part_of_cnt_more);

    TCase* strncnt_empty_str = tcase_create("strncnt with empty str");
    tcase_add_test(strncnt_empty_str, test_strncnt_empty_str);

    TCase* strncnt_empty_cnt = tcase_create("strncnt with empty cnt");
    tcase_add_test(strncnt_empty_cnt, test_strncnt_empty_cnt);

    suite_add_tcase(s, strncnt_ascii_single_char);
    suite_add_tcase(s, strncnt_ascii_substring);
    suite_add_tcase(s, strncnt_utf_8_single_char);
    suite_add_tcase(s, strncnt_utf_8_substring);
    suite_add_tcase(s, strncnt_ascii_overlap);
    suite_add_tcase(s, strncnt_utf_8_overlap);
    suite_add_tcase(s, strncnt_num_not_eq_str_length);
    suite_add_tcase(s, strncnt_cnt_len_not_eq_cnt_length);
    suite_add_tcase(s, strncnt_empty_str);
    suite_add_tcase(s, strncnt_empty_cnt);

    return s;
}

Suite* setup_strnrep_suite() {
    Suite* s = suite_create("strnrep");

    TCase* strnrep_res_smaller = tcase_create("strnrep with res string smaller than src string");
    tcase_add_test(strnrep_res_smaller, test_strnrep_res_smaller_len);
    tcase_add_test(strnrep_res_smaller, test_strnrep_res_smaller_value);

    TCase* strnrep_res_equal = tcase_create("strnrep with res string same length as src string");
    tcase_add_test(strnrep_res_equal, test_strnrep_res_equal_len);
    tcase_add_test(strnrep_res_equal, test_strnrep_res_equal_value);

    TCase* strnrep_res_greater = tcase_create("strnrep with res string longer than src string");
    tcase_add_test(strnrep_res_greater, test_strnrep_res_greater_len);
    tcase_add_test(strnrep_res_greater, test_strnrep_res_greater_value);

    TCase* strnrep_replace_from_empty = tcase_create("strnrep with from string empty");
    tcase_add_test(strnrep_replace_from_empty, test_strnrep_from_empty_len);
    tcase_add_test(strnrep_replace_from_empty, test_strnrep_from_empty_value);

    TCase* strnrep_replace_to_empty = tcase_create("strnrep with to string empty");
    tcase_add_test(strnrep_replace_to_empty, test_strnrep_to_empty_len);
    tcase_add_test(strnrep_replace_to_empty, test_strnrep_to_empty_value);

    TCase* strnrep_replace_empty = tcase_create("strnrep with src string empty");
    tcase_add_test(strnrep_replace_empty, test_strnrep_empty_len);
    tcase_add_test(strnrep_replace_empty, test_strnrep_empty_value);

    TCase* strnrep_rep_from_len_not_eq_rep_from_length = tcase_create("strnrep with rep_from_len != strlen(rep_from)");
    tcase_add_test(strnrep_rep_from_len_not_eq_rep_from_length, test_strnrep_rep_from_len_not_eq_rep_from_length_less_len);
    tcase_add_test(strnrep_rep_from_len_not_eq_rep_from_length, test_strnrep_rep_from_len_not_eq_rep_from_length_less_value);
    tcase_add_test(strnrep_rep_from_len_not_eq_rep_from_length, test_strnrep_rep_from_len_not_eq_rep_from_length_greater_len);
    tcase_add_test(strnrep_rep_from_len_not_eq_rep_from_length, test_strnrep_rep_from_len_not_eq_rep_from_length_greater_value);

    TCase* strnrep_rep_to_len_not_eq_rep_to_length = tcase_create("strnrep with rep_to_len != strlen(rep_to)");
    tcase_add_test(strnrep_rep_to_len_not_eq_rep_to_length, test_strnrep_rep_to_len_not_eq_rep_to_length_less_len);
    tcase_add_test(strnrep_rep_to_len_not_eq_rep_to_length, test_strnrep_rep_to_len_not_eq_rep_to_length_less_value);
    tcase_add_test(strnrep_rep_to_len_not_eq_rep_to_length, test_strnrep_rep_to_len_not_eq_rep_to_length_greater_len);
    tcase_add_test(strnrep_rep_to_len_not_eq_rep_to_length, test_strnrep_rep_to_len_not_eq_rep_to_length_greater_value);

    TCase* strnrep_num_not_eq_str_length = tcase_create("strnrep with num != strlen(str)");
    tcase_add_test(strnrep_num_not_eq_str_length, test_strnrep_num_not_eq_str_length_less_len);
    tcase_add_test(strnrep_num_not_eq_str_length, test_strnrep_num_not_eq_str_length_less_value);
    tcase_add_test(strnrep_num_not_eq_str_length, test_strnrep_num_not_eq_str_length_greater_len);
    tcase_add_test(strnrep_num_not_eq_str_length, test_strnrep_num_not_eq_str_length_greater_value);

    suite_add_tcase(s, strnrep_res_smaller);
    suite_add_tcase(s, strnrep_res_equal);
    suite_add_tcase(s, strnrep_res_greater);
    suite_add_tcase(s, strnrep_replace_from_empty);
    suite_add_tcase(s, strnrep_replace_to_empty);
    suite_add_tcase(s, strnrep_replace_empty);
    suite_add_tcase(s, strnrep_rep_from_len_not_eq_rep_from_length);
    suite_add_tcase(s, strnrep_rep_to_len_not_eq_rep_to_length);
    suite_add_tcase(s, strnrep_num_not_eq_str_length);

    return s;
}

Suite* setup_find_alnum_suite() {
    Suite* s = suite_create("find_alnum");

    TCase* find_alnum_ascii = tcase_create("find_alnum on ascii string");
    tcase_add_test(find_alnum_ascii, test_find_alnum_ascii);

    TCase* find_alnum_num_only = tcase_create("find_alnum on string with numbers only");
    tcase_add_test(find_alnum_num_only, test_find_alnum_num_only);

    TCase* find_alnum_utf_8 = tcase_create("find_alnum on UTF-8 string");
    tcase_add_test(find_alnum_utf_8, test_find_alnum_utf_8);

    TCase* find_alnum_no_alnum = tcase_create("find_alnum on string without alnum chars");
    tcase_add_test(find_alnum_no_alnum, test_find_alnum_no_alnum_in_str);

    TCase* find_alnum_empty = tcase_create("find_alnum on empty string");
    tcase_add_test(find_alnum_empty, test_find_alnum_empty_str);

    suite_add_tcase(s, find_alnum_ascii);
    suite_add_tcase(s, find_alnum_num_only);
    suite_add_tcase(s, find_alnum_utf_8);
    suite_add_tcase(s, find_alnum_no_alnum);
    suite_add_tcase(s, find_alnum_empty);

    return s;
}

Suite* setup_strcmp_alnum_suite() {
    Suite* s = suite_create("strcmp_alnum");

    TCase* strcmp_alnum_equal = tcase_create("strcmp_alnum on equal strings");
    tcase_add_test(strcmp_alnum_equal, test_strcmp_alnum_equal);
    tcase_add_test(strcmp_alnum_equal, test_strcmp_alnum_equal_punct);

    TCase* strcmp_alnum_unequal = tcase_create("strcmp_alnum on unequal strings");
    tcase_add_test(strcmp_alnum_unequal, test_strcmp_alnum_not_equal_less);
    tcase_add_test(strcmp_alnum_unequal, test_strcmp_alnum_not_equal_less_punct);
    tcase_add_test(strcmp_alnum_unequal, test_strcmp_alnum_not_equal_greater);
    tcase_add_test(strcmp_alnum_unequal, test_strcmp_alnum_not_equal_greater_punct);

    TCase* strcmp_alnum_prefix = tcase_create("strcmp_alnum when one string is a prefix of another");
    tcase_add_test(strcmp_alnum_prefix, test_strcmp_alnum_prefix);
    tcase_add_test(strcmp_alnum_prefix, test_strcmp_alnum_prefix_punct);

    TCase* strcmp_alnum_empty = tcase_create("strcmp_alnum when one string is empty");
    tcase_add_test(strcmp_alnum_empty, test_strcmp_alnum_empty);
    tcase_add_test(strcmp_alnum_empty, test_strcmp_alnum_empty_punct);

    suite_add_tcase(s, strcmp_alnum_equal);
    suite_add_tcase(s, strcmp_alnum_unequal);
    suite_add_tcase(s, strcmp_alnum_prefix);
    suite_add_tcase(s, strcmp_alnum_empty);

    return s;
}

int main() {
    SRunner* sr = srunner_create(NULL);
    srunner_add_suite(sr, setup_strrev_suite());
    srunner_add_suite(sr, setup_strncnt_suite());
    srunner_add_suite(sr, setup_strnrep_suite());
    srunner_add_suite(sr, setup_find_alnum_suite());
    srunner_add_suite(sr, setup_strcmp_alnum_suite());

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    if (num_failed) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
