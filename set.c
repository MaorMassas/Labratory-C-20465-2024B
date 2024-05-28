#include <stdio.h>
#define SET_SIZE 16

int main() {
}

void set_union(char *set1, char *set2, int set_size) {
	int i;
	for (i = 0; i < set_size; i++)
		set1[i] = set1[i] | set2[i];
}

void set_intersect(char *set1, char *set2, int set_size) {
	int i;
	for (i = 0; i < set_size; i++)
		set1[i] = set1[i] & set2[i];
}
