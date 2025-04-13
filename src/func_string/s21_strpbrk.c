#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *ptr = S21_NULL;
  s21_size_t point = 0;
  if (str1 != S21_NULL && str2 != S21_NULL) {
    for (s21_size_t i = 0; str1[i] != '\0'; i++) {
      for (s21_size_t j = 0; str2[j] != '\0' && point == 0; j++) {
        if (str1[i] == str2[j]) {
          ptr = (char *)&str1[i];
          point = 1;
        }
      }
    }
  }
  return ptr;
}
