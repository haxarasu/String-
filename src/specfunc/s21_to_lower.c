#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  char *lowerStr = S21_NULL;
  if (str == S21_NULL) {
    lowerStr = S21_NULL;
  } else {
    s21_size_t lenStr = s21_strlen(str);
    lowerStr = (char *)calloc(lenStr + 1, sizeof(char));
    if (lowerStr == S21_NULL) {
      free(lowerStr);
      lowerStr = S21_NULL;
    } else {
      for (s21_size_t i = 0; i < lenStr; i++) {
        char chStr = str[i];
        if (chStr >= 'A' && chStr <= 'Z') {
          lowerStr[i] = chStr + ('a' - 'A');
        } else {
          lowerStr[i] = chStr;
        }
      }
    }
  }
  return lowerStr;
}
