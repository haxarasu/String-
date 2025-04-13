#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(sscanf_test1) {
  char str[] = "5";

  int v1;
  int v2;
  s21_sscanf(str, "%d", &v1);
  sscanf(str, "%d", &v2);

  ck_assert_int_eq(v1, v2);
}

START_TEST(sscanf_test2) {
  char str[] = "Hello World!";

  char str1[100] = {0};
  char str2[100] = {0};
  s21_sscanf(str, "%s", str1);
  sscanf(str, "%s", str2);

  ck_assert_str_eq(str2, str2);
}

START_TEST(sscanf_test3) {
  char str[] = "5.3";

  float v1;
  float v2;
  s21_sscanf(str, "%f", &v1);
  sscanf(str, "%f", &v2);

  ck_assert_double_eq(v1, v2);
}

START_TEST(sscanf_test4) {
  char str[] = "www5.3";
  char str1[100] = {0};
  char str2[100] = {0};

  float v1 = 0;
  float v2 = 0;
  s21_sscanf(str, "%s%f", str1, &v1);
  sscanf(str, "%s%f", str2, &v2);

  ck_assert_double_eq(v1, v2);
  ck_assert_str_eq(str1, str2);
}

START_TEST(sscanf_test5) {
  char str[] = {'A'};

  char v1;
  char v2;
  s21_sscanf(str, "%c", &v1);
  sscanf(str, "%c", &v2);

  ck_assert_int_eq(v1, v2);
}

START_TEST(sscanf_test6) {
  char str[] = {"45"};

  unsigned int v1 = 0;
  unsigned int v2 = 0;
  s21_sscanf(str, "%u", &v1);
  sscanf(str, "%u", &v2);

  ck_assert_uint_eq(v1, v2);

  char str1[] = {"-45"};
  s21_sscanf(str1, "%u", &v1);
  sscanf(str1, "%u", &v2);

  ck_assert_uint_eq(v1, v2);
}

START_TEST(sscanf_test8) {
  char str[] = {"1e+09"};

  float v1 = 0;
  float v2 = 0;
  s21_sscanf(str, "%g", &v1);
  sscanf(str, "%g", &v2);

  ck_assert_double_eq(v1, v2);

  char str1[] = {"1e-09"};

  v1 = 0;
  v2 = 0;
  s21_sscanf(str1, "%g", &v1);
  sscanf(str1, "%g", &v2);

  char str2[] = {"23"};

  v1 = 0;
  v2 = 0;
  s21_sscanf(str2, "%g", &v1);
  sscanf(str2, "%g", &v2);

  ck_assert_double_eq(v1, v2);
}

START_TEST(sscanf_test9) {
  char str[] = {"1e+09"};

  float v1 = 0;
  float v2 = 0;
  s21_sscanf(str, "%G", &v1);
  sscanf(str, "%G", &v2);

  ck_assert_double_eq(v1, v2);

  char str1[] = {"1e-09"};

  v1 = 0;
  v2 = 0;
  s21_sscanf(str1, "%G", &v1);
  sscanf(str1, "%G", &v2);

  char str2[] = {"23"};

  v1 = 0;
  v2 = 0;
  s21_sscanf(str2, "%G", &v1);
  sscanf(str2, "%G", &v2);

  ck_assert_double_eq(v1, v2);
}

START_TEST(sscanf_test10) {
  char str[] = "!!!!! 5.3 45";
  char str1[100] = {0};
  char str2[100] = {0};

  double v1 = 0;
  double v2 = 0;
  int dv1 = 0;
  int dv2 = 0;
  s21_sscanf(str, "%s%lf%d", str1, &v1, &dv1);
  sscanf(str, "%s%lf%d", str2, &v2, &dv2);

  ck_assert_double_eq(v1, v2);
  ck_assert_int_eq(dv1, dv2);
  ck_assert_str_eq(str1, str2);
}

START_TEST(sscanf_test11) {
  char str[] = "%!!!!! 5.3 45";
  // char str1[100] = {0};
  // char str2[100] = {0};

  int d1 = 0;
  int d2 = 0;
  s21_sscanf(str, "A%d 342", &d1);
  sscanf(str, "A%d 342", &d2);

  ck_assert_int_eq(d1, d2);
}

START_TEST(sscanf_test12) {
  char str[] = "045";

  short int hd1 = 0;
  short int hd2 = 0;

  s21_sscanf(str, "%hd", &hd1);
  sscanf(str, "%hd", &hd2);

  ck_assert_int_eq(hd1, hd2);

  long int ld1 = 0;
  long int ld2 = 0;

  s21_sscanf(str, "%ld", &ld1);
  sscanf(str, "%ld", &ld2);

  ck_assert_int_eq(ld1, ld2);

  long long lld1 = 0;
  long long lld2 = 0;

  s21_sscanf(str, "%lld", &lld1);
  sscanf(str, "%lld", &lld2);

  ck_assert_int_eq(lld1, lld2);

  long double Ld1 = 0;
  long double Ld2 = 0;

  s21_sscanf(str, "%Lf", &Ld1);
  sscanf(str, "%Lf", &Ld2);

  ck_assert_double_eq(Ld1, Ld2);
}

START_TEST(sscanf_test13) {
  char str[] = "045";

  int v1 = 0;
  int v2 = 0;

  s21_sscanf(str, "%i", &v1);
  sscanf(str, "%i", &v2);

  ck_assert_int_eq(v1, v2);

  s21_sscanf(str, "%x", &v1);
  sscanf(str, "%x", &v2);

  ck_assert_int_eq(v1, v2);

  char str2[] = "0x45";

  s21_sscanf(str2, "%i", &v1);
  sscanf(str2, "%i", &v2);

  ck_assert_int_eq(v1, v2);

  char str3[] = "-45";

  s21_sscanf(str3, "%i", &v1);
  sscanf(str3, "%i", &v2);

  ck_assert_int_eq(v1, v2);
}

SRunner *sscanf_test_runner() {
  TCase *cases = tcase_create("sscanf_case");

  tcase_add_test(cases, sscanf_test1);
  tcase_add_test(cases, sscanf_test2);
  tcase_add_test(cases, sscanf_test3);
  tcase_add_test(cases, sscanf_test4);
  tcase_add_test(cases, sscanf_test5);
  tcase_add_test(cases, sscanf_test6);
  tcase_add_test(cases, sscanf_test8);
  tcase_add_test(cases, sscanf_test9);
  tcase_add_test(cases, sscanf_test10);
  tcase_add_test(cases, sscanf_test11);
  tcase_add_test(cases, sscanf_test12);
  tcase_add_test(cases, sscanf_test13);

  Suite *suite = suite_create("sscanf_tests");
  suite_add_tcase(suite, cases);

  return srunner_create(suite);
}