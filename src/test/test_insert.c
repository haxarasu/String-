#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(s21_insert_test1) {
  const char sstr[] = "Begin";
  char* new_str = s21_insert(sstr, "->", 0);

  ck_assert_str_eq(new_str, "->Begin");

  free(new_str);
}

START_TEST(s21_insert_test2) {
  const char sstr[] = "Begin";
  char* new_str = s21_insert(sstr, "!", 1);

  ck_assert_str_eq(new_str, "B!egin");

  free(new_str);
}

START_TEST(s21_insert_test3) {
  const char sstr[] = "Begin";
  char* new_str = s21_insert(sstr, "!!", 2);

  ck_assert_str_eq(new_str, "Be!!gin");

  free(new_str);
}

START_TEST(s21_insert_test4) {
  const char sstr[] = "";
  char* new_str = s21_insert(sstr, "!!", 0);

  ck_assert_str_eq(new_str, "!!");

  free(new_str);
}

START_TEST(s21_insert_test5) {
  const char sstr[] = "";
  char* new_str = s21_insert(sstr, "!!", 2);

  ck_assert_ptr_null(new_str);

  free(new_str);
}

START_TEST(s21_insert_test6) {
  const char str[] = "GeeksForGeeks";
  char* new_str = s21_insert(str, "GFG", 5);
  ck_assert_str_eq(new_str, "GeeksGFGForGeeks");
  free(new_str);
}

SRunner* insert_test_runner() {
  TCase* cases = tcase_create("s21_insert_case");

  tcase_add_test(cases, s21_insert_test1);
  tcase_add_test(cases, s21_insert_test2);
  tcase_add_test(cases, s21_insert_test3);
  tcase_add_test(cases, s21_insert_test4);
  tcase_add_test(cases, s21_insert_test5);
  tcase_add_test(cases, s21_insert_test6);

  Suite* suite = suite_create("s21_insert_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
