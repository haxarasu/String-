#include <check.h>
#include <s21_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(to_upper_test1) {
  char str[] = "sd";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "SD");
  free(result);
}

START_TEST(to_upper_test2) {
  char str[] = "";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "");
  free(result);
}

START_TEST(to_upper_test3) {
  char *s = s21_to_upper(S21_NULL);
  ck_assert_ptr_null(s);
  free(s);
}

START_TEST(to_upper_test4) {
  char str[] = "SD";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "SD");
  free(result);
}

SRunner *to_upper_test_runner() {
  TCase *cases = tcase_create("to_upper_case");

  tcase_add_test(cases, to_upper_test1);
  tcase_add_test(cases, to_upper_test2);
  tcase_add_test(cases, to_upper_test3);
  tcase_add_test(cases, to_upper_test4);

  Suite *suite = suite_create("to_upper_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}