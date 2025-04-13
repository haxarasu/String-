#include <check.h>
#include <s21_string.h>
#include <string.h>

START_TEST(sprintf_test1) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "Digit %d\n", 23),
                   s21_sprintf(buffer2, "Digit %d\n", 23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "Digit %d\n", -23),
                   s21_sprintf(buffer2, "Digit %d\n", -23));

  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_int_eq(sprintf(buffer1, "Flag %%\n"),
                   s21_sprintf(buffer2, "Flag %%\n"));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%s %d\n", "Digit", 23),
                   s21_sprintf(buffer2, "%s %d\n", "Digit", 23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%s %d %c\n", "Digit", 23, 'A'),
                   s21_sprintf(buffer2, "%s %d %c\n", "Digit", 23, 'A'));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_test2_width) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%.23d\n", 23),
                   s21_sprintf(buffer2, "%.23d\n", 23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%d\n", -23),
                   s21_sprintf(buffer2, "%d\n", -23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_test3_precison_width) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%f\n", 23.563),
                   s21_sprintf(buffer2, "%f\n", 23.563));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%.3f\n", 23.563f),
                   s21_sprintf(buffer2, "%.3f\n", 23.563f));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%.9f\n", 0.5),
                   s21_sprintf(buffer2, "%.9f\n", 0.5));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%f\n", -23.2),
                   s21_sprintf(buffer2, "%f\n", -23.2));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_test3_unsigned_width) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%u\n", -23),
                   s21_sprintf(buffer2, "%u\n", -23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%.4u\n", -23),
                   s21_sprintf(buffer2, "%.4u\n", -23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%u\n", 23),
                   s21_sprintf(buffer2, "%u\n", 23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_test4_flags) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%+d\n", -23),
                   s21_sprintf(buffer2, "%+d\n", -23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%-u\n", -23),
                   s21_sprintf(buffer2, "%-u\n", -23));

  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_int_eq(sprintf(buffer1, "% d", 2), s21_sprintf(buffer2, "% d", 2));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "'%-5d'\n", 42),
                   s21_sprintf(buffer2, "'%-5d'\n", 42));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%-3u\n", -23),
                   s21_sprintf(buffer2, "%-3u\n", -23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_test5_trash) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%+d\n", 23),
                   s21_sprintf(buffer2, "%+d\n", 23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%+d\n", -23),
                   s21_sprintf(buffer2, "%+d\n", -23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%-d\n", -23),
                   s21_sprintf(buffer2, "%-d\n", -23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_test6_trash) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%20d\n", 23),
                   s21_sprintf(buffer2, "%20d\n", 23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%.4lf\n", 23.2),
                   s21_sprintf(buffer2, "%.4lf\n", 23.2));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%.4hd\n", 23),
                   s21_sprintf(buffer2, "%.4hd\n", 23));
  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%hd\n", 23),
                   s21_sprintf(buffer2, "%hd\n", 23));
  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%ld\n", 2334534534523453425),
                   s21_sprintf(buffer2, "%ld\n", 2334534534523453425));
  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_spec_g) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%g\n", 23.0),
                   s21_sprintf(buffer2, "%g\n", 23.0));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_spec_G) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%G\n", 23.0),
                   s21_sprintf(buffer2, "%G\n", 23.0));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_spec_e) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%e\n", 23.0),
                   s21_sprintf(buffer2, "%e\n", 23.0));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_spec_E) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%E\n", 23.0),
                   s21_sprintf(buffer2, "%E\n", 23.0));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_spec_x) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%x\n", 23),
                   s21_sprintf(buffer2, "%x\n", 23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_spec_X) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%X\n", 23),
                   s21_sprintf(buffer2, "%X\n", 23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_spec_o) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%o\n", 23),
                   s21_sprintf(buffer2, "%o\n", 23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_spec_p) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  char str[] = "A";
  void *ptr = &str;
  ck_assert_int_eq(sprintf(buffer1, "%p\n", ptr),
                   s21_sprintf(buffer2, "%p\n", ptr));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_flag_1) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%#x\n", 23),
                   s21_sprintf(buffer2, "%#x\n", 23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%#o\n", 23),
                   s21_sprintf(buffer2, "%#o\n", 23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%#e\n", 23.23),
                   s21_sprintf(buffer2, "%#e\n", 23.23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%#E\n", 23.23),
                   s21_sprintf(buffer2, "%#E\n", 23.23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%#g\n", 23.23),
                   s21_sprintf(buffer2, "%#g\n", 23.23));

  ck_assert_str_eq(buffer1, buffer2);

  s21_memset(buffer1, 0x00, 100);
  s21_memset(buffer2, 0x00, 100);

  ck_assert_int_eq(sprintf(buffer1, "%#G\n", 23.23),
                   s21_sprintf(buffer2, "%#G\n", 23.23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_flag_0) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%04d\n", 23),
                   s21_sprintf(buffer2, "%04d\n", 23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_width) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%*d\n", 4, 23),
                   s21_sprintf(buffer2, "%*d\n", 4, 23));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_precision) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  ck_assert_int_eq(sprintf(buffer1, "%.*f\n", 4, 0.5),
                   s21_sprintf(buffer2, "%.*f\n", 4, 0.5));

  ck_assert_str_eq(buffer1, buffer2);
}

START_TEST(sprintf_bonus_long) {
  char buffer1[100] = {0};
  char buffer2[100] = {0};

  long double v = 0.54353453453345345;
  sprintf(buffer1, "%Lf\n", v);
  s21_sprintf(buffer2, "%Lf\n", v);

  ck_assert_str_eq(buffer1, buffer2);
}

SRunner *sprintf_test_runner() {
  Suite *suite = suite_create("sprintf_tests");

  TCase *cases = tcase_create("sprintf_case");
  tcase_add_test(cases, sprintf_test1);
  tcase_add_test(cases, sprintf_test2_width);
  tcase_add_test(cases, sprintf_test3_precison_width);
  tcase_add_test(cases, sprintf_test3_unsigned_width);
  tcase_add_test(cases, sprintf_test4_flags);
  tcase_add_test(cases, sprintf_test5_trash);
  tcase_add_test(cases, sprintf_test6_trash);
  suite_add_tcase(suite, cases);

  // Тесты на спецификаторы g, G, e, E, x, X, o, p
  TCase *bonus_spec_case = tcase_create("sprintf_bonus_spec_case");
  tcase_add_test(bonus_spec_case, sprintf_bonus_spec_e);
  tcase_add_test(bonus_spec_case, sprintf_bonus_spec_E);
  tcase_add_test(bonus_spec_case, sprintf_bonus_spec_g);
  tcase_add_test(bonus_spec_case, sprintf_bonus_spec_G);
  tcase_add_test(bonus_spec_case, sprintf_bonus_spec_x);
  tcase_add_test(bonus_spec_case, sprintf_bonus_spec_X);
  tcase_add_test(bonus_spec_case, sprintf_bonus_spec_o);
  tcase_add_test(bonus_spec_case, sprintf_bonus_spec_p);
  suite_add_tcase(suite, bonus_spec_case);

  // Тесты на флаги #, O
  TCase *bonus_flags_case = tcase_create("sprintf_bonus_flags_case");
  tcase_add_test(bonus_flags_case, sprintf_bonus_flag_1);
  tcase_add_test(bonus_flags_case, sprintf_bonus_flag_0);
  tcase_add_test(bonus_flags_case, sprintf_bonus_width);
  tcase_add_test(bonus_flags_case, sprintf_bonus_precision);
  tcase_add_test(bonus_flags_case, sprintf_bonus_long);

  suite_add_tcase(suite, bonus_flags_case);

  return srunner_create(suite);
}
