#include "../s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* lastToken = S21_NULL;
  char* tokenStart = S21_NULL;
  char* tokenEnd = S21_NULL;
  if (str != S21_NULL) {
    lastToken = str;
  }
  if (lastToken != S21_NULL) {
    tokenStart = lastToken;
    while (*tokenStart != '\0' && s21_strchr(delim, *tokenStart) != S21_NULL) {
      tokenStart++;
    }
    if (*tokenStart == '\0') {
      lastToken = S21_NULL;
      tokenStart = S21_NULL;
    } else {
      tokenEnd = tokenStart;
      while (*tokenEnd != '\0' && s21_strchr(delim, *tokenEnd) == S21_NULL) {
        tokenEnd++;
      }
      if (*tokenEnd != '\0') {
        *tokenEnd = '\0';
        lastToken = tokenEnd + 1;
      } else {
        lastToken = S21_NULL;
      }
    }
  }

  return tokenStart;
}
