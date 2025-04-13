#include <check.h>
#include <s21_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(strlen_test1) {
  int len1 = strlen("Hello world!");
  int len2 = s21_strlen("Hello world!");
  ck_assert_int_eq(len1, len2);
}

START_TEST(strlen_test2) {
  int len1 = strlen("");
  int len2 = s21_strlen("");
  ck_assert_int_eq(len1, len2);
}

START_TEST(strlen_test3) {
  int len1 = strlen("\n");
  int len2 = s21_strlen("\n");
  ck_assert_int_eq(len1, len2);
}

START_TEST(strlen_test4) {
  char *Buffer = calloc(10000, 1);
  int len1 = strlen(Buffer);
  int len2 = s21_strlen(Buffer);
  ck_assert_int_eq(len1, len2);
  free(Buffer);
}

START_TEST(strlen_test5) {
  ck_assert_int_eq(sizeof(size_t), sizeof(s21_size_t));
}

SRunner *strlen_test_runner() {
  TCase *cases = tcase_create("strlen_case");

  tcase_add_test(cases, strlen_test1);
  tcase_add_test(cases, strlen_test2);
  tcase_add_test(cases, strlen_test3);
  tcase_add_test(cases, strlen_test4);
  tcase_add_test(cases, strlen_test5);

  Suite *suite = suite_create("strlen_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}