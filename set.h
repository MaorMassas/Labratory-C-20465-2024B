#define SET_H

#define SET_SIZE 16
#define MAX_CMD_LEN 256

typedef char set[SET_SIZE];

void read_set(set s, const int *values);
void print_set(set s);
void union_set(set result, set set1, set set2);
void intersect_set(set result, set set1, set set2);
void sub_set(set result, set set1, set set2);
void symdiff_set(set result, set set1, set set2);
void handle_input(char *input);
set* get_set(char *name);