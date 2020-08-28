#include "is_equal.h"

#include <check.h>

#include <math.h>
#include <stdlib.h>

START_TEST(test_is_equal_nan_nan) {
    double d1 = NAN;
    double d2 = NAN;
    ck_assert_msg(!isEqual(d1, d2), "nan should not be equal to nan");
}
END_TEST

START_TEST(test_is_equal_inf_inf) {
    double d1 = INFINITY;
    double d2 = INFINITY;
    ck_assert_msg(!isEqual(d1, d2), "inf should not be equal to inf");
}
END_TEST

START_TEST(test_is_equal_inf_nan) {
    double d1 = INFINITY;
    double d2 = NAN;
    ck_assert_msg(!isEqual(d1, d2), "inf should not be equal to nan");
}
END_TEST

START_TEST(test_is_equal_d1_d2_eq_d2_d1) {
    double d1 = 1;
    double d2 = 2;
    ck_assert_msg(isEqual(d1, d2) == isEqual(d2, d1), "If (d1 == d2) than (d2 == d1)");
}
END_TEST

START_TEST(test_is_equal_equal_vals) {
    double d1 = 1;
    ck_assert_msg(isEqual(d1, d1), "Equal values should be equal");
}
END_TEST

START_TEST(test_is_equal_not_equal_vals) {
    double d1 = 1;
    double d2 = 2;
    ck_assert_msg(!isEqual(d1, d2), "Not equal values should be not equal");
}
END_TEST

START_TEST(test_is_equal_good_val_inf) {
    double d1 = 1;
    double d2 = INFINITY;
    ck_assert_msg(!isEqual(d1, d2), "Finite values should not be equal to inf");
}
END_TEST

START_TEST(test_is_equal_good_val_nan) {
    double d1 = 1;
    double d2 = NAN;
    ck_assert_msg(!isEqual(d1, d2), "Finite values should not be equal to nan");
}
END_TEST

START_TEST(test_is_equal_small_delta) {
    double d1 = 1;
    double d2 = d1 + DBL_MIN;
    ck_assert_msg(isEqual(d1, d2), "Almost equal values should be equal");
}
END_TEST

Suite* is_equal_suite() {
    Suite* s = suite_create("is_equal");

    TCase* tc_all = tcase_create("all");
    tcase_add_test(tc_all, test_is_equal_nan_nan);
    tcase_add_test(tc_all, test_is_equal_inf_nan);
    tcase_add_test(tc_all, test_is_equal_inf_inf);
    tcase_add_test(tc_all, test_is_equal_d1_d2_eq_d2_d1);
    tcase_add_test(tc_all, test_is_equal_equal_vals);
    tcase_add_test(tc_all, test_is_equal_not_equal_vals);
    tcase_add_test(tc_all, test_is_equal_small_delta);
    tcase_add_test(tc_all, test_is_equal_good_val_inf);
    tcase_add_test(tc_all, test_is_equal_good_val_nan);
    suite_add_tcase(s, tc_all);

    return s;
}

int main() {
    Suite* s = is_equal_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (num_failed) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
