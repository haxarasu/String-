#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  for (; i <= n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  return dest;
}