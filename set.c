#include "set.h"
#include <stdio.h>
#include <string.h>

void read_set(set s, const int *values) {
    int i;
    memset(s, 0, SET_SIZE);

    for (i = 0; values[i] != -1; i++) {
        if (values[i] < 0 || values[i] > 127) {
            printf("Invalid set member – value out of range\n");
            return;
        }
        s[values[i] / 8] |= (1 << (values[i] % 8));
    }
}


void print_set(const set s) {
    int i;
    int count = 0;
    int first = 1;

    for (i = 0; i < 128; i++) {
        if (s[i / 8] & (1 << (i % 8))) {
            if (!first) {
                printf(", ");
            }
            printf("%d", i);
            count++;
            first = 0;

            if (count == 16) {
                printf("\n");
                count = 0;
                first = 1;
            }
        }
    }

    if (count == 0) {
        printf("The set is empty");
    }
    printf("\n");
}

void union_set(char *result, set *set1, set *set2) {
	int i;
	for (i = 0; i < SET_SIZE; i++)
		result[i] = set1[i] | set2[i];
}

void intersect_set(char *result, set *set1, set *set2) {
	int i;
	for (i = 0; i < SET_SIZE; i++)
		result[i] = set1[i] & set2[i];
}

void sub_set(char *result, set *set1, set *set2){
	int i;
	for(i = 0; i < SET_SIZE; i++)
		result[i] = set1[i] & ~set2[i];
}

void symdiff_set(char *result, set *set1, set *set2){
	int i;
	for(i = 0; i < SET_SIZE; i++)
		result[i] = set1[i] ^ set2[i];
}