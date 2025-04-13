#include "../s21_string.h"

void *s21_trim(const char *src, const char *trimChars) {
  char *result = S21_NULL;
  s21_size_t start = 0;
  s21_size_t end = s21_strlen(src) - 1;
  if (src != S21_NULL && trimChars != S21_NULL) {
    while (s21_strchr(trimChars, src[start]) != S21_NULL && start < end) {
      start++;
    }
    if (start == end) {
      result = calloc(1, sizeof(char));
      if (result != S21_NULL) {
        result[0] = '\0';
      }
    } else {
      while (s21_strchr(trimChars, src[end]) != S21_NULL && end > start) {
        end--;
      }
      result = (char *)calloc(end - start + 2, sizeof(char));
      if (result != S21_NULL) {
        s21_size_t countRes = 0;
        for (; start <= end; start++, countRes++) {
          result[countRes] = src[start];
        }
        result[countRes] = '\0';
      }
    }
  } else if (trimChars == S21_NULL) {
    s21_size_t len = 0;
    result = (char *)calloc(s21_strlen(src) + 1, sizeof(char));
    for (; src[len] != '\0'; len++) result[len] = src[len];
    result[len] = '\0';
  }
  return result;
}