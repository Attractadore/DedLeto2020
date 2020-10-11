#include "util.h"

#include <check.h>

#include <assert.h>
#include <stdlib.h>

enum {NUM_QUICK_SORT_ITER = 1000};

int int_comp(void const* lvp, void const* rvp) {
    assert(lvp);
    assert(rvp);

    int const* lip = lvp;
    int const* rip = rvp;

    if (*lip < *rip) {
        return -1;
    }
    if (*lip > *rip) {
        return 1;
    }
    return 0;
}

void fill_random(int* arr, size_t num) {
    assert(arr);

    for (size_t i = 0; i < num; i++) {
        arr[i] = rand();
    }
}

void fill_same(int* arr, size_t num) {
    assert(arr);

    int v = rand();
    for (size_t i = 0; i < num; i++) {
        arr[i] = v;
    }
}

void fill_sorted(int* arr, size_t num) {
    assert(arr);

    fill_random(arr, num);
    qsort(arr, num, sizeof(*arr), int_comp);
}

START_TEST(test_swap_1) {
    int a = 10;
    int b = 0;
    swap(int, a, b);
    ck_assert_int_eq(a, 0);
    ck_assert_int_eq(b, 10);
}
END_TEST

START_TEST(test_swap_2) {
    int a = 10;
    int b = 0;
    int* ap = &a;
    int* bp = &b;
    swap(int*, ap, bp);
    ck_assert_ptr_eq(ap, &b);
    ck_assert_ptr_eq(bp, &a);
}
END_TEST

START_TEST(test_memswap_1) {
    int a = 10;
    int b = 0;
    memswap(&a, &b, sizeof(a));
    ck_assert_int_eq(a, 0);
    ck_assert_int_eq(b, 10);
}
END_TEST

START_TEST(test_memswap_2) {
    int a = 10;
    int b = 0;
    int* ap = &a;
    int* bp = &b;
    memswap(&ap, &bp, sizeof(a));
    ck_assert_ptr_eq(ap, &b);
    ck_assert_ptr_eq(bp, &a);
}
END_TEST

START_TEST(test_memswap_3) {
    char a[100];
    char a_orig[100];
    char b[100];
    char b_orig[100];
    memset(a_orig, 'a', sizeof(a));
    memset(b_orig, 'b', sizeof(b));
    memcpy(a, a_orig, sizeof(a_orig));
    memcpy(b, b_orig, sizeof(b_orig));

    memswap(a, b, sizeof(a));
    ck_assert_mem_eq(a, b_orig, sizeof(a));
    ck_assert_mem_eq(b, a_orig, sizeof(b));
}
END_TEST

START_TEST(test_read_buffer_non_empty_file_ptr) {
    char const* file_name = "test/non_empty_file";
    char const* file_contents = "This is a \n test file\n";
    FILE* fp = fopen(file_name, "rb");
    ck_assert_msg(fp, "Failed to open file %s for reading", file_name);
    char* buf = NULL;
    int num = read_buffer(fp, &buf);
    ck_assert_msg(strncmp(buf, file_contents, strlen(file_contents)) == 0,
                  "Failed to read data from file %s: "
                  "expected contents to be %s, got %.*s",
                  file_name, file_contents, num, buf);
    free(buf);
    fclose(fp);
}
END_TEST

START_TEST(test_read_buffer_non_empty_file_num) {
    char const* file_name = "test/non_empty_file";
    char const* file_contents = "This is a \n test file\n";
    FILE* fp = fopen(file_name, "rb");
    ck_assert_msg(fp, "Failed to open file %s for reading", file_name);
    char* buf = NULL;
    size_t num = read_buffer(fp, &buf);
    size_t contents_size = strlen(file_contents);
    ck_assert_msg(num == contents_size,
                  "Failed to read data from file %s: "
                  "expected size to be %lu got %lu",
                  file_name, num, contents_size);
    free(buf);
    fclose(fp);
}
END_TEST

START_TEST(test_read_buffer_empty_file_ptr) {
    char const* file_name = "test/empty_file";
    char const* file_contents = "";
    FILE* fp = fopen(file_name, "rb");
    ck_assert_msg(fp, "Failed to open file %s for reading", file_name);
    char* buf = NULL;
    int num = read_buffer(fp, &buf);
    ck_assert_msg(buf == NULL,
                  "Failed to read data from file %s: "
                  "expected contents to be %s, got %.*s",
                  file_name, file_contents, num, buf);
    free(buf);
    fclose(fp);
}
END_TEST

START_TEST(test_read_buffer_empty_file_num) {
    char const* file_name = "test/empty_file";
    char const* file_contents = "";
    FILE* fp = fopen(file_name, "rb");
    ck_assert_msg(fp, "Failed to open file %s for reading", file_name);
    char* buf = NULL;
    size_t num = read_buffer(fp, &buf);
    size_t contents_size = strlen(file_contents);
    ck_assert_msg(num == contents_size,
                  "Failed to read data from file %s: "
                  "expected size to be %lu got %lu",
                  file_name, num, contents_size);
    free(buf);
    fclose(fp);
}
END_TEST

