#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(strncpy_test1) {
  char str[] = "Hello world!";
  char buffer1[80] = {0};
  char buffer2[80] = {0};

  strncpy(buffer1, str, strlen(str));
  s21_strncpy(buffer2, str, s21_strlen(str));

  ck_assert_str_eq(buffer1, buffer2);
}

SRunner *strncpy_test_runner() {
  TCase *cases = tcase_create("strncpy_case");

  tcase_add_test(cases, strncpy_test1);

  Suite *suite = suite_create("strncpy_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}