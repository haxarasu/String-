#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;

  int dif = 0;

  for (size_t i = 0; i < n && dif == 0; i++) {
    dif = (int)(s1[i] - s2[i]);
  }
  return dif;
}