START_TEST(test_read_buffer_non_read_file_ptr) {
    char const* file_name = "test/non_empty_file";
    FILE* fp = fopen(file_name, "ab");
    ck_assert_msg(fp, "Failed to open file %s for appending", file_name);
    char* buf = NULL;
    int num = read_buffer(fp, &buf);
    ck_assert_msg(buf == NULL,
                  "Unexpected result while trying to read data from file %s not opened for reading: "
                  "expected contents to be NULL, got %.*s",
                  file_name, num, buf);
    free(buf);
    fclose(fp);
}
END_TEST

START_TEST(test_read_buffer_non_read_file_num) {
    char const* file_name = "test/non_empty_file";
    FILE* fp = fopen(file_name, "ab");
    ck_assert_msg(fp, "Failed to open file %s for appending", file_name);
    char* buf = NULL;
    size_t num = read_buffer(fp, &buf);
    ck_assert_msg(num == 0,
                  "Unexpected result while trying to read data from file %s not opened for reading: "
                  "expected size to be %lu, for %lu",
                  file_name, 0UL, num);
    free(buf);
    fclose(fp);
}
END_TEST

START_TEST(test_read_buffer_non_read_stream_ptr) {
    char* buf = NULL;
    int num = read_buffer(stdout, &buf);
    ck_assert_msg(buf == NULL,
                  "Unexpected result while trying to read data from stdout: "
                  "expected contents to be NULL, got %.*s",
                  num, buf);
    free(buf);
}
END_TEST

START_TEST(test_read_buffer_non_read_stream_num) {
    char* buf = NULL;
    size_t num = read_buffer(stdout, &buf);
    ck_assert_msg(num == 0,
                  "Unexpected result while trying to read data from stdout: "
                  "expected size to be %lu, for %lu",
                  0UL, num);
    free(buf);
}
END_TEST

START_TEST(test_is_sorted_sorted) {
    int arr[] = {-10, 0, 1, 2, 3, 3, 4, 5, 10};
    size_t num = sizeof(arr) / sizeof(*arr);
    size_t sz = sizeof(*arr);
    ck_assert_msg(is_sorted(arr, num, sz, int_comp),
                  "Expected sorted array to be considered sorted");
}
END_TEST

START_TEST(test_is_sorted_not_sorted) {
    int arr[] = {10, 5, 4, 2, 3, 3, 5, 0, -10};
    size_t num = sizeof(arr) / sizeof(*arr);
    size_t sz = sizeof(*arr);
    ck_assert_msg(!is_sorted(arr, num, sz, int_comp),
                  "Expected not sorted array to be considered not sorted");
}
END_TEST

START_TEST(test_is_sorted_almost_sorted) {
    int arr[] = {-10, 0, 1, 2, 4, 3, 4, 5, 10};
    size_t num = sizeof(arr) / sizeof(*arr);
    size_t sz = sizeof(*arr);
    ck_assert_msg(!is_sorted(arr, num, sz, int_comp),
                  "Expected almost sorted array to be considered not sorted");
}
END_TEST

START_TEST(test_is_sorted_same_element) {
    int arr[10] = {};
    size_t num = sizeof(arr) / sizeof(*arr);
    size_t sz = sizeof(*arr);
    ck_assert_msg(is_sorted(arr, num, sz, int_comp),
                  "expected array of same elements to be considered sorted");
}
END_TEST

START_TEST(test_is_sorted_empty) {
    int arr[] = {};
    size_t num = sizeof(arr) / sizeof(*arr);
    size_t sz = sizeof(*arr);
    ck_assert_msg(is_sorted(arr, num, sz, int_comp),
                  "expected empty array to be considered sorted");
}
END_TEST

START_TEST(test_is_sorted_one) {
    int arr[1] = {};
    size_t num = sizeof(arr) / sizeof(*arr);
    size_t sz = sizeof(*arr);
    ck_assert_msg(is_sorted(arr, num, sz, int_comp),
                  "expected array of one element to be considered sorted");
}
END_TEST

START_TEST(test_quick_sort_random) {
    int arr[1000];
    size_t sz = sizeof(*arr);
    size_t num = sizeof(arr) / sz;
    for (size_t i = 0; i < NUM_QUICK_SORT_ITER; i++) {
        fill_random(arr, num);
        quick_sort(arr, num, sz, int_comp);
        ck_assert_msg(is_sorted(arr, num, sz, int_comp),
                      "quick_sort failed to sort an array of random data of size %lu", num);
    }
}
END_TEST

START_TEST(test_quick_sort_same) {
    int arr[1000];
    size_t sz = sizeof(*arr);
    size_t num = sizeof(arr) / sz;
    for (size_t i = 0; i < NUM_QUICK_SORT_ITER; i++) {
        fill_same(arr, num);
        quick_sort(arr, num, sz, int_comp);
        ck_assert_msg(is_sorted(arr, num, sz, int_comp),
                      "quick_sort failed to sort an array of same data of size %lu", num);
    }
}
END_TEST

