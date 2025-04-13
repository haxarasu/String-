#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(strncmp_test1) {
  char testStr1[] = "Debug";
  char testStr2[] = "Debug";

  int r1 = strncmp(testStr1, testStr2, strlen(testStr1)) == 0 ? 1 : -1;
  int r2 = s21_strncmp(testStr1, testStr2, s21_strlen(testStr1)) == 0 ? 1 : -1;
  ck_assert_int_eq(r1, r2);
}

START_TEST(strncmp_test2) {
  char testStr1[] = "Debug";
  char testStr2[] = "D";

  int r1 = strncmp(testStr1, testStr2, strlen(testStr1)) == 0 ? 1 : -1;
  int r2 = s21_strncmp(testStr1, testStr2, s21_strlen(testStr1)) == 0 ? 1 : -1;
  ck_assert_int_eq(r1, r2);
}

START_TEST(strncmp_test3) {
  char testStr1[] = "Deb";
  char testStr2[] = "Debug";

  int r1 = strncmp(testStr1, testStr2, strlen(testStr1)) == 0 ? 1 : -1;
  int r2 = s21_strncmp(testStr1, testStr2, s21_strlen(testStr1)) == 0 ? 1 : -1;
  ck_assert_int_eq(r1, r2);
}

START_TEST(strncmp_test4) {
  char testStr1[] = "0";
  char testStr2[] = "";

  int r1 = strncmp(testStr1, testStr2, strlen(testStr1)) == 0 ? 1 : -1;
  int r2 = s21_strncmp(testStr1, testStr2, s21_strlen(testStr1)) == 0 ? 1 : -1;
  ck_assert_int_eq(r1, r2);
}

START_TEST(strncmp_test5) {
  char testStr1[] = "";
  char testStr2[] = "";

  int r1 = strncmp(testStr1, testStr2, strlen(testStr1)) == 0 ? 1 : -1;
  int r2 = s21_strncmp(testStr1, testStr2, s21_strlen(testStr1)) == 0 ? 1 : -1;
  ck_assert_int_eq(r1, r2);
}

SRunner *strncmp_test_runner() {
  TCase *cases = tcase_create("strncmp_case");

  tcase_add_test(cases, strncmp_test1);
  tcase_add_test(cases, strncmp_test2);
  tcase_add_test(cases, strncmp_test3);
  tcase_add_test(cases, strncmp_test4);
  tcase_add_test(cases, strncmp_test5);

  Suite *suite = suite_create("strncmp_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
