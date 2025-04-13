#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(memset_test1) {
  char s1[80];
  void *m1 = memset(s1, 0x41, 8);
  void *m2 = s21_memset(s1, 0x41, 8);

  ck_assert_ptr_eq(m1, m2);
}

START_TEST(memset_test2) {
  char buf1[4] = {0};
  memset(buf1, 0x41, strlen(buf1));

  char buf2[4] = {0};
  s21_memset(buf2, 0x41, s21_strlen(buf2));

  ck_assert_str_eq(buf1, buf2);
}

START_TEST(memset_test3) {
  char buf1[4] = "DDD\0";
  memset(buf1, 0x41, strlen(buf1));

  char buf2[4] = "DDD\0";
  s21_memset(buf2, 0x41, s21_strlen(buf2));

  ck_assert_str_eq(buf1, buf2);
}

SRunner *memset_test_runner() {
  TCase *cases = tcase_create("memset_case");

  tcase_add_test(cases, memset_test1);
  tcase_add_test(cases, memset_test2);
  tcase_add_test(cases, memset_test3);

  Suite *suite = suite_create("memset_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}
