#include "grep.h"

int main(int argc, char *argv[]) {
  s21_grep(argc, argv);
  return 0;
}

void s21_grep(int argc, char *argv[]) {
  char pattern_array[ARRAY] = {0};
  int match_in_files = 0, match_count = 0;
  int count_of_files = 0, position_index = 0;
  if (read_flag(argc, argv, pattern_array) == 0) {
    if (pattern_array[strlen(pattern_array) - 1] == '|') {
      pattern_array[strlen(pattern_array) - 1] = '\0';
    }
    if (changed_flag.e || changed_flag.f) {
      count_of_files = argc - optind;
    } else {
      count_of_files = argc - optind - 1;
    }
    if (changed_flag.e || changed_flag.f) {
      position_index = optind;
    } else {
      position_index = optind + 1;
    }
    for (int index = position_index; index < argc; index++) {
      if (index != 1) {
        FILE *file = fopen(argv[index], "r");
        match_in_files = 0;
        match_count = 0;
        if (file != NULL) {
          int status = 0;
          char text[ARRAY] = {0};
          for (int string_number = 1; fgets(text, ARRAY, file) != NULL;
               string_number++) {
            if (text[strlen(text)] == '\0' && text[strlen(text) - 1] != '\n') {
              text[strlen(text)] = '\n';
            }
            if (flags(argv, index, text, &match_count, &match_in_files,
                      string_number, count_of_files, pattern_array) == 0) {
              status++;
            }
            if (changed_flag.o) {
              if (flag_o(pattern_array, text, string_number, argv, index,
                         count_of_files) == 0) {
                status++;
              }
            }
          }
          flags_c_l(match_in_files, argv[index], count_of_files, match_count);
          fclose(file);
        } else if (!changed_flag.s) {
          fprintf(stderr, "grep: %s: No such file or directory\n", argv[index]);
        }
      }
    }
  }
}

