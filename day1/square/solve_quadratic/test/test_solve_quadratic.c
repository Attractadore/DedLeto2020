#include "is_equal.h"
#include "solve_quadratic.h"

#include <check.h>

#include <float.h>
#include <stdlib.h>

#define setup(av, bv, cv)                              \
    double a = av, b = bv, c = cv, x1 = NAN, x2 = NAN; \
    int num_sol = solveQuadratic(a, b, c, &x1, &x2);

START_TEST(test_solve_quadratic_a_nan) {
    setup(NAN, 1, 1);
    ck_assert_msg(num_sol == EQ_ERROR_SOLUTIONS, "If a is nan, an EQ_ERROR_SOLUTIONS should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_inf) {
    setup(INFINITY, 1, 1)
        ck_assert_msg(num_sol == EQ_ERROR_SOLUTIONS, "If a is inf, an EQ_ERROR_SOLUTIONS should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_b_nan) {
    setup(1, NAN, 1);
    ck_assert_msg(num_sol == EQ_ERROR_SOLUTIONS, "If b is nan, an EQ_ERROR_SOLUTIONS should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_b_inf) {
    setup(1, INFINITY, 1)
        ck_assert_msg(num_sol == EQ_ERROR_SOLUTIONS, "If b is inf, an EQ_ERROR_SOLUTIONS should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_c_nan) {
    setup(1, 1, NAN);
    ck_assert_msg(num_sol == EQ_ERROR_SOLUTIONS, "If c is nan, an EQ_ERROR_SOLUTIONS should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_c_inf) {
    setup(1, 1, INFINITY)
        ck_assert_msg(num_sol == EQ_ERROR_SOLUTIONS, "If c is inf, an EQ_ERROR_SOLUTIONS should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_zero_b_zero_c_zero) {
    setup(0, 0, 0);
    ck_assert_msg(num_sol == EQ_INFINITE_SOLUTIONS, "If a = b = c = 0, EQ_INFINITE_SOLUTIONS should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_zero_b_zero_c_nonzero) {
    setup(0, 0, 1);
    ck_assert_msg(num_sol == 0, "If a = b = 0, c != 0, 0 should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_zero_b_nonzero_num_sol) {
    setup(0, 1, 5);
    ck_assert_msg(num_sol == 1, "If a = 0, b != 0, 1 should be returned, got %d", num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_zero_b_nonzero_sol_value_1) {
    setup(0, 1, 5);
    ck_assert_msg(isEqual(x1, -5), "If a = %g, b = %g, c = %g, x1 should be -5, got x1 = %g", a, b, c, x1);
}
END_TEST

START_TEST(test_solve_quadratic_a_zero_b_nonzero_sol_value_2) {
    setup(0, 1, 5);
    ck_assert_msg(isEqual(x2, -5), "If a = %g, b = %g, c = %g, x2 should be -5, got x2 = %g", a, b, c, x2);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_zero_no_sol) {
    setup(1, 0, 5);
    ck_assert_msg(num_sol == 0, "If a = %g, b = %g, c = %g, 0 should be returned, got %d", a, b, c, num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_zero_one_sol_num_sol) {
    setup(1, 0, 0);
    ck_assert_msg(num_sol == 1, "If a = %g, b = %g, c = %g, 1 should be returned, got %d", a, b, c, num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_zero_one_sol_num_sol_value_1) {
    setup(1, 0, 0);
    ck_assert_msg(isEqual(x1, 0), "If a = %g, b = %g, c = %g, x1 == 0, got x1 = %g", a, b, c, x1);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_zero_one_sol_num_sol_value_2) {
    setup(1, 0, 0);
    ck_assert_msg(isEqual(x2, 0), "If a = %g, b = %g, c = %g, x2 == 0, got x2 = %g", a, b, c, x2);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_zero_two_sol_num_sol) {
    setup(1, 0, -4);
    ck_assert_msg(num_sol == 2, "If a = %g, b = %g, c = %g, 2 should be returned, got %d", a, b, c, num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_zero_two_sol_num_sol_value_1) {
    setup(1, 0, -4);
    ck_assert_msg(isEqual(x1, -2), "If a = %g, b = %g, c = %g, x1 == -2, got x1 = %g", a, b, c, x1);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_zero_two_sol_num_sol_value_2) {
    setup(1, 0, -4);
    ck_assert_msg(isEqual(x2, 2), "If a = %g, b = %g, c = %g, x2 == 2, got x2 = %g", a, b, c, x2);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_nonzero_c_zero_num_sol) {
    setup(1, 1, 0);
    ck_assert_msg(num_sol == 2, "If a = %g, b = %g, c = %g, 2 should be returned, got %d", a, b, c, num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_nonzero_c_zero_sol_value_1) {
    setup(1, 1, 0);
    ck_assert_msg(isEqual(x1, -1), "If a = %g, b = %g, c = %g, x1 == -1, got x1 = %g", a, b, c, x1);
}
END_TEST

START_TEST(test_solve_quadratic_a_nonzero_b_nonzero_c_zero_sol_value_2) {
    setup(1, 1, 0);
    ck_assert_msg(isEqual(x2, 0), "If a = %g, b = %g, c = %g, x2 == 0, got x2 = %g", a, b, c, x2);
}
END_TEST

START_TEST(test_solve_quadratic_d_less_zero) {
    setup(1, 1, 1);
    ck_assert_msg(num_sol == 0, "If a = %g, b = %g, c = %g, 0 should be returned, got %d", a, b, c, num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_d_zero_num_sol) {
    setup(1, 2, 1);
    ck_assert_msg(num_sol == 1, "If a = %g, b = %g, c = %g, 1 should be returned, got %d", a, b, c, num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_d_zero_sol_value_1) {
    setup(1, 2, 1);
    ck_assert_msg(isEqual(x1, -1), "If a = %g, b = %g, c = %g, x1 == -1, got x1 = %g", a, b, c, x1);
}
END_TEST

START_TEST(test_solve_quadratic_d_zero_sol_value_2) {
    setup(1, 2, 1);
    ck_assert_msg(isEqual(x2, -1), "If a = %g, b = %g, c = %g, x2 == -1, got x2 = %g", a, b, c, x2);
}
END_TEST

START_TEST(test_solve_quadratic_d_more_zero_num_sol) {
    setup(1, -3, 2);
    ck_assert_msg(num_sol == 2, "If a = %g, b = %g, c = %g, 2 should be returned, got %d", a, b, c, num_sol);
}
END_TEST

START_TEST(test_solve_quadratic_d_more_zero_sol_value_1) {
    setup(1, -3, 2);
    ck_assert_msg(isEqual(x1, 1), "If a = %g, b = %g, c = %g, x1 == 1, got x1 = %g", a, b, c, x1);
}
END_TEST

START_TEST(test_solve_quadratic_d_more_zero_sol_value_2) {
    setup(1, -3, 2);
    ck_assert_msg(isEqual(x2, 2), "If a = %g, b = %g, c = %g, x2 == 2, got x2 = %g", a, b, c, x2);
}
END_TEST

START_TEST(test_solve_quadratic_normalize_value1) {
    double a = 4, b = -12, c = 8, x1 = NAN, x2 = NAN, x3 = NAN, x4 = NAN;
    solveQuadratic(a, b, c, &x1, &x2);
    a = 1;
    b = -3;
    c = 2;
    solveQuadratic(a, b, c, &x3, &x4);
    ck_assert_msg(isEqual(x1, x3), "If a = %g, b = %g, c = %g, x1 == x3, got x1 = %g, x3 = %g", a, b, c, x1, x3);
}
END_TEST

START_TEST(test_solve_quadratic_normalize_value2) {
    double a = 4, b = -12, c = 8, x1 = NAN, x2 = NAN, x3 = NAN, x4 = NAN;
    solveQuadratic(a, b, c, &x1, &x2);
    a = 1;
    b = -3;
    c = 2;
    solveQuadratic(a, b, c, &x3, &x4);
    ck_assert_msg(isEqual(x2, x4), "If a = %g, b = %g, c = %g, x2 == x4, got x2 = %g, x4 = %g", a, b, c, x2, x4);
}
END_TEST

Suite* test_solve_quadratic_suite() {
    Suite* s = suite_create("solve_quadratic");

    TCase* tc_all = tcase_create("all");
    tcase_add_test(tc_all, test_solve_quadratic_a_nan);
    tcase_add_test(tc_all, test_solve_quadratic_a_inf);
    tcase_add_test(tc_all, test_solve_quadratic_b_nan);
    tcase_add_test(tc_all, test_solve_quadratic_b_inf);
    tcase_add_test(tc_all, test_solve_quadratic_c_nan);
    tcase_add_test(tc_all, test_solve_quadratic_c_inf);
    tcase_add_test(tc_all, test_solve_quadratic_a_zero_b_zero_c_zero);
    tcase_add_test(tc_all, test_solve_quadratic_a_zero_b_zero_c_nonzero);
    tcase_add_test(tc_all, test_solve_quadratic_a_zero_b_nonzero_num_sol);
    tcase_add_test(tc_all, test_solve_quadratic_a_zero_b_nonzero_sol_value_1);
    tcase_add_test(tc_all, test_solve_quadratic_a_zero_b_nonzero_sol_value_2);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_zero_no_sol);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_zero_one_sol_num_sol);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_zero_one_sol_num_sol_value_1);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_zero_one_sol_num_sol_value_2);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_zero_two_sol_num_sol);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_zero_two_sol_num_sol_value_1);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_zero_two_sol_num_sol_value_2);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_nonzero_c_zero_num_sol);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_nonzero_c_zero_sol_value_1);
    tcase_add_test(tc_all, test_solve_quadratic_a_nonzero_b_nonzero_c_zero_sol_value_2);
    tcase_add_test(tc_all, test_solve_quadratic_d_less_zero);
    tcase_add_test(tc_all, test_solve_quadratic_d_zero_num_sol);
    tcase_add_test(tc_all, test_solve_quadratic_d_zero_sol_value_1);
    tcase_add_test(tc_all, test_solve_quadratic_d_zero_sol_value_2);
    tcase_add_test(tc_all, test_solve_quadratic_d_more_zero_num_sol);
    tcase_add_test(tc_all, test_solve_quadratic_d_more_zero_sol_value_1);
    tcase_add_test(tc_all, test_solve_quadratic_d_more_zero_sol_value_2);
    tcase_add_test(tc_all, test_solve_quadratic_normalize_value1);
    tcase_add_test(tc_all, test_solve_quadratic_normalize_value2);

    suite_add_tcase(s, tc_all);
    return s;
}

int main() {
    Suite* s = test_solve_quadratic_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (num_failed) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
