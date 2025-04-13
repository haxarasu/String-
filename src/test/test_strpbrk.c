#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(strpbrk_test1) {
  char testStr[] = "cvsdfdsAsdfewsdFAe";
  char *o1 = strpbrk(testStr, "vienna");
  char *o2 = s21_strpbrk(testStr, "vienna");

  ck_assert_ptr_eq(o1, o2);
  ck_assert_str_eq(o1, o2);
}

START_TEST(strpbrk_test2) {
  char testStr[] = "cvsdfdsA";
  char *o1 = strpbrk(testStr, "na");
  char *o2 = s21_strpbrk(testStr, "na");

  ck_assert_ptr_eq(o1, o2);
}

START_TEST(strpbrk_test3) {
  char testStr[] = "";
  char *o1 = strpbrk(testStr, "na");
  char *o2 = s21_strpbrk(testStr, "na");

  ck_assert_ptr_eq(o1, o2);
}

START_TEST(strpbrk_test4) {
  char testStr[] = "sdfsdfasdf";
  char *o1 = strpbrk(testStr, "");
  char *o2 = s21_strpbrk(testStr, "");

  ck_assert_ptr_eq(o1, o2);
}

SRunner *strpbrk_test_runner() {
  TCase *cases = tcase_create("strpbrk_case");

  tcase_add_test(cases, strpbrk_test1);
  tcase_add_test(cases, strpbrk_test2);
  tcase_add_test(cases, strpbrk_test3);
  tcase_add_test(cases, strpbrk_test4);

  Suite *suite = suite_create("strpbrk_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
