#ifndef UTILS_H
#define UTILS_H
#include "common.h"
void clear_input_buffer(void);
int get_int_input(const char *prompt, int min, int max);
float get_float_input(const char *prompt, float min, float max);
void get_string_input(char *buffer, size_t size, const char *prompt);
void to_lower(char *str);
int compare_strings_ignore_case(const char *s1, const char *s2);
float grade_to_gpa_points(float grade);
const char* get_letter_grade(float grade);
#endif
