#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(strncat_test1) {
  char buffer1[80] = {0};
  char test1[] = "Hello ";
  char test2[] = "world !";
  strcpy(buffer1, test1);
  char* result1 = strncat(buffer1, test2, strlen(test2) + 1);

  // ck_assert_str_eq(result1, "Hello world !");

  char buffer2[80] = {0};
  strcpy(buffer2, test1);
  char* result2 = s21_strncat(buffer2, test2, s21_strlen(test2) + 1);

  ck_assert_str_eq(result2, result1);
}

START_TEST(strncat_test2) {
  char buffer1[80] = {0};
  char test1[] = "";
  char test2[] = "0";
  strcpy(buffer1, test1);
  char* result1 = strncat(buffer1, test2, strlen(test2) + 1);

  // ck_assert_str_eq(result1, "Hello world !");

  char buffer2[80] = {0};
  strcpy(buffer2, test1);
  char* result2 = s21_strncat(buffer2, test2, s21_strlen(test2) + 1);

  ck_assert_str_eq(result2, result1);
}

SRunner* strncat_test_runner() {
  TCase* cases = tcase_create("strncat_case");

  tcase_add_test(cases, strncat_test1);
  tcase_add_test(cases, strncat_test2);

  Suite* suite = suite_create("strncat_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
