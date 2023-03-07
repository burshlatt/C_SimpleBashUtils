#ifndef SRC_GREP_H_
#define SRC_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY 10000

typedef struct flag {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int no_flag;
} flag_t;

flag_t changed_flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
flag_t *change = &changed_flag;

int read_flag(int argc, char *argv[], char *pattern_array);
int switch_construction(int check_options);
int flags(char *argv[], int index, char *text, int *match_count,
          int *match_in_files, int string_number, int count_of_files,
          char *pattern_array);
int flag_o(char *pattern_array, char *text, int string_number, char *argv[],
           int index, int count_of_files);
int regex_function(char *pattern, char *text, int *match_in_files,
                   int *match_count);

void s21_grep(int argc, char *argv[]);
void flags_c_l(int match_in_files, char *name_of_file, int count_of_files,
               int match_count);
void print_grep(char *text, int string_number, char *name_of_file,
                int count_of_files, int status);

#endif // SRC_GREP_H_
