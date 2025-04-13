#include "../s21_string.h"
#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

struct flag {
  int plus_flag;
  int minus_flag;
  int space_flag;
  int width_flag;
  int point;
  int Negative;
  int flag_zero;
  int small_e;
  int sharp_flag;
};

typedef struct {
  char charType;
  char *stringType;
  wchar_t *wchartType;
  int standIntType;
  unsigned int unsignedIntType;
  short halfType;
  unsigned short unsignedHalfType;
  long longType;
  unsigned long unsignedLongType;
  double standDoubleType;
  long double longDoubleType;
} argsTypes;

struct lenghtTypes {
  int symbolsh, symbolsl, symbolsL;
};

argsTypes change_types(const char *p, va_list args, struct lenghtTypes *ltype);
int fl_plus(char **buffer, int i);
int fl_space(char **buffer, int i);
int fl_minus(char **buffer, int i, int width);
void get_flag(const char **p, struct flag *cfg);
int parseInteger(const char *str, int *val);
int get_width(const char **p);
void reverse(char *str, int length);
long double l_round_to_decimal(long double value, int decimal_places);
float f_round_to_decimal(float value, int decimal_places);
int string_help_round(long double value, int precision);
long double checker_precision(long double value, int precision,
                              struct lenghtTypes *ltype);
int checker_flag(struct flag *cfg, char **buffer, int i);
int double_to_string(char **buffer, long double value, int precision,
                     struct flag *cfg, int width, struct lenghtTypes *ltype);
int int_to_string(long int num, char **str, int base, int width,
                  struct flag *cfg);
int uint_to_string(unsigned int num, char **str, int base, int width,
                   struct flag *cfg);
void set_width(char **str, int width, int long_number, struct flag *cfg);
void set_width_for_str(char **str, int width, int len_str, void *data,
                       struct flag *cfg);
int format_exponent(char **buffer, struct flag *cfg, int exponent, int i);
int scientific_zero(char **buffer, int i, struct flag *cfg, int precision);
int scientific_to_string(char **buffer, long double value, int precision,
                         struct flag *cfg, int width);
int s21_spec_p(char **str, void *ptr);
int remove_zeros(char **s, struct flag *cfg);
void set_flag_sharp_prefix(char **str, struct flag *cfg, char spec,
                           int precision);
void spec_int(const char **p, struct flag *cfg, int width, int precision,
              char **s, va_list args, struct lenghtTypes *ltype);
void spec_uint(const char **p, struct flag *cfg, int width, char **s,
               va_list args, struct lenghtTypes *ltype);
void spec_string(const char **p, struct flag *cfg, int width, char **s,
                 va_list args, struct lenghtTypes *ltype);
void spec_char(const char **p, struct flag *cfg, int width, char **s,
               va_list args, struct lenghtTypes *ltype);
void spec_double(const char **p, struct flag *cfg, int width, int precision,
                 char **s, va_list args, struct lenghtTypes *ltype);
void spec_gg(const char **p, struct flag *cfg, int width, int precision,
             char **s, va_list args, struct lenghtTypes *ltype);
void spec_ee(const char **p, struct flag *cfg, int width, int precision,
             char **s, va_list args, struct lenghtTypes *ltype);
void spec_small_x(const char **p, struct flag *cfg, int width, int precision,
                  char **s, va_list args, struct lenghtTypes *ltype);
void spec_big_x(const char **p, struct flag *cfg, int width, int precision,
                char **s, va_list args, struct lenghtTypes *ltype);
void spec_o(const char **p, struct flag *cfg, int width, int precision,
            char **s, va_list args, struct lenghtTypes *ltype);
void spec_p(struct flag *cfg, int width, char **s, va_list args);
void get_specificator(const char **p, struct flag *cfg, int width,
                      int precision, char **s, va_list args,
                      struct lenghtTypes *ltype);
void get_length_type(const char **p, struct lenghtTypes *ltype);

#endif