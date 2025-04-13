#include <check.h>
#include <s21_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(to_lower_test1) {
  char str[] = "SD";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "sd");
  free(result);
}

START_TEST(to_lower_test2) {
  char str[] = "";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "");
  free(result);
}

START_TEST(to_lower_test3) {
  char *s = s21_to_lower(S21_NULL);
  ck_assert_ptr_null(s);
  free(s);
}

START_TEST(to_lower_test4) {
  char str[] = "sd";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "sd");
  free(result);
}

SRunner *to_lower_test_runner() {
  TCase *cases = tcase_create("to_lower_case");

  tcase_add_test(cases, to_lower_test1);
  tcase_add_test(cases, to_lower_test2);
  tcase_add_test(cases, to_lower_test3);
  tcase_add_test(cases, to_lower_test4);

  Suite *suite = suite_create("to_lower_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}