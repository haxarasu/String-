#include "../s21_string.h"
#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_

#define BUFF 512

typedef enum width_t { NONE_WIDTH, WIDTH_NUMBER, WIDTH_AST } width_t;

typedef enum length_t {
  NONE_LENGTH,
  LENGTH_SHORT,
  LENGTH_LONG,
  LENGTH_LONG_LONG,
  LENGTH_DOUBLE,
  LENGTH_LONG_DOUBLE
} length_t;

typedef struct token {
  void *addr;
  width_t width;
  unsigned int width_n;

  length_t length_t;

  char buff[512];
  char spec;
} token;

int is_eof(const char *src);
void chars_to_buff(char **str, const char *chars, char *buff, int16_t width,
                   int start_ind);
unsigned long long int s21_strntollu(const char *string, char **endptr,
                                     int basis, int n_byte);
long double s21_strtold(const char *buffer);
char *s21_strcpy(char *dest, const char *src);
s21_size_t s21_strspn(const char *str1, const char *str2);
int s21_atoi(const char *str);
int c_isspace(char c);
void unsigned_type_converter(token *tok, unsigned long long int result,
                             int sign);
void int_type_converter(token *tok, long long int result, int sign);
void float_type_converter(token *tok, long double result);
int c_isalpha(char c);

token parse_tokens(char **format, va_list *va);
void format_parse_width(char **format, token *tok);
void format_parse_length(char **format, token *tok);
void format_parse_specifier(char **format, token *tok);
int parse_number_from_format(char **format);

void format_parse_buffer(char **fstr, token *tok);
void skip_space(char **src);
void skip_chars_in_buff(char **src, int *fail, token *tok);

void tokens_to_mem(char **src, token *tokens, int tok_len, int *res);
void char_to_mem(char **str, int *res, token *tok, int *fail);
void int_to_mem(char **str, int *fail, int *res, token *tok);
void unspec_int_to_mem(char **str, int *fail, int *res, token *tok);
void float_to_mem(char **str, int *res, token *tok);
void string_to_mem(char **str, const int *fail, int *res, token *tok);
void unsigned_to_mem(char **str, int *fail, int *res, token *tok);
void hexoct_to_mem(char **str, int *fail, int *res, token *tok, int base);

#endif