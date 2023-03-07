#include "cat.h"

void s21_cat(int argc, char *argv[]) {
  int numbers = 0;
  int is_flag = 0;
  char text[ARRAY];
  if (check_flag(argc, argv, &is_flag) == 0) {
    for (int index = 1; index < argc; index++) {
      if (argv[index][0] != '-') {
        FILE *file = fopen(argv[index], "r");
        if (file != NULL) {
          for (int i = 0; (text[i] = fgetc(file)) != EOF; i++) {
            if (flag_s(text, i) == 1) {
              continue;
            }
            flag_b(text, i, &numbers);
            flag_n(text, i, &numbers);
            if (flag_e_t_v(text, i) == 0) {
              print_text(text, i);
            } else {
              continue;
            }
          }
          numbers = 0;
          fclose(file);
        } else {
          fprintf(stderr, "s21_cat: %s: No such file or directory",
                  argv[index]);
        }
      }
    }
    print_error(argc, argv, is_flag);
  }
}

int check_flag(int argc, char *argv[], int *is_flag) {
  int check_options;
  int error_flag = 0;
  int flags_index = 0;
  const struct option long_flags[] = {
      {"number-nonblank", no_argument, &((*change).b), 1},
      {"number", no_argument, &((*change).n), 1},
      {"squeeze-blank", no_argument, &((*change).s), 1},
  };
  while ((check_options = getopt_long(argc, argv, "+benstvTE", long_flags,
                                      &flags_index)) != -1) {
    if (switch_construction(check_options) == 1) {
      error_flag = 1;
    }
    if (error_flag == 1) {
      break;
    } else {
      *is_flag = 1;
    }
  }
  return error_flag;
}

int switch_construction(int check_options) {
  int wrong_flag = 0;
  switch (check_options) {
    case 'b':
      change->b = 1;
      break;
    case 'e':
      change->e = 1;
      change->v = 1;
      break;
    case 'n':
      change->n = 1;
      break;
    case 's':
      change->s = 1;
      break;
    case 't':
      change->t = 1;
      change->v = 1;
      break;
    case 'v':
      change->v = 1;
      break;
    case 'E':
      change->e = 2;
      break;
    case 'T':
      change->t = 2;
      break;
    case '?':
      fprintf(stderr, "usage: s21_cat [-benstvTE] [file ...]");
      wrong_flag = 1;
      break;
  }
  return wrong_flag;
}

void flag_b(char *text, int i, int *numbers) {
  if (changed_flag.b && (text[i - 1] == '\n' || i == 0) && text[i] != '\n') {
    (*numbers)++;
    printf("%6d\t", *numbers);
  }
}

int flag_e_t_v(char *text, int i) {
  int skip_char = 0;
  if (changed_flag.e && text[i] == 10) {
    printf("$");
  }
  if (changed_flag.t && text[i] == 9) {
    printf("^I");
    skip_char = 1;
  }
  if (text[i] == 127 && (changed_flag.e || changed_flag.t || changed_flag.v)) {
    printf("^?");
    skip_char = 1;
  }
  if ((changed_flag.e || changed_flag.t || changed_flag.v) && text[i] != 127 &&
      text[i] >= 0 && text[i] != 9 && text[i] != 10 && text[i] < 32) {
    printf("^%c", text[i] + 64);
    skip_char = 1;
  }
  return skip_char;
}

void flag_n(char *text, int i, int *numbers) {
  if (changed_flag.n && !changed_flag.b && (text[i - 1] == '\n' || i == 0)) {
    (*numbers)++;
    printf("%6d\t", *numbers);
  }
}

int flag_s(char *text, int i) {
  int skip_cycle = 0;
  if (changed_flag.s &&
      ((i == 1 && text[0] == '\n' && text[1] == '\n') ||
       (text[i] == '\n' && text[i - 1] == '\n' && text[i - 2] == '\n'))) {
    skip_cycle = 1;
  }
  return skip_cycle;
}

void print_text(char *text, int i) { printf("%c", text[i]); }

void print_error(int argc, char *argv[], int is_flag) {
  int fix_bag = 0;
  if (argv[argc - 1][0] == '-') {
    for (int i = 1; i < argc; i++) {
      if (fix_bag == 0 && is_flag == 1) {
        printf("\n");
      }
      fix_bag++;
      if (argv[i][0] == '-' && fix_bag > 2) {
        fprintf(stdout, "s21_cat: %s: No such file or directory\n", argv[i]);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  s21_cat(argc, argv);
  return 0;
}
