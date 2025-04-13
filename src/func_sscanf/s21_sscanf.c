#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int file_eof = is_eof(str);
  int res = 0;

  if (!file_eof) {
    va_list va;
    va_start(va, format);
    int tokens_len = 0;

    char *formstr = (char *)format;
    int len = (int)s21_strlen(formstr);
    char *src = (char *)str;

    token tokens[BUFF];

    while (*formstr && formstr < format + len && tokens_len < BUFF) {
      tokens[tokens_len] = parse_tokens(&formstr, &va);
      tokens_len++;
    }

    tokens_to_mem(&src, tokens, tokens_len, &res);
    va_end(va);
  }

  return (file_eof) ? file_eof : res;
}

int is_eof(const char *src) {
  int res = -1;
  // тут ||res
  for (int i = 0; src[i]; i++) {
    if (!c_isspace(src[i]) && src[i] != '\0') {
      res = 0;
      break;
    }
  }

  return res;
}

int c_isspace(char c) { return (c == ' ' || c == '\n' || c == '\t'); }

int c_isalpha(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

token parse_tokens(char **format, va_list *va) {
  token tok = {.addr = S21_NULL,
               .length_t = NONE_LENGTH,
               .spec = 0,
               .width = NONE_WIDTH,
               .width_n = 0};

  if (c_isspace(**format)) {
    tok.spec = 'z';
    skip_space(format);
  }

  if (**format == '%' && !tok.spec) {
    (*format)++;

    if (**format == '%') {
      s21_memset(tok.buff, '\0', BUFF - 1);
      tok.buff[0] = '%';
      (*format)++;
      tok.spec = 'b';
    } else {
      format_parse_width(format, &tok);
      format_parse_length(format, &tok);
      format_parse_specifier(format, &tok);

      if (tok.width != WIDTH_AST) tok.addr = va_arg(*va, void *);
    }

    if (tok.spec == 'p') tok.length_t = NONE_LENGTH;
  }

  if (c_isalpha(**format) && !tok.spec) {
    s21_memset(tok.buff, '\0', BUFF - 1);
    int i = 0;
    while (**format && !c_isspace(**format) && **format != '%') {
      tok.buff[i++] = **format;
      (*format)++;
    }
    tok.spec = 'b';
  }

  return tok;
}

void skip_chars_in_buff(char **src, int *fail, token *tok) {
  int test = s21_strspn(*src, tok->buff);
  int len = s21_strlen(tok->buff);

  if (len == 1 && **src == tok->buff[0]) {
    (*src) = (*src) + len;
    return;
  }

  if (test != len)
    *fail = 1;
  else
    (*src) = (*src) + len;
}

void format_parse_width(char **format, token *tok) {
  if (**format == '*') {
    (*format)++;
    tok->width = WIDTH_AST;
  } else {
    int res = parse_number_from_format(format);

    if (res) {
      tok->width = WIDTH_NUMBER;
      tok->width_n = res;
    }
  }
}

int parse_number_from_format(char **format) {
  char tmp[BUFF] = {'\0'};

  int res = 0;
  int i = 0;

  while (**format >= '0' && **format <= '9') {
    tmp[i] = **format;
    (*format)++;
    i++;
  }

  res = s21_atoi(tmp);

  return res;
}

void format_parse_length(char **format, token *tok) {
  switch (**format) {
    case 'h':
      tok->length_t = LENGTH_SHORT;
      (*format)++;
      break;
    case 'l':
      tok->length_t = LENGTH_LONG;
      (*format)++;
      if (**format == 'l') {
        tok->length_t = LENGTH_LONG_LONG;
        (*format)++;
      }
      break;
    case 'L':
      tok->length_t = LENGTH_LONG_DOUBLE;
      (*format)++;
      break;
  }
}

void format_parse_specifier(char **format, token *tok) {
  tok->spec = (**format);
  (*format)++;
}

void tokens_to_mem(char **src, token *tokens, int tokens_len, int *res) {
  char *start = *src;

  for (int i = 0, fail = 0; i < tokens_len && !fail; i++) {
    skip_space(src);
    char spec = tokens[i].spec;
    if (spec == 'c') char_to_mem(src, res, (tokens + i), &fail);
    if (spec == 'd') int_to_mem(src, &fail, res, (tokens + i));
    if (spec == 'i' || spec == 'p')
      unspec_int_to_mem(src, &fail, res, (tokens + i));
    if (spec == 'g' || spec == 'G' || spec == 'f')
      float_to_mem(src, res, (tokens + i));
    if (spec == 's') string_to_mem(src, &fail, res, (tokens + i));
    if (spec == 'u') unsigned_to_mem(src, &fail, res, (tokens + i));
    if (spec == 'x' || spec == 'X')
      hexoct_to_mem(src, &fail, res, (tokens + i), 16);
    if (spec == 'o') hexoct_to_mem(src, &fail, res, (tokens + i), 8);
    if (spec == 'n') *((int *)tokens[i].addr) = (*src) - start;
    if (spec == 'z') skip_space(src);
    if (spec == 'b') skip_chars_in_buff(src, &fail, (tokens + i));
  }
}

void skip_space(char **src) {
  while (**src && c_isspace(**src)) {
    (*src)++;
  }
}

void char_to_mem(char **str, int *res, token *tok, int *fail) {
  *fail = 1;
  while (**str) {
    *fail = 0;
    if (tok->width == WIDTH_AST) {
      (*str)++;
      break;
    } else {
      *(char *)tok->addr = **str;
      (*str)++;
      (*res)++;
      break;
    }
  }
}

void int_to_mem(char **str, int *fail, int *res, token *tok) {
  long long int result = 0;
  char buff[BUFF] = {'\0'};

  *fail = 1;

  if (s21_strspn(*str, "0123456789+-")) {
    int sign = s21_strspn(*str, "+-");
    if (!(sign > 1 || (sign && (tok->width_n <= 1 && tok->width)))) {
      buff[0] = **str;
      (*str)++;
      chars_to_buff(str, "0123456789", buff, tok->width_n, 1);
      if (tok->width != WIDTH_AST) (*res)++;
      *fail = 0;
    }
  }

  result = s21_atoi(buff);

  if (tok->spec == 'p' && tok->width != WIDTH_AST && !*fail) {
    unsigned long long int ress =
        s21_strntollu(buff, S21_NULL, 16, s21_strlen(buff));
    *(int *)tok->addr = (int)ress;
  } else {
    if (tok->width != WIDTH_AST && !*fail) int_type_converter(tok, result, 1);
  }

  if (tok->width != WIDTH_NUMBER)
    chars_to_buff(str, "0123456789", S21_NULL, 0, 0);
}

void unspec_int_to_mem(char **str, int *fail, int *res, token *tok) {
  *fail = 1;
  skip_space(str);

  if (s21_strspn(*str, "0x") == 2) {
    *fail = 0;
    hexoct_to_mem(str, fail, res, tok, 16);
  } else if (s21_strspn(*str, "0") == 1) {
    *fail = 0;
    hexoct_to_mem(str, fail, res, tok, 8);
  } else if (s21_strspn(*str, "+-0123456789")) {
    *fail = 0;
    int_to_mem(str, fail, res, tok);
  }
}

void chars_to_buff(char **str, const char *chars, char *buff, int16_t width,
                   int start_index) {
  while (**str && s21_strspn(*str, chars) != 0) {
    if ((width && start_index >= width) || (c_isspace(**str))) break;

    if (buff) buff[start_index] = **str;

    (*str)++;
    start_index++;
  }
}

void float_to_mem(char **str, int *res, token *tok) {
  int test = 0;

  if (tok->spec == 'f')
    test = s21_strspn(*str, "0123456789+-");
  else
    test = s21_strspn(*str, "0123456789eE+-NnaAifIF");

  if (test) {
    int sign = s21_strspn(*str, "+-");
    if (!(sign > 1 || (sign && (tok->width_n <= 1 && tok->width)))) {
      char buff[BUFF] = {'\0'};
      int start_index = 0;
      if (sign) {
        buff[0] = **str;
        start_index = 1;
        (*str)++;
      }

      if (tok->spec == 'f')
        chars_to_buff(str, ".0123456789+-", buff, tok->width_n, start_index);
      else
        chars_to_buff(str, ".0123456789eE+-NnaAifIF", buff, tok->width_n,
                      start_index);

      if (tok->width != WIDTH_AST) {
        long double result = s21_strtold(buff);
        (*res)++;
        float_type_converter(tok, result);
      }
    }
  }

  if (tok->width != WIDTH_NUMBER) {
    if (tok->spec == 'f')
      chars_to_buff(str, ".0123456789+-", S21_NULL, 0, 0);
    else
      chars_to_buff(str, ".0123456789eE+-NnaAifIF", S21_NULL, 0, 0);
  }
}

void string_to_mem(char **str, const int *fail, int *res, token *tok) {
  int succ = 0;
  char buff[BUFF] = {'\0'};
  unsigned int i = 0;

  while (**str != '\0' && !succ && !(*fail)) {
    if (!c_isspace(**str)) {
      succ = 1;
      while (**str != '\0' && !(*fail)) {
        buff[i] = **str;
        i++;

        if (tok->width == WIDTH_NUMBER && i >= tok->width_n) {
          break;
        }

        (*str)++;

        if (c_isspace(**str)) {
          (*str)--;
          break;
        }
      }
    }

    (*str)++;
  }

  if (tok->width != WIDTH_AST && succ) {
    s21_strcpy((char *)tok->addr, buff);
    (*res)++;
  }
}

void unsigned_to_mem(char **str, int *fail, int *res, token *tok) {
  *fail = 1;
  skip_space(str);
  char buff[BUFF] = {'\0'};

  if (s21_strspn(*str, "0123456789+-")) {
    int sign = s21_strspn(*str, "+-");
    if (!((sign > 1 || (sign && (tok->width_n <= 1 && tok->width))))) {
      *fail = 0;
      buff[0] = **str;
      (*str)++;

      chars_to_buff(str, "0123456789", buff, tok->width_n, 1);

      if (tok->width != WIDTH_AST) (*res)++;
    }
  }

  unsigned long long int result = s21_atoi(buff);

  if (tok->width != WIDTH_AST && !*fail)
    unsigned_type_converter(tok, result, 1);

  if (tok->width != WIDTH_NUMBER)
    chars_to_buff(str, "0123456789", S21_NULL, 0, 0);
}

void hexoct_to_mem(char **str, int *fail, int *res, token *tok, int base) {
  int sign = 1;
  char *ptr = S21_NULL;
  if (tok->spec == 'p') base = 16;

  skip_space(str);
  if (**str == '-') {
    tok->width_n--;
    sign = -1;
    (*str)++;
  }
  if (base == 16 && **str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X'))
    tok->width_n -= 2;

  if (s21_strspn(*str, "0123456789abcdefABCDEF") > 0 ||
      s21_strspn(*str, "xX0123456789abcdefABCDEF") >= 2) {
    unsigned long long int result = s21_strntollu(
        *str, &ptr, base, tok->width ? tok->width_n : s21_strlen(*str));
    if (tok->width != WIDTH_AST) {
      *res += 1;

      if (tok->spec == 'p')
        *(int *)tok->addr = (int)result;
      else
        unsigned_type_converter(tok, result, sign);
    }
  } else {
    *fail = 1;
  }
  unsigned int max = (unsigned int)s21_strspn(*str, "xX0123456789abcdefABCDEF");

  if (tok->width != WIDTH_NUMBER)
    *str += max;
  else
    *str += max < tok->width_n ? max : tok->width_n;
}

void unsigned_type_converter(token *tok, unsigned long long int result,
                             int sign) {
  if (tok->length_t == NONE_LENGTH) {
    *(unsigned int *)tok->addr = sign * (unsigned int)result;
  } else if (tok->length_t == LENGTH_SHORT) {
    *(unsigned short int *)tok->addr = sign * (unsigned short int)result;
  } else if (tok->length_t == LENGTH_LONG) {
    *(unsigned long int *)tok->addr = sign * (unsigned long int)result;
  } else if (tok->length_t == LENGTH_LONG_LONG) {
    *(unsigned long long int *)tok->addr =
        sign * (unsigned long long int)result;
  }
}

void int_type_converter(token *tok, long long int result, int sign) {
  if (tok->spec != 'p') {
    if (tok->length_t == NONE_LENGTH) {
      *(int *)tok->addr = sign * (int)result;
    } else if (tok->length_t == LENGTH_SHORT) {
      *(short int *)tok->addr = sign * (short int)result;
    } else if (tok->length_t == LENGTH_LONG) {
      *(long int *)tok->addr = sign * (long int)result;
    } else if (tok->length_t == LENGTH_LONG_LONG) {
      *(long long int *)tok->addr = sign * (long long int)result;
    }
  }
}

void float_type_converter(token *tok, long double result) {
  if (tok->length_t == NONE_LENGTH) *(float *)tok->addr = (float)result;
  if (tok->length_t == LENGTH_LONG) *(double *)tok->addr = (double)result;
  if (tok->length_t == LENGTH_LONG_DOUBLE)
    *(long double *)tok->addr = (long double)result;
}