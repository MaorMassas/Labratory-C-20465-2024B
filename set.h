#define SET_H

#define SET_SIZE 16

typedef char set[SET_SIZE];

void read_set(set s, const int *values);
void print_set(const set s);
void union_set(set result, const set set1, const set set2);
void intersect_set(set result, const set set1, const set set2);
void sub_set(set result, const set set1, const set set2);
void symdiff_set(set result, const set set1, const set set2);
