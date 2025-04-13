#include <check.h>
#include <s21_string.h>
#include <string.h>

#define ERROR_COUNT 107

START_TEST(strerror_test1) {
  for (int i = 0; i < ERROR_COUNT; i++) {
    char *error = strerror(i);
    char *s21_error = s21_strerror(i);

    ck_assert_str_eq(error, s21_error);
  }
}

START_TEST(strerror_test2) {
  char *error = strerror(-1);
  char *s21_error = s21_strerror(-1);
  ck_assert_str_eq(error, s21_error);
}

START_TEST(strerror_test3) {
  char *error = strerror(-107);
  char *s21_error = s21_strerror(-107);
  ck_assert_str_eq(error, s21_error);
}

START_TEST(strerror_test4) {
  char *error = strerror(200);
  char *s21_error = s21_strerror(200);
  ck_assert_str_eq(error, s21_error);
}

SRunner *strerror_test_runner() {
  TCase *cases = tcase_create("strerror_case");

  tcase_add_test(cases, strerror_test1);
  tcase_add_test(cases, strerror_test2);
  tcase_add_test(cases, strerror_test3);
  tcase_add_test(cases, strerror_test4);

  Suite *suite = suite_create("strerror_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
