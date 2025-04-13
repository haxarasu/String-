#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t len = 0;
  for (; dest[len]; len++) {
    ;
  }
  for (s21_size_t i = 0; i < n && *src; src++, len++, i++) {
    dest[len] = *src;
  }
  return dest;
}
