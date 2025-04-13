#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t ctr = 0;
  for (s21_size_t i = 0; i < n; i++) {
    ctr = str1[i] - str2[i];
    if (ctr != 0) {
      i = n;
    }
  }
  return ctr;
}