int read_flag(int argc, char *argv[], char *pattern_array) {
  char check_options;
  int error_flag = 0;
  int error_switch = 0;
  for (int i = 0;
       (check_options = getopt_long(argc, argv, "e:ivclnhsf:o", 0, NULL)) != -1;
       i++) {
    if (switch_construction(check_options) == 1) {
      error_flag = 1;
      error_switch = 1;
      break;
    }
    if (change->e && check_options == 'e') {
      strcat(pattern_array, optarg);
      strcat(pattern_array, "|");
    }
    if (change->f && check_options == 'f') {
      FILE *file = fopen(optarg, "r");
      if (file != NULL) {
        while (1) {
          char string[ARRAY];
          if (fgets(string, ARRAY, file) != NULL) {
            if (string[strlen(string) - 1] == '\n' &&
                string[strlen(string)] == '\0' && ((strlen(string) - 1) != 0)) {
              string[strlen(string) - 1] = '\0';
            }
            if ((strlen(string) - 1) == 0 && changed_flag.o) {
              change->o = 0;
            }
            strcat(pattern_array, string);
            strcat(pattern_array, "|");
          } else {
            break;
          }
        }
        fclose(file);
      } else if (file == NULL && !changed_flag.s) {
        fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
      }
    }
  }
  if ((argc <= 1 && changed_flag.no_flag) ||
      (argc <= 2 && !changed_flag.no_flag)) {
    error_switch = 1;
  }
  if (changed_flag.c || changed_flag.v) {
    change->o = 0;
  }
  if (!change->e && !change->i && !change->v && !change->c && !change->l &&
      !change->n && !change->h && !change->s && !change->f && !change->o) {
    changed_flag.no_flag = 1;
  }
  if (!changed_flag.e && !changed_flag.f && error_switch == 0) {
    strcat(pattern_array, argv[optind]);
    strcat(pattern_array, "|");
  }
  if (error_switch == 1) {
    error_flag = 1;
    fprintf(stderr,
            "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B "
            "num] [-C[num]]\n");
    fprintf(stderr,
            "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
    fprintf(stderr,
            "\t[--context[=num]] [--directories=action] [--label] "
            "[--line-buffered]\n");
    fprintf(stderr, "\t[--null] [pattern] [file ...]\n");
  }
  return error_flag;
}

int switch_construction(int check_options) {
  int wrong_flag = 0;
  switch (check_options) {
    case 'e':
      change->e = 1;
      break;
    case 'i':
      change->i = 1;
      break;
    case 'v':
      change->v = 1;
      break;
    case 'c':
      change->c = 1;
      break;
    case 'l':
      change->l = 1;
      break;
    case 'n':
      change->n = 1;
      break;
    case 'h':
      change->h = 1;
      break;
    case 's':
      change->s = 1;
      break;
    case 'f':
      change->f = 1;
      break;
    case 'o':
      change->o = 1;
      break;
    case '?':
      wrong_flag = 1;
      break;
  }
  return wrong_flag;
}

int flags(char *argv[], int index, char *text, int *match_count,
          int *match_in_files, int string_number, int count_of_files,
          char *pattern_array) {
  int status = regex_function(pattern_array, text, match_in_files, match_count);
  if (!changed_flag.o) {
    print_grep(text, string_number, argv[index], count_of_files, status);
  }
  return status;
}

void flags_c_l(int match_in_files, char *name_of_file, int count_of_files,
               int match_count) {
  int number_of_files = 0;
  if (changed_flag.c && !changed_flag.l) {
    if (count_of_files > 1 && !changed_flag.h) {
      printf("%s:", name_of_file);
    }
    printf("%d\n", match_count);
  }
  if (changed_flag.l && match_in_files > 0) {
    number_of_files++;
    if (changed_flag.c) {
      if (count_of_files > 1 && !changed_flag.h) {
        printf("%s:%d\n", name_of_file, number_of_files);
      } else {
        printf("%d\n", number_of_files);
      }
    }
    printf("%s\n", name_of_file);
  }
  if (changed_flag.l && match_in_files == 0) {
    if (changed_flag.c) {
      if (count_of_files > 1 && !changed_flag.h) {
        printf("%s:%d\n", name_of_file, number_of_files);
      } else {
        printf("%d\n", number_of_files);
      }
    }
  }
}

int flag_o(char *pattern_array, char *text, int string_number, char *argv[],
           int index, int count_of_files) {
  int status = 1;
  int limiter = 0;
  char *s = text;
  regex_t regex;
  regmatch_t pmatch[1];
  regoff_t offset, length;
  if (!changed_flag.i) {
    status = regcomp(&regex, pattern_array, REG_NEWLINE | REG_EXTENDED);
  } else {
    status =
        regcomp(&regex, pattern_array, REG_NEWLINE | REG_ICASE | REG_EXTENDED);
  }
  for (int i = 0; 1; i++) {
    status = regexec(&regex, s, 1, pmatch, 0);
    if ((status && !changed_flag.v) || (!status && changed_flag.v)) {
      break;
    }
    offset = pmatch[0].rm_so + (s - text);
    length = pmatch[0].rm_eo - pmatch[0].rm_so;
    s += pmatch[0].rm_eo;
    if (!changed_flag.c && !changed_flag.l && !changed_flag.v) {
      if (count_of_files > 1 && !changed_flag.h) {
        printf("%s:", argv[index]);
      }
      if (changed_flag.n && limiter == 0) {
        printf("%d:", string_number);
        limiter = 1;
      }
      int j = 0;
      for (int i = offset; j < length; i++) {
        printf("%c", text[i]);
        j++;
      }
      printf("\n");
    } else if (changed_flag.v) {
      print_grep(text, string_number, argv[index], count_of_files, status);
      break;
    }
  }
  regfree(&regex);
  return status;
}

int regex_function(char *pattern, char *text, int *match_in_files,
                   int *match_count) {
  regex_t regex;
  regmatch_t pmatch[1];
  int status = 0;
  if (!changed_flag.i) {
    status = regcomp(&regex, pattern, REG_NEWLINE | REG_EXTENDED);
  } else {
    status = regcomp(&regex, pattern, REG_NEWLINE | REG_ICASE | REG_EXTENDED);
  }
  if (!status) {
    status = regexec(&regex, text, 1, pmatch, 0);
    if (!status && !changed_flag.v) {
      (*match_count)++;
      (*match_in_files)++;
    } else if (status && changed_flag.v) {
      (*match_count)++;
      (*match_in_files)++;
    }
  }
  regfree(&regex);
  return status;
}

void print_grep(char *text, int string_number, char *name_of_file,
                int count_of_files, int status) {
  if (!changed_flag.v && !status && !changed_flag.c && !changed_flag.l) {
    if (count_of_files > 1 && !changed_flag.h) {
      printf("%s:", name_of_file);
    }
    if (changed_flag.n) {
      printf("%d:", string_number);
    }
    printf("%s", text);
  } else if (changed_flag.v && status && !changed_flag.c && !changed_flag.l) {
    if (count_of_files > 1 && !changed_flag.h) {
      printf("%s:", name_of_file);
    }
    if (changed_flag.n) {
      printf("%d:", string_number);
    }
    printf("%s", text);
  }
}
