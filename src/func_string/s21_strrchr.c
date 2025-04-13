#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *otv = S21_NULL;
  if (str != S21_NULL) {
    while (*str) {
      if (*str == c) {
        otv = (char *)str;
      }
      str++;
    }
    if (c == '\0') {
      otv = (char *)str;
    }
    if (*str != '\0') {
      otv = (char *)str;
    }
  }
  return otv;
}
