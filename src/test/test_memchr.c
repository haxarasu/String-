#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(memchr_test1) {
  char testStr[] = "Debug";
  char *r1 = memchr(testStr, 'D', strlen(testStr));
  char *r2 = s21_memchr(testStr, 'D', s21_strlen(testStr));
  ck_assert_str_eq(r1, r2);
}

START_TEST(memchr_test2) {
  char testStr[] = "";
  char *o = memchr(testStr, 'D', strlen(testStr));
  char *o1 = s21_memchr(testStr, 'D', s21_strlen(testStr));

  ck_assert_ptr_null(o);
  ck_assert_ptr_null(o1);
}

START_TEST(memchr_test3) {
  char testStr[] = "cvsdfdsAsdfewsdFAe";
  char *o = memchr(testStr, 'A', strlen(testStr));
  char *o1 = s21_memchr(testStr, 'A', s21_strlen(testStr));

  ck_assert_ptr_nonnull(o);
  ck_assert_ptr_nonnull(o1);

  ck_assert_pstr_eq(o, o1);
}

START_TEST(memchr_test4) {
  char testStr1[] = "sdfsdfsdf";
  char testStr2[] = "sdfs!fsdf";
  char *o = memchr(testStr1, '!', strlen(testStr1));
  char *o1 = s21_memchr(testStr2, '!', s21_strlen(testStr2));

  ck_assert_ptr_null(o);
  ck_assert_ptr_nonnull(o1);

  ck_assert_pstr_ne(o, o1);
}

SRunner *memchr_test_runner() {
  TCase *cases = tcase_create("memchr_case");

  tcase_add_test(cases, memchr_test1);
  tcase_add_test(cases, memchr_test2);
  tcase_add_test(cases, memchr_test3);
  tcase_add_test(cases, memchr_test4);

  Suite *suite = suite_create("memchr_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