START_TEST(test_quick_sort_sorted) {
    int arr[1000];
    size_t sz = sizeof(*arr);
    size_t num = sizeof(arr) / sz;
    for (size_t i = 0; i < NUM_QUICK_SORT_ITER; i++) {
        fill_sorted(arr, num);
        quick_sort(arr, num, sz, int_comp);
        ck_assert_msg(is_sorted(arr, num, sz, int_comp),
                      "quick_sort failed to sort an array of sorted data of size %lu", num);
    }
}
END_TEST

Suite* setup_swap_suite() {
    Suite* s = suite_create("swap");

    TCase* swap_all = tcase_create("usage of swap");
    tcase_add_test(swap_all, test_swap_1);
    tcase_add_test(swap_all, test_swap_2);

    suite_add_tcase(s, swap_all);

    return s;
}

Suite* setup_memswap_suite() {
    Suite* s = suite_create("memswap");

    TCase* memswap_all = tcase_create("usage of memswap");
    tcase_add_test(memswap_all, test_memswap_1);
    tcase_add_test(memswap_all, test_memswap_2);
    tcase_add_test(memswap_all, test_memswap_3);

    suite_add_tcase(s, memswap_all);

    return s;
}

Suite* setup_read_buffer_suite() {
    Suite* s = suite_create("read_buffer");

    TCase* read_buffer_non_empty = tcase_create("read_buffer on non-empty file");
    tcase_add_test(read_buffer_non_empty, test_read_buffer_non_empty_file_ptr);
    tcase_add_test(read_buffer_non_empty, test_read_buffer_non_empty_file_num);

    TCase* read_buffer_empty = tcase_create("read_buffer on empty file");
    tcase_add_test(read_buffer_empty, test_read_buffer_empty_file_ptr);
    tcase_add_test(read_buffer_empty, test_read_buffer_empty_file_num);

    TCase* read_buffer_non_read = tcase_create("read_buffer on non-read file");
    tcase_add_test(read_buffer_non_read, test_read_buffer_non_read_file_ptr);
    tcase_add_test(read_buffer_non_read, test_read_buffer_non_read_file_num);

    TCase* read_buffer_non_read_stream = tcase_create("read_buffer on non-read file");
    tcase_add_test(read_buffer_non_read_stream, test_read_buffer_non_read_stream_ptr);
    tcase_add_test(read_buffer_non_read_stream, test_read_buffer_non_read_stream_num);

    suite_add_tcase(s, read_buffer_non_empty);
    suite_add_tcase(s, read_buffer_empty);
    suite_add_tcase(s, read_buffer_non_read);
    suite_add_tcase(s, read_buffer_non_read_stream);

    return s;
}

Suite* setup_is_sorted_suite() {
    Suite* s = suite_create("is_sorted");

    TCase* is_sorted_sorted = tcase_create("is_sorted on sorted arrays");
    tcase_add_test(is_sorted_sorted, test_is_sorted_sorted);
    tcase_add_test(is_sorted_sorted, test_is_sorted_same_element);
    tcase_add_test(is_sorted_sorted, test_is_sorted_empty);
    tcase_add_test(is_sorted_sorted, test_is_sorted_one);

    TCase* is_sorted_not_sorted = tcase_create("is_sorted on sorted arrays");
    tcase_add_test(is_sorted_not_sorted, test_is_sorted_not_sorted);
    tcase_add_test(is_sorted_not_sorted, test_is_sorted_almost_sorted);

    suite_add_tcase(s, is_sorted_sorted);
    suite_add_tcase(s, is_sorted_not_sorted);

    return s;
}

Suite* setup_quick_sort_suite() {
    Suite* s = suite_create("quick_sort");

    TCase* quick_sort_random = tcase_create("quick_sort on random data");
    tcase_add_test(quick_sort_random, test_quick_sort_random);

    TCase* quick_sort_same = tcase_create("quick_sort on same data");
    tcase_add_test(quick_sort_same, test_quick_sort_same);

    TCase* quick_sort_sorted = tcase_create("quick_sort on sorted data");
    tcase_add_test(quick_sort_sorted, test_quick_sort_sorted);

    suite_add_tcase(s, quick_sort_random);
    suite_add_tcase(s, quick_sort_same);
    suite_add_tcase(s, quick_sort_sorted);

    return s;
}

int main() {
    SRunner* runner = srunner_create(NULL);
    srunner_add_suite(runner, setup_swap_suite());
    srunner_add_suite(runner, setup_memswap_suite());
    srunner_add_suite(runner, setup_read_buffer_suite());
    srunner_add_suite(runner, setup_is_sorted_suite());
    srunner_add_suite(runner, setup_quick_sort_suite());

    srunner_run_all(runner, CK_NORMAL);
    int num_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    if (num_failed) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
