#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(strcspn_test1) {
  char T1[] = "AAABBBOAAA";
  char T2[] = "O";
  int r1 = strcspn(T1, T2);
  int r2 = s21_strcspn(T1, T2);

  ck_assert_int_eq(r1, r2);
}

START_TEST(strcspn_test2) {
  char T1[] = "AAABBBOAAA";
  char T2[] = "!!@3232";
  int r1 = strcspn(T1, T2);
  int r2 = s21_strcspn(T1, T2);

  ck_assert_int_eq(r1, r2);
}

START_TEST(strcspn_test3) {
  char T1[] = "";
  char T2[] = "!!@3232";
  int r1 = strcspn(T1, T2);
  int r2 = s21_strcspn(T1, T2);

  ck_assert_int_eq(r1, r2);
}

START_TEST(strcspn_test4) {
  char T1[] = "AAABBBOAAA";
  char T2[] = "";
  int r1 = strcspn(T1, T2);
  int r2 = s21_strcspn(T1, T2);

  ck_assert_int_eq(r1, r2);
}

SRunner *strcspn_test_runner() {
  TCase *cases = tcase_create("strcspn_case");

  tcase_add_test(cases, strcspn_test1);
  tcase_add_test(cases, strcspn_test2);
  tcase_add_test(cases, strcspn_test3);
  tcase_add_test(cases, strcspn_test4);

  Suite *suite = suite_create("strcspn_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
