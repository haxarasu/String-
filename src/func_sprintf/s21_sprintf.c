#include "s21_sprintf.h"

argsTypes change_types(const char *p, va_list args, struct lenghtTypes *ltype) {
  argsTypes value = {0};

  if (ltype->symbolsh == 1) {
    if (*p == 'd' || *p == 'i') {
      value.halfType = (short int)va_arg(args, int);
    } else if (*p == 'u' || *p == 'o' || *p == 'x' || *p == 'X') {
      value.unsignedHalfType = (unsigned short)va_arg(args, unsigned int);
    }
  } else if (ltype->symbolsl == 1) {
    if (*p == 'd' || *p == 'i') {
      value.longType = (long int)va_arg(args, long int);
    } else if (*p == 'u' || *p == 'x' || *p == 'X' || *p == 'o') {
      value.unsignedLongType = (long)va_arg(args, unsigned long);
    } else if (*p == 'g' || *p == 'G' || *p == 'e' || *p == 'E' || *p == 'f') {
      value.standDoubleType = va_arg(args, double);
    } else if (*p == 'c' || *p == 's') {
      value.wchartType = va_arg(args, wchar_t *);
    }
  } else if (ltype->symbolsL == 1) {
    if (*p == 'g' || *p == 'G' || *p == 'e' || *p == 'E' || *p == 'f') {
      value.longDoubleType = va_arg(args, long double);
    }
  } else {
    if (*p == 'd' || *p == 'i') {
      value.standIntType = va_arg(args, int);
    } else if (*p == 'u' || *p == 'x' || *p == 'X' || *p == 'o') {
      value.unsignedIntType = va_arg(args, unsigned int);
    } else if (*p == 'g' || *p == 'G' || *p == 'e' || *p == 'E' || *p == 'f') {
      value.standDoubleType = va_arg(args, double);
    } else if (*p == 'c') {
      value.charType = (char)va_arg(args, int);
    } else if (*p == 's') {
      value.stringType = (char *)va_arg(args, char *);
    }
  }
  return value;
}

void get_length_type(const char **p, struct lenghtTypes *ltype) {
  while (**p == 'h' || **p == 'l' || **p == 'L') {
    switch (**p) {
      case 'h':
        ltype->symbolsh = 1;
        break;
      case 'l':
        ltype->symbolsl = 1;
        break;
      case 'L':
        ltype->symbolsL = 1;
        break;
    }
    (*p)++;
  }
}

void get_flag(const char **p, struct flag *cfg) {
  while (**p == '+' || **p == '-' || **p == ' ' || **p == '*' || **p == '0' ||
         **p == '#') {
    switch (**p) {
      case '+':
        cfg->plus_flag = 1;
        break;
      case '-':
        cfg->minus_flag = 1;
        break;
      case ' ':
        cfg->space_flag = 1;
        break;
      case '*':
        cfg->width_flag = 1;
        break;
      case '0':
        cfg->flag_zero = 1;
        break;
      case '#':
        cfg->sharp_flag = 1;
        break;
    }
    (*p)++;
  }
}

int fl_plus(char **buffer, int i) {
  (*buffer)[i++] = '+';
  return i;
}
int fl_space(char **buffer, int i) {
  (*buffer)[i++] = ' ';
  return i;
}
int fl_minus(char **buffer, int i, int width) {
  while (i < width) {
    (*buffer)[i++] = ' ';
  }
  return i;
}

int parseInteger(const char *str, int *val) {
  int result = 0;
  int isNegative = 0;
  const char *sptr = str;
  while (*str == ' ') {
    str++;
  }
  if (*str == '-') {
    isNegative = 1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }
  if (isNegative) {
    result = -result;
  }

  *val = result;

  return str - sptr;
}

int get_width(const char **p) {
  int width = 0;
  while (**p >= '0' && **p <= '9') {
    width = width * 10 + (**p - '0');
    (*p)++;
  }
  return width;
}

