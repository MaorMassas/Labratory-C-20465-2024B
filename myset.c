#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function declarations
void prompt();
void initialize_sets();
set* get_set_by_name(const char* name);
void handle_command(char* command);

set SETA, SETB, SETC, SETD, SETE, SETF;

typedef struct {
    const char* name;
    set* set_ptr;
} set_map;

typedef struct {
    const char* name;
    void (*func)(set*, const set*, const set*);
} command_map;

set_map sets[] = {
        {"SETA", &SETA},
        {"SETB", &SETB},
        {"SETC", &SETC},
        {"SETD", &SETD},
        {"SETE", &SETE},
        {"SETF", &SETF},
        {NULL, NULL}
};

command_map cmd[] = {
        {"read_set", (void (*)(set*, const set*, const set*))read_set},
        {"print_set", (void (*)(set*, const set*, const set*))print_set},
        {"union_set", union_set},
        {"intersect_set", intersect_set},
        {"sub_set", sub_set},
        {"symdiff_set", symdiff_set},
        {NULL, NULL}
};

int main() {
    char command[256];

    initialize_sets();

    while (1) {
        prompt();
        if (!fgets(command, sizeof(command), stdin)) {
            printf("Error: EOF encountered. Stopping the program.\n");
            break;
        }
        command[strcspn(command, "\n")] = '\0'; // Remove newline character
        printf("%s\n", command); // Print the command as read

        handle_command(command);
    }

    return 0;
}

// Function to prompt the user for input
void prompt() {
    printf("Enter a command: ");
}

// Function to initialize sets
void initialize_sets() {
    int i;
    for (i = 0; sets[i].set_ptr != NULL; i++) {
        memset(sets[i].set_ptr, 0, SET_SIZE);
    }
}

// Function to get a set by its name
set* get_set_by_name(const char* name) {
    int i;
    for (i = 0; sets[i].set_ptr != NULL; i++) {
        if (strcmp(sets[i].name, name) == 0) {
            return sets[i].set_ptr;
        }
    }
    return NULL;
}

// Function to handle commands
void handle_command(char* command) {
    char cmd_name[32];
    char param1[32], param2[32], param3[32];
    int num_params;
    set* set1;
    set* set2;
    set* set3;

    // Parse the command and its parameters
    num_params = sscanf(command, "%31s %31s , %31s , %31s", cmd_name, param1, param2, param3);

    if (num_params < 1) {
        printf("Error: Invalid command format.\n");
        return;
    }

    if (strcmp(cmd_name, "stop") == 0) {
        exit(0);
    }

    // Find and execute the corresponding command function
    int i;
    for (i = 0; cmd[i].name != NULL; i++) {
        if (strcmp(cmd[i].name, cmd_name) == 0) {
            switch (num_params) {
                case 2:
                    set1 = get_set_by_name(param1);
                    if (set1) {
                        ((void (*)(set*, const set*, const set*))cmd[i].func)(set1, NULL, NULL);
                    } else {
                        printf("Error: Undefined set name.\n");
                    }
                    break;
                case 3:
                    set1 = get_set_by_name(param1);
                    set2 = get_set_by_name(param2);
                    if (set1 && set2) {
                        ((void (*)(set*, const set*, const set*))cmd[i].func)(set1, set2, NULL);
                    } else {
                        printf("Error: Undefined set name.\n");
                    }
                    break;
                case 4:
                    set1 = get_set_by_name(param1);
                    set2 = get_set_by_name(param2);
                    set3 = get_set_by_name(param3);
                    if (set1 && set2 && set3) {
                        cmd[i].func(set3, set1, set2);
                    } else {
                        printf("Error: Undefined set name.\n");
                    }
                    break;
                default:
                    printf("Error: Invalid number of parameters.\n");
            }
            return;
        }
    }

    printf("Error: Undefined command name.\n");
}
