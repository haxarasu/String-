#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *otv = S21_NULL;
  s21_size_t stoper = 0;
  if (!*needle || *needle == '\0') {
    otv = (char *)haystack;
  } else {
    for (; stoper == 0 && *haystack; haystack++) {
      if (*haystack == needle[0]) {
        stoper = 1;
        otv = (char *)haystack;
      }
      for (s21_size_t i = 0; stoper == 1 && needle[i] != '\0'; i++) {
        if (*haystack == needle[i]) {
          haystack++;
        } else {
          stoper = 0;
          otv = S21_NULL;
          haystack++;
        }
      }
    }
  }
  return otv;
}
