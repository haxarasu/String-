#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(s21_trim_test1) {
  const char sstr[] = "Begin";
  char* new_str = s21_trim(sstr, "H");

  ck_assert_str_eq(new_str, "Begin");

  free(new_str);
}

START_TEST(s21_trim_test2) {
  const char sstr[] = "Begin";
  char* new_str = s21_trim(sstr, "B");
  ck_assert_str_eq(new_str, "egin");

  free(new_str);
}

START_TEST(s21_trim_test3) {
  const char sstr[] = "Begin";
  char* new_str = s21_trim(sstr, "Be");
  ck_assert_str_eq(new_str, "gin");

  free(new_str);
}

START_TEST(s21_trim_test4) {
  const char sstr[] = "Begin";
  char* new_str = s21_trim(sstr, "n");
  ck_assert_str_eq(new_str, "Begi");

  free(new_str);
}

START_TEST(s21_trim_test5) {
  const char sstr[] = "Begin";
  char* new_str = s21_trim(sstr, "Begin");
  ck_assert_str_eq(new_str, "");

  free(new_str);
}

START_TEST(s21_trim_test6) {
  const char sstr[] = "Begin";
  char* new_str = s21_trim(sstr, S21_NULL);
  ck_assert_str_eq(new_str, "Begin");

  free(new_str);
}

SRunner* trim_test_runner() {
  TCase* cases = tcase_create("s21_trim_case");

  tcase_add_test(cases, s21_trim_test1);
  tcase_add_test(cases, s21_trim_test2);
  tcase_add_test(cases, s21_trim_test3);
  tcase_add_test(cases, s21_trim_test4);
  tcase_add_test(cases, s21_trim_test5);
  tcase_add_test(cases, s21_trim_test6);

  Suite* suite = suite_create("s21_trim_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}