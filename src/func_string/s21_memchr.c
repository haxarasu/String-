#include "../s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  int check = 1;
  void* res = S21_NULL;
  for (s21_size_t i = 0; i < n && check; i++) {
    if (*(unsigned char*)(str + i) == c) {
      check = 0;
      res = (void*)(str + i);
    }
  }
  return res;
}