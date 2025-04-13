#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(strchr_test1) {
  char *r1 = strchr("Debug", 'D');
  char *r2 = s21_strchr("Debug", 'D');
  ck_assert_str_eq(r1, r2);
}

START_TEST(strchr_test2) {
  char *o = strchr("", 'D');
  char *o1 = s21_strchr("", 'D');

  ck_assert_ptr_null(o);
  ck_assert_ptr_null(o1);
}

START_TEST(strchr_test3) {
  char *o = strchr("cvsdfdsAsdfewsdFAe", 'A');
  char *o1 = s21_strchr("ocvsdfdsAsdfewsdFAe", 'A');

  ck_assert_ptr_nonnull(o);
  ck_assert_ptr_nonnull(o1);

  ck_assert_pstr_eq(o, o1);
}

START_TEST(strchr_test4) {
  char *o = strchr("sdfsdfsdf", '!');
  char *o1 = s21_strchr("sdfs!fsdf", '!');

  ck_assert_ptr_null(o);
  ck_assert_ptr_nonnull(o1);

  ck_assert_pstr_ne(o, o1);
}

START_TEST(strchr_test5) {
  char *o = strchr("sdfsdfsdf", '\0');
  char *o1 = s21_strchr("sdfsdfsdf", '\0');

  ck_assert_pstr_eq(o, o1);
}

SRunner *strchr_test_runner() {
  TCase *cases = tcase_create("strchr_case");

  tcase_add_test(cases, strchr_test1);
  tcase_add_test(cases, strchr_test2);
  tcase_add_test(cases, strchr_test3);
  tcase_add_test(cases, strchr_test4);
  tcase_add_test(cases, strchr_test5);

  Suite *suite = suite_create("strchr_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
