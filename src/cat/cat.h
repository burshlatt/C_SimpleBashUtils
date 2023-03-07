#ifndef SRC_CAT_H_
#define SRC_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY 10000

typedef struct flag {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} flag_t;

flag_t changed_flag = {0, 0, 0, 0, 0, 0};
flag_t *change = &changed_flag;

int flag_s(char *text, int i);
int flag_e_t_v(char *text, int i);
int switch_construction(int check_options);
int check_flag(int argc, char *argv[], int *is_flag);

void print_text(char *text, int i);
void s21_cat(int argc, char *argv[]);
void flag_b(char *text, int i, int *numbers);
void flag_n(char *text, int i, int *numbers);
void print_error(int argc, char *argv[], int is_flag);

#endif // SRC_CAT_H_
