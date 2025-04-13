#include <check.h>
#include <s21_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(strrchr_test1) {
  char *r1 = strrchr("Debug", 'D');
  char *r2 = s21_strrchr("Debug", 'D');
  ck_assert_str_eq(r1, r2);
}

START_TEST(strrchr_test2) {
  char *o = strrchr("", 'D');
  char *o1 = s21_strrchr("", 'D');

  ck_assert_ptr_null(o);
  ck_assert_ptr_null(o1);
}

START_TEST(strrchr_test3) {
  char *o = strrchr("cvsdfdsAsdfewsdFAe", 'A');
  char *o1 = s21_strrchr("ocvsdfdsAsdfewsdFAe", 'A');

  ck_assert_ptr_nonnull(o);
  ck_assert_ptr_nonnull(o1);

  ck_assert_pstr_eq(o, o1);
}

START_TEST(strrchr_test4) {
  char *o = strrchr("sdfsdfsdf", '!');
  char *o1 = s21_strrchr("sdfs!fsdf", '!');

  ck_assert_ptr_null(o);
  ck_assert_ptr_nonnull(o1);

  ck_assert_pstr_ne(o, o1);
}

START_TEST(strrchr_test5) {
  char *o = strrchr("sdfsdfsdf", '\0');
  char *o1 = s21_strrchr("sdfsdfsdf", '\0');

  ck_assert_pstr_eq(o, o1);
}

SRunner *strrchr_test_runner() {
  TCase *cases = tcase_create("strrchr_case");

  tcase_add_test(cases, strrchr_test1);
  tcase_add_test(cases, strrchr_test2);
  tcase_add_test(cases, strrchr_test3);
  tcase_add_test(cases, strrchr_test4);
  tcase_add_test(cases, strrchr_test5);

  Suite *suite = suite_create("strrchr_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}