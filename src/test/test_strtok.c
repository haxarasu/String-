#include <check.h>
#include <s21_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(strtok_test1) {
  char str1[] = "Fuck-you-bich";

  char *s = s21_strtok(str1, "-");
  char *s1 = strtok(str1, "-");

  ck_assert_str_eq(s1, s);
}

START_TEST(strtok_test2) {
  char str1[] = "Fuck-you-bich";

  char *s = s21_strtok(str1, "-");
  char *s1 = strtok(str1, "-");

  ck_assert_ptr_eq(s1, s);
}

START_TEST(strtok_test3) {
  char str1[] = "Fuck-you-bich";
  char str2[] = "Fuck-you-bich";

  char *s = s21_strtok(str1, "-");
  char *s1 = strtok(str2, "-");

  s = s21_strtok(NULL, "-");
  s1 = strtok(NULL, "-");

  ck_assert_str_eq(s, s1);
}

START_TEST(strtok_test4) {
  char str1[] = "Fuck-you-bich";

  char *s = s21_strtok(str1, "-");
  char *s1 = strtok(str1, "-");

  s = s21_strtok(NULL, "-");
  s1 = strtok(NULL, "-");

  s = s21_strtok(NULL, "-");
  s1 = strtok(NULL, "-");

  s = s21_strtok(NULL, "-");
  s1 = strtok(NULL, "-");

  ck_assert_ptr_null(s);
  ck_assert_ptr_null(s1);
}

START_TEST(strtok_test5) {
  char str1[] = "";

  char *s = s21_strtok(str1, "-");
  char *s1 = strtok(str1, "-");

  ck_assert_ptr_null(s);
  ck_assert_ptr_null(s1);
}

SRunner *strtok_test_runner() {
  TCase *cases = tcase_create("strtok_case");

  tcase_add_test(cases, strtok_test1);
  tcase_add_test(cases, strtok_test2);
  tcase_add_test(cases, strtok_test3);
  tcase_add_test(cases, strtok_test4);
  tcase_add_test(cases, strtok_test5);

  Suite *suite = suite_create("strtok_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}