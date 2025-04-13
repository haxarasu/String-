#include <check.h>
#include <s21_string.h>
#include <stdio.h>
#include <stdlib.h>

SRunner *strlen_test_runner();
SRunner *strchr_test_runner();
SRunner *strncat_test_runner();
SRunner *strncpy_test_runner();
SRunner *strrchr_test_runner();
SRunner *strstr_test_runner();
SRunner *memchr_test_runner();
SRunner *memcmp_test_runner();
SRunner *memcpy_test_runner();
SRunner *strcspn_test_runner();
SRunner *memset_test_runner();
SRunner *strncmp_test_runner();
SRunner *strpbrk_test_runner();
SRunner *strtok_test_runner();
SRunner *strerror_test_runner();

SRunner *insert_test_runner();
SRunner *to_upper_test_runner();
SRunner *to_lower_test_runner();
SRunner *trim_test_runner();

SRunner *sprintf_test_runner();
SRunner *sscanf_test_runner();

int run_tests(SRunner *run) {
  srunner_run_all(run, CK_VERBOSE);

  int failed_count = srunner_ntests_failed(run);
  srunner_free(run);

  if (failed_count != 0) {
    printf("%s\n", "Tests run FAILURE!\n");
    return 0;
  }

  printf("\n");
  return 1;
}

int main() {
  run_tests(strlen_test_runner());
  run_tests(strchr_test_runner());
  run_tests(strncat_test_runner());
  run_tests(strncpy_test_runner());
  run_tests(strrchr_test_runner());
  run_tests(strstr_test_runner());
  run_tests(memchr_test_runner());
  run_tests(memcmp_test_runner());
  run_tests(memcpy_test_runner());
  run_tests(strcspn_test_runner());
  run_tests(memset_test_runner());
  run_tests(strncmp_test_runner());
  run_tests(strpbrk_test_runner());
  run_tests(strtok_test_runner());
  run_tests(strerror_test_runner());

  run_tests(insert_test_runner());
  run_tests(to_upper_test_runner());
  run_tests(to_lower_test_runner());
  run_tests(trim_test_runner());

  run_tests(sprintf_test_runner());
  run_tests(sscanf_test_runner());

  return EXIT_SUCCESS;
}