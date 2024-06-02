#define SET_H

#define SET_SIZE 16

typedef char set[SET_SIZE];

void read_set(set s, const int *values);
void print_set(set s);
void union_set(char result, set set1, set set2);
void intersect_set(char result, set set1, set set2);
void sub_set(char result, set set1, set set2);
void symdiff_set(char result, set set1, set set2);

