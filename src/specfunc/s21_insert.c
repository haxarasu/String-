#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t startIndex) {
  s21_size_t sizSrc = s21_strlen(src);
  s21_size_t sizStr = s21_strlen(str);
  char *result = S21_NULL;
  if (src == S21_NULL || str == S21_NULL || startIndex > s21_strlen(src)) {
    result = S21_NULL;
  } else {
    result = (char *)calloc(sizSrc + sizStr + 1, sizeof(char));
    if (!result) {
      free(result);
      result = S21_NULL;
    } else {
      s21_strncpy(result, src, startIndex);
      s21_strncpy(result + startIndex, str, sizStr);
      s21_strncpy(result + startIndex + sizStr, src + startIndex,
                  sizSrc - startIndex);
    }
  }
  return result;
}