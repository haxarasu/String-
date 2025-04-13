#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *otv = S21_NULL;
  if (str != S21_NULL) {
    for (; *str && *str != c; str++) {
      ;
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
