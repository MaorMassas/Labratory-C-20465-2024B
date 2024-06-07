
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "set.h"

#define MAX_CMD_LEN 256

set SETA, SETB, SETC, SETD, SETE, SETF;

typedef struct {
    char name[5];
    set *set;
} set_map;

set_map sets[] = {
    {"SETA", &SETA},
    {"SETB", &SETB},
    {"SETC", &SETC},
    {"SETD", &SETD},
    {"SETE", &SETE},
    {"SETF", &SETF},
    {"", NULL}
};

typedef struct {
    char *name;
    void (*func)(void);
} command_map;

set *temp_set1;
set *temp_set2;
set *temp_result;
int *temp_values;

void handle_read_set(void) {
    read_set(*temp_set1, temp_values);
    free(temp_values);
    temp_values = NULL;
}

void handle_print_set(void) {
    print_set(*temp_set1);
}

void handle_union_set(void) {
    union_set(*temp_result, *temp_set1, *temp_set2);
}

void handle_intersect_set(void) {
    intersect_set(*temp_result, *temp_set1, *temp_set2);
}

void handle_sub_set(void) {
    sub_set(*temp_result, *temp_set1, *temp_set2);
}

void handle_symdiff_set(void) {
    symdiff_set(*temp_result, *temp_set1, *temp_set2);
}

void handle_stop(void) {
    printf("Program terminated.\n");
    exit(0);
}

void not_valid(void) {
    printf("Command not valid\n");
}

command_map cmd[] = {
    {"read_set", handle_read_set},
    {"print_set", handle_print_set},
    {"union_set", handle_union_set},
    {"intersect_set", handle_intersect_set},
    {"sub_set", handle_sub_set},
    {"symdiff_set", handle_symdiff_set},
    {"stop", handle_stop},
    {"not_valid", not_valid}
};

set* get_set(char *name) {
    int i;
    for (i = 0; sets[i].set != NULL; i++) {
        if (strcmp(name, sets[i].name) == 0) {
            return sets[i].set;
        }
    }
    return NULL;
}

int is_valid_integer(const char *str) {
    if (*str == '-' || *str == '+') str++;
    if (!*str) return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

char* trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char) *str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;
    end[1] = '\0';
    return str;
}

int parse_command(char *command) {
    char *cmd_name, *token;
    char set1_name[5], set2_name[5], result_name[5];
    int i, value, num_values;

    cmd_name = strtok(command, " \t");
    if (cmd_name == NULL) {
        printf("Error: command missing\n");
        return -1;
    }

    for (i = 0; cmd[i].func != NULL; i++) {
        if (strcmp(cmd_name, cmd[i].name) == 0) {
            break;
        }
    }

    if (cmd[i].func == NULL) {
        printf("Error: name command Undefined\n");
        return -1;
    }

    if (strcmp(cmd_name, "read_set") == 0) {
        token = strtok(NULL, " ,\t");
        if (token) {
            strcpy(set1_name, token);
            temp_set1 = get_set(set1_name);
            if (temp_set1 == NULL) {
                printf("Error: nameset Undefined\n");
                return -1;
            }
            num_values = 0;
            temp_values = malloc(128 * sizeof(int));
            if (temp_values == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            while ((token = strtok(NULL, " ,\t")) != NULL) {
                if (!is_valid_integer(token)) {
                    printf("Error: member set Invalid - not an integer\n");
                    free(temp_values);
                    temp_values = NULL;
                    return -1;
                }
                value = atoi(token);
                if (value < -1 || value > 127) {
                    printf("Error: member set Invalid - value out of range\n");
                    free(temp_values);
                    temp_values = NULL;
                    return -1;
                }
                temp_values[num_values++] = value;
                if (num_values % 128 == 0) {
                    temp_values = realloc(temp_values, (num_values + 128) * sizeof(int));
                    if (temp_values == NULL) {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            if (temp_values) {
                temp_values[num_values] = -1;
                cmd[i].func();
            }
        } else {
            printf("Error: nameset Undefined\n");
            return -1;
        }
    } else if (strcmp(cmd_name, "print_set") == 0) {
        token = strtok(NULL, " ,\t");
        if (token) {
            strcpy(set1_name, token);
            temp_set1 = get_set(set1_name);
            if (temp_set1 == NULL) {
                printf("Error: nameset Undefined\n");
                return -1;
            }
            if (strtok(NULL, " ,\t") != NULL) {
                printf("Error: Extraneous text after end of command\n");
                return -1;
            } else {
                cmd[i].func();
            }
        } else {
            printf("Error: nameset Undefined\n");
            return -1;
        }
    } else if (strcmp(cmd_name, "union_set") == 0 ||
               strcmp(cmd_name, "intersect_set") == 0 ||
               strcmp(cmd_name, "sub_set") == 0 ||
               strcmp(cmd_name, "symdiff_set") == 0) {
        token = strtok(NULL, " ,\t");
        if (token) {
            strcpy(result_name, token);
            temp_result = get_set(result_name);
            if (temp_result == NULL) {
                printf("Error: nameset Undefined\n");
                return -1;
            }
            token = strtok(NULL, " ,\t");
            if (token) {
                strcpy(set1_name, token);
                temp_set1 = get_set(set1_name);
                if (temp_set1 == NULL) {
                    printf("Error: nameset Undefined\n");
                    return -1;
                }
                token = strtok(NULL, " ,\t");
                if (token) {
                    strcpy(set2_name, token);
                    temp_set2 = get_set(set2_name);
                    if (temp_set2 == NULL) {
                        printf("Error: nameset Undefined\n");
                        return -1;
                    }
                    if (strtok(NULL, " ,\t") != NULL) {
                        printf("Error: Extraneous text after end of command\n");
                        return -1;
                    } else {
                        cmd[i].func();
                    }
                } else {
                    printf("Error: nameset Undefined\n");
                    return -1;
                }
            } else {
                printf("Error: nameset Undefined\n");
                return -1;
            }
        } else {
            printf("Error: nameset Undefined\n");
            return -1;
        }
    } else if (strcmp(cmd_name, "stop") == 0) {
        if (strtok(NULL, " ,\t") != NULL) {
            printf("Error: Extraneous text after end of command\n");
            return -1;
        } else {
            cmd[i].func();
        }
    } else {
        printf("Error: name command Undefined\n");
        return -1;
    }

    return 0;
}

int main(void) {
    FILE *fp;
    char command[MAX_CMD_LEN];

    fp = fopen("test_input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(command, sizeof(command), fp)) {
        /* Remove trailing newline character*/
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        /* Remove leading whitespace*/
        char *ptr = command;
        while (*ptr != '\0' && isspace((unsigned char)*ptr)) {
            ptr++;
        }

        /* Skip empty lines*/
        if (*ptr == '\0') {
            continue;
        }

        if (parse_command(ptr) == -1) {
            printf("Command parsing failed. Please try again.\n");
        }
    }

    fclose(fp);

    return 0;
}
