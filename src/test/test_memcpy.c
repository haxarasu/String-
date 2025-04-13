#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(memcpy_test1) {
  char testStr1[100];
  char testStr2[] = "Debug";

  void* r1 = memcpy(testStr1, testStr2, strlen(testStr2));
  void* r2 = s21_memcpy(testStr1, testStr2, s21_strlen(testStr2));
  ck_assert_ptr_eq(r1, r2);
}

START_TEST(memcpy_test2) {
  char testStr1[100];
  char testStr2[] = "";

  void* r1 = memcpy(testStr1, testStr2, strlen(testStr2));
  void* r2 = s21_memcpy(testStr1, testStr2, s21_strlen(testStr2));
  ck_assert_ptr_eq(r1, r2);
}

START_TEST(memcpy_test3) {
  char testStr2[] = "Debug";
  char dest1[10];

  void* r1 = memcpy(dest1, testStr2, 0);
  void* r2 = s21_memcpy(dest1, testStr2, 0);
  ck_assert_ptr_eq(r1, r2);
}

START_TEST(memcpy_test4) {
  char testStr1[80];
  char testStr2[] = "Debug";

  void* r1 = memcpy(testStr1, testStr2, 0);
  void* r2 = s21_memcpy(testStr1, testStr2, 0);
  ck_assert_ptr_eq(r1, r2);
}

START_TEST(memcpy_test5) {
  char testStr1[] = "DEBUG";
  char testStr2[] = "DEBUG";

  void* r1 = memcpy(testStr1, testStr2, strlen(testStr2));
  void* r2 = s21_memcpy(testStr1, testStr2, s21_strlen(testStr2));
  ck_assert_ptr_eq(r1, r2);
  ck_assert_str_eq(testStr1, testStr2);
}

SRunner* memcpy_test_runner() {
  TCase* cases = tcase_create("memcpy_case");

  tcase_add_test(cases, memcpy_test1);
  tcase_add_test(cases, memcpy_test2);
  tcase_add_test(cases, memcpy_test3);
  tcase_add_test(cases, memcpy_test4);
  tcase_add_test(cases, memcpy_test5);

  Suite* suite = suite_create("memcpy_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