void reverse(char *str, int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

long double l_round_to_decimal(long double value, int decimal_places) {
  long double factor = powf(10.0, decimal_places);
  return roundl(value * factor) / factor;
}

float f_round_to_decimal(float value, int decimal_places) {
  float factor = powf(10.0f, decimal_places);
  return roundf(value * factor) / factor;
}

int string_help_round(long double value, int precision) {
  long ipart = (long)value;
  double fp = value - ipart;
  char data[256];
  int i = 0;
  int res;
  int fd = (int)(fp * pow(10, precision) + 0.1);
  do {
    data[i++] = (fd % 10) + '0';
    fd /= 10;
  } while (fd > 0);
  if (data[0] == '0') {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

long double checker_precision(long double value, int precision,
                              struct lenghtTypes *ltype) {
  if (precision == 0) {
    value = round(value);
  } else if (ltype->symbolsL) {
    value = l_round_to_decimal(value, precision);
  } else if (string_help_round(value, precision) == 0) {
    value = f_round_to_decimal(value, precision);
  }
  return value;
}

int checker_flag(struct flag *cfg, char **buffer, int i) {
  if (cfg->Negative) {
    (*buffer)[i++] = '-';
  } else if (cfg->plus_flag) {
    i = fl_plus(buffer, i);
  } else if (cfg->space_flag == 1 && cfg->plus_flag == 0) {
    i = fl_space(buffer, i);
  }
  return i;
}

int double_to_string(char **buffer, long double value, int precision,
                     struct flag *cfg, int width, struct lenghtTypes *ltype) {
  value = checker_precision(value, precision, ltype);
  long intPart = (long)value;
  double fractionalPart = value - intPart;
  int i = 0;
  int fractionalDigit = (int)(fractionalPart * pow(10, precision) + 0.1);
  int fd1 = fractionalDigit;
  if (intPart == 0 && fractionalDigit == 0) {
    (*buffer)[i++] = '0';
    if (precision != 0) {
      (*buffer)[i++] = '.';
    }
    for (int j = 0; j < precision; j++) {
      (*buffer)[i++] = '0';
    }
  } else {
    if (precision != 0) {
      if (fractionalDigit == 0)
        for (int j = 0; j < precision; j++) {
          (*buffer)[i++] = '0';
        }
      else {
        do {
          (*buffer)[i++] = (fractionalDigit % 10) + '0';
          fractionalDigit /= 10;
        } while (fractionalDigit > 0);
        int fp = pow(10, precision) / fd1;
        int zero_count = 0;
        do {
          fp /= 10;
          zero_count++;
        } while (fp > 1);

        for (int i1 = 0; i1 < zero_count - 1; i1++) (*buffer)[i++] = '0';
      }
      (*buffer)[i++] = '.';
    }
    do {
      (*buffer)[i++] = (intPart % 10) + '0';
      intPart /= 10;
    } while (intPart > 0);
    i = checker_flag(cfg, buffer, i);
    reverse(*buffer, i);
    if (width > i && cfg->minus_flag == 1) {
      i = fl_minus(buffer, i, width);
    }
  }
  return i;
}

int int_to_string(long int num, char **str, int base, int width,
                  struct flag *cfg) {
  int i = 0;
  if (num < 0 && base == 10) {
    cfg->Negative = 1;
    num = -num;
  }

  do {
    int remainder = num % base;
    (*str)[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
    num /= base;
  } while (num != 0);
  i = checker_flag(cfg, str, i);

  reverse(*str, i);

  if (width != -1) {
    int dlen = i;
    if (cfg->Negative) dlen = dlen - 1;
    if (width > i && cfg->minus_flag == 1 && cfg->point == 0) {
      i = fl_minus(str, i, width);
    } else if (cfg->Negative) {
      while (i <= width) (*str)[i++] = '0';
    } else {
      while (i < width) (*str)[i++] = '0';
    }
    char tmpd[dlen];
    char *offset_str = *str;
    if (cfg->Negative) offset_str = offset_str + 1;
    s21_memcpy(tmpd, offset_str, dlen);
    s21_memset(offset_str, '0', i);
    if (cfg->Negative)
      offset_str += (i - dlen) - 1;
    else
      offset_str += (i - dlen);
    s21_memcpy(offset_str, tmpd, dlen);
  }
  return i;
}

int uint_to_string(unsigned int num, char **str, int base, int width,
                   struct flag *cfg) {
  int i = 0;

  do {
    int remainder = num % base;
    (*str)[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
    num /= base;
  } while (num != 0);
  reverse(*str, i);

  if (width != -1) {
    int dlen = i;

    if (width > i && cfg->minus_flag == 1 && cfg->point == 0) {
      i = fl_minus(str, i, width);
    } else {
      while (i < width) (*str)[i++] = '0';
    }

    char tmpd[dlen];
    char *offset_str = (*str);

    s21_memcpy(tmpd, offset_str, dlen);
    s21_memset(offset_str, '0', i);
    offset_str += (i - dlen);

    s21_memcpy(offset_str, tmpd, dlen);
  }

  return i;
}

void set_width(char **str, int width, int long_number, struct flag *cfg) {
  if (width < 0) width = width * (-1);
  if (width > long_number) {
    if (!cfg->minus_flag) {
      *str -= long_number;
      int space_col = width - long_number;
      char *tmp = malloc(sizeof(char) * long_number);
      s21_memcpy(tmp, *str, long_number);
      if (cfg->flag_zero) {
        s21_memset(*str, '0', space_col);
      } else {
        s21_memset(*str, ' ', space_col);
      }
      *str += space_col;
      s21_memcpy(*str, tmp, long_number);
      *str += long_number;
      free(tmp);
    }
    if (cfg->minus_flag) {
      int space_col = width - long_number;
      s21_memset(*str, ' ', space_col);
      *str += space_col;
    }
  }
}

void set_width_for_str(char **str, int width, int len_str, void *data,
                       struct flag *cfg) {
  if (width > len_str) {
    if (!cfg->minus_flag) {
      s21_size_t col_space = width - len_str;
      s21_memset(*str, ' ', col_space);
      *str += col_space;
      s21_memcpy(*str, data, len_str);
      *str += len_str;
    } else if (cfg->minus_flag) {
      s21_size_t col_space = width - len_str;
      s21_memcpy(*str, data, len_str);
      *str += len_str;
      s21_memset(*str, ' ', col_space);
      *str += col_space;
    }
  } else {
    s21_memcpy(*str, data, len_str);
    *str += len_str;
  }
}

int format_exponent(char **buffer, struct flag *cfg, int exponent, int i) {
  i = checker_flag(cfg, buffer, i);
  reverse(*buffer, i);
  if (cfg->small_e) {
    (*buffer)[i++] = 'e';
  } else {
    (*buffer)[i++] = 'E';
  }
  if (exponent < 0) {
    exponent = -exponent;
    (*buffer)[i++] = '-';
  } else {
    (*buffer)[i++] = '+';
  }
  if (exponent < 10) {
    (*buffer)[i++] = '0';
    (*buffer)[i++] = exponent + '0';
  } else {
    int tempExponent = exponent;
    char tempExp[4];
    int expIndex = 0;
    while (tempExponent > 0) {
      tempExp[expIndex++] = (tempExponent % 10) + '0';
      tempExponent /= 10;
    }
    tempExp[expIndex] = '\0';
    for (int j = expIndex - 1; j >= 0; j--) {
      (*buffer)[i++] = tempExp[j];
    }
  }
  return i;
}

int scientific_zero(char **buffer, int i, struct flag *cfg, int precision) {
  (*buffer)[i++] = '0';
  if (precision != 0) {
    (*buffer)[i++] = '.';
    for (int j = 0; j < precision; j++) {
      (*buffer)[i++] = '0';
    }
  }
  if (cfg->small_e) {
    (*buffer)[i++] = 'e';
  } else {
    (*buffer)[i++] = 'E';
  }
  (*buffer)[i++] = '+';
  (*buffer)[i++] = '0';
  (*buffer)[i++] = '0';
  return i;
}

int scientific_to_string(char **buffer, long double value, int precision,
                         struct flag *cfg, int width) {
  long intPart = (long)value;
  double frac_part_for_zero = value - intPart;
  double fractionalPart = value - intPart;
  int i = 0;
  int exponent = 0;
  if (value == 0) {
    i = scientific_zero(buffer, i, cfg, precision);
  } else {
    while (intPart >= 10) {
      value /= 10;
      intPart /= 10;
      exponent++;
      fractionalPart = value - intPart;
    }
    while (intPart == 0) {
      frac_part_for_zero *= 10;
      intPart = (long)(frac_part_for_zero);
      exponent--;
      fractionalPart = frac_part_for_zero - intPart;
    }
    int fractionalDigit = (int)(fractionalPart * pow(10, precision) + 0.5);
    if (precision != 0) {
      do {
        (*buffer)[i++] = (fractionalDigit % 10) + '0';
        fractionalDigit /= 10;
      } while (fractionalDigit > 0);
      (*buffer)[i++] = '.';
    } else if (cfg->sharp_flag) {
      (*buffer)[i++] = '.';
    }
    (*buffer)[i++] = intPart + '0';
    i = format_exponent(buffer, cfg, exponent, i);
    if (width > i && cfg->minus_flag == 1) {
      i = fl_minus(buffer, i, width);
    }
  }

  return i;
}

int s21_spec_p(char **str, void *ptr) {
  s21_size_t lenBuf = 0;
  int i = 0;
  int *address = ptr;
  if (address == S21_NULL) {
    char buf[7] = "(nil)";
    lenBuf = s21_strlen(buf);
    s21_strncpy(*str, buf, lenBuf);
  } else {
    char buf[4] = "x0";
    while (address) {
      unsigned int dig = ((size_t)address) % 16;
      if (dig < 10)
        (*str)[i++] = (char)('0' + dig);
      else
        (*str)[i++] = (char)('a' + (dig - 10));

      address = (void *)(((size_t)address) / 16);
    }
    *str += i;
    lenBuf = s21_strlen(buf);
    s21_strncpy(*str, buf, lenBuf);
    *str -= i;
    reverse(*str, i + lenBuf);
  }
  return i + lenBuf;
}

int remove_zeros(char **s, struct flag *cfg) {
  char *data = *s;
  int end = 0;
  int expStart = 0;
  int deletZero = 0;
  for (int i = 0; data[i] != '\0'; i++) {
    if (data[i] == 'e' || data[i] == 'E') {
      end = i;
      expStart = i;
    }
  }
  if (end == 0) {
    end = s21_strlen(data);
  }
  for (; data[end - 1] == '0'; end--) {
    deletZero++;
  }
  if (data[end - 1] == '.' && !cfg->sharp_flag) {
    data[end - 1] = '\0';
    deletZero++;
    end--;
  }
  if (expStart != 0) {
    while (data[expStart] != '\0') {
      data[end++] = data[expStart++];
    }
  }

  return deletZero;
}

void set_flag_sharp_prefix(char **str, struct flag *cfg, char spec,
                           int precision) {
  s21_size_t lenBuf = 0;
  if (cfg->sharp_flag) {
    if (spec == 'x') {
      s21_strncpy(*str, "0x", 2);
      lenBuf += 2;
    }
    if (spec == 'X') {
      s21_strncpy(*str, "0X", 2);
      lenBuf += 2;
    }
    if (spec == 'o') {
      s21_strncpy(*str, "0", 1);
      lenBuf += 1;
    }
    if (spec == 'f' && precision == 0) {
      s21_strncpy(*str, ".", 1);
      lenBuf += 1;
    }
    *str += lenBuf;
  }
}

void spec_int(const char **p, struct flag *cfg, int width, int precision,
              char **s, va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  int dl =
      int_to_string(number.halfType | number.standIntType | number.longType, s,
                    10, precision, cfg);
  *s += dl;
  set_width(s, width, dl, cfg);
}

void spec_uint(const char **p, struct flag *cfg, int width, char **s,
               va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  int dl = uint_to_string(number.unsignedHalfType | number.unsignedLongType |
                              number.unsignedIntType,
                          s, 10, width, cfg);
  *s += dl;
  set_width(s, width, dl, cfg);
}

void spec_string(const char **p, struct flag *cfg, int width, char **s,
                 va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  int sa_len = 0;
  if (number.stringType != S21_NULL) {
    sa_len = s21_strlen(number.stringType);
    s21_memcpy(*s, number.stringType, sa_len);
    set_width_for_str(s, width, sa_len, number.stringType, cfg);
  } else if (number.wchartType != S21_NULL) {
    sa_len = wcslen(number.wchartType);
    s21_memcpy(*s, number.wchartType, sa_len);
    set_width_for_str(s, width, sa_len, number.wchartType, cfg);
  }
}

void spec_char(const char **p, struct flag *cfg, int width, char **s,
               va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  if (number.wchartType != S21_NULL) {
    s21_memcpy(*s, &number.wchartType, 1);
  } else {
    s21_memcpy(*s, &number.charType, 1);
  }
  (*s)++;
  set_width(s, width, 1, cfg);
}

void spec_double(const char **p, struct flag *cfg, int width, int precision,
                 char **s, va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  if (precision == -1) precision = 6;
  int dl;
  if (number.standDoubleType != 0) {
    if (number.standDoubleType < 0) {
      cfg->Negative = 1;
      number.standDoubleType = -number.standDoubleType;
    }
    dl = double_to_string(s, number.standDoubleType, precision, cfg, width,
                          ltype);
  } else {
    if (number.longDoubleType < 0) {
      cfg->Negative = 1;
      number.longDoubleType = -number.longDoubleType;
    }
    dl = double_to_string(s, number.longDoubleType, precision, cfg, width,
                          ltype);
  }
  *s += dl;
  set_width(s, width, dl, cfg);
}

void spec_gg(const char **p, struct flag *cfg, int width, int precision,
             char **s, va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  if (precision == -1) precision = 6;
  int exponent = 0;
  if (number.longDoubleType != 0) {
    exponent = (int)log10(fabsl(number.longDoubleType));
  } else if (number.standDoubleType != 0) {
    exponent = (int)log10(fabs(number.standDoubleType));
  }
  if (number.standDoubleType < 0 || number.longDoubleType < 0) {
    cfg->Negative = 1;
    if (number.standDoubleType != 0) {
      number.standDoubleType = -number.standDoubleType;
    } else {
      number.longDoubleType = -number.longDoubleType;
    }
  }
  int use_scientific = (exponent <= -4 || exponent >= precision);
  int dl = 0;
  if (use_scientific) {
    if (number.standDoubleType != 0) {
      dl = scientific_to_string(s, number.standDoubleType, precision - 1, cfg,
                                width);
    } else {
      dl = scientific_to_string(s, number.longDoubleType, precision - 1, cfg,
                                width);
    }
    if (**p == 'g') {
      char *e_pos = s21_strchr(*s, 'E');
      if (e_pos) {
        *e_pos = 'e';
      }
    }
  } else {
    if (number.standDoubleType != 0) {
      dl = double_to_string(s, number.standDoubleType, precision - exponent - 1,
                            cfg, width, ltype);
    } else {
      dl = double_to_string(s, number.longDoubleType, precision - exponent - 1,
                            cfg, width, ltype);
      ;
    }
  }
  if (!cfg->sharp_flag || precision == 0) {
    dl -= remove_zeros(s, cfg);
  }
  *s += dl;
  set_width(s, width, dl, cfg);
}

void spec_ee(const char **p, struct flag *cfg, int width, int precision,
             char **s, va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  int dl;
  if (precision == -1) precision = 6;
  if (number.standDoubleType != 0) {
    if (number.standDoubleType < 0) {
      cfg->Negative = 1;
      number.standDoubleType = -number.standDoubleType;
    }

    dl = scientific_to_string(s, number.standDoubleType, precision, cfg, width);
  } else {
    if (number.longDoubleType < 0) {
      cfg->Negative = 1;
      number.longDoubleType = -number.longDoubleType;
    }
    dl = scientific_to_string(s, number.longDoubleType, precision, cfg, width);
  }
  *s += dl;
  set_width(s, width, dl, cfg);
}

void spec_small_x(const char **p, struct flag *cfg, int width, int precision,
                  char **s, va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  int dl = uint_to_string(number.unsignedHalfType | number.unsignedLongType |
                              number.unsignedIntType,
                          s, 16, precision, cfg);
  *s += dl;
  dl = cfg->sharp_flag ? dl + 2 : dl;
  set_width(s, width, dl, cfg);
}

void spec_big_x(const char **p, struct flag *cfg, int width, int precision,
                char **s, va_list args, struct lenghtTypes *ltype) {
  char data[100];
  argsTypes number = change_types(*p, args, ltype);
  int dl = uint_to_string(number.unsignedHalfType | number.unsignedLongType |
                              number.unsignedIntType,
                          s, 16, precision, cfg);
  s21_memcpy(data, *s, dl);
  data[dl] = '\0';
  char *hex_up = S21_NULL;
  hex_up = s21_to_upper(data);
  if (hex_up != S21_NULL) {
    s21_memcpy(*s, hex_up, dl);
    free(hex_up);
    *s += dl;
    dl = cfg->sharp_flag ? dl + 2 : dl;
    set_width(s, width, dl, cfg);
  }
}

void spec_o(const char **p, struct flag *cfg, int width, int precision,
            char **s, va_list args, struct lenghtTypes *ltype) {
  argsTypes number = change_types(*p, args, ltype);
  int dl = uint_to_string(number.unsignedHalfType | number.unsignedLongType |
                              number.unsignedIntType,
                          s, 8, precision, cfg);
  *s += dl;
  // если есть флаг решетки, то мы увеличиваем смещение указателя
  dl = cfg->sharp_flag ? dl + 1 : dl;
  set_width(s, width, dl, cfg);
}

void spec_p(struct flag *cfg, int width, char **s, va_list args) {
  void *v = va_arg(args, void *);
  int dl = s21_spec_p(s, v);
  *s += dl;
  set_width(s, width, dl, cfg);
}

void get_specificator(const char **p, struct flag *cfg, int width,
                      int precision, char **s, va_list args,
                      struct lenghtTypes *ltype) {
  switch (**p) {
    case 'd': {
      spec_int(p, cfg, width, precision, s, args, ltype);
      break;
    }
    case 'u': {
      spec_uint(p, cfg, width, s, args, ltype);
      break;
    }
    case 's': {
      spec_string(p, cfg, width, s, args, ltype);
      break;
    }
    case 'c': {
      spec_char(p, cfg, width, s, args, ltype);
      break;
    }
    case 'f': {
      spec_double(p, cfg, width, precision, s, args, ltype);
      set_flag_sharp_prefix(s, cfg, **p, precision);
      break;
    }
    case 'g':
    case 'G': {
      spec_gg(p, cfg, width, precision, s, args, ltype);
      break;
    }
    case 'e': {
      cfg->small_e = 1;
      spec_ee(p, cfg, width, precision, s, args, ltype);
      break;
    }
    case 'E': {
      spec_ee(p, cfg, width, precision, s, args, ltype);
      break;
    }
    case 'x': {
      set_flag_sharp_prefix(s, cfg, **p, precision);
      spec_small_x(p, cfg, width, precision, s, args, ltype);
      break;
    }
    case 'X': {
      set_flag_sharp_prefix(s, cfg, **p, precision);
      spec_big_x(p, cfg, width, precision, s, args, ltype);
      break;
    }
    case 'o': {
      set_flag_sharp_prefix(s, cfg, **p, precision);
      spec_o(p, cfg, width, precision, s, args, ltype);
      break;
    }
    case 'p': {
      spec_p(cfg, width, s, args);
      break;
    }
    case '%': {
      (*s)[0] = '%';
      (*s)++;
      break;
    }
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  int result = 0;
  va_list args;
  va_start(args, format);

  const char *p;
  char *s = str;
  int precision = -1;

  for (p = format; *p != '\0'; p++) {
    if (*p == '%') {
      p++;
      struct flag cfg = {0};
      struct lenghtTypes ltype = {0};
      get_flag(&p, &cfg);
      int width = 0;
      if (cfg.width_flag)
        width = va_arg(args, int);
      else
        width = get_width(&p);
      if (*p == '.') {
        cfg.point = 1;
        p++;
        if (*p == '*') {
          precision = va_arg(args, int);
          p++;
        } else
          p += parseInteger(p, &precision);
      }
      get_length_type(&p, &ltype);
      get_specificator(&p, &cfg, width, precision, &s, args, &ltype);
    } else {
      s21_memcpy(s, &(*p), 1);
      s++;
    }
  }
  *s = '\0';
  result = s - str;
  va_end(args);
  return result;
}