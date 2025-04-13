#include <check.h>
#include <s21_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(strstr_test1) {
  char *str1 = "Hello World!";
  char *str2 = "Wo";
  char *s = strstr(str1, str2);
  char *s21 = s21_strstr(str1, str2);

  ck_assert_str_eq(s, s21);
}

START_TEST(strstr_test2) {
  char *str1 = "Hello World!";
  char *str2 = "Wo45";
  char *s = strstr(str1, str2);
  char *s21 = s21_strstr(str1, str2);

  ck_assert_ptr_null(s);
  ck_assert_ptr_null(s21);
}

START_TEST(strstr_test3) {
  char *str1 = "Hello World!";
  char *str2 = "";
  char *s = strstr(str1, str2);
  char *s21 = s21_strstr(str1, str2);

  ck_assert_ptr_nonnull(s);
  ck_assert_ptr_nonnull(s21);
}

START_TEST(strstr_test4) {
  char *str1 = "Hello World!";
  char *str2 = " World!";
  char *s = strstr(str1, str2);
  char *s21 = s21_strstr(str1, str2);

  ck_assert_ptr_nonnull(s);
  ck_assert_ptr_nonnull(s21);
}

START_TEST(strstr_test5) {
  char *str1 = "Hello Wo rld!";
  char *str2 = "Wo rld!";
  char *s = strstr(str1, str2);
  char *s21 = s21_strstr(str1, str2);

  ck_assert_str_eq(s, s21);
}

START_TEST(strstr_test6) {
  char *str1 = "Hello World!\n";
  char *str2 = "World!\n";
  char *s = strstr(str1, str2);
  char *s21 = s21_strstr(str1, str2);

  if (s == NULL)
    ck_assert_ptr_null(s21);
  else
    ck_assert_str_eq(s, s21);
}

SRunner *strstr_test_runner() {
  TCase *cases = tcase_create("strstr_case");

  tcase_add_test(cases, strstr_test1);
  tcase_add_test(cases, strstr_test2);
  tcase_add_test(cases, strstr_test3);
  tcase_add_test(cases, strstr_test4);
  tcase_add_test(cases, strstr_test5);
  tcase_add_test(cases, strstr_test6);

  Suite *suite = suite_create("strstr_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}