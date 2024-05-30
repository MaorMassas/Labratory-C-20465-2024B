#include "set.h"
#include <stdio.h>
#include <string.h>

void read_set(char s, int *values){
	 /* Initialize set to empty*/
	 memset(s, 0, SET_SIZE);

}

void union_set(char *result, char *set1, char *set2) {
	int i;
	for (i = 0; i < SET_SIZE; i++)
		result[i] = set1[i] | set2[i];
}

void intersect_set(char *result, char *set1, char *set2) {
	int i;
	for (i = 0; i < SET_SIZE; i++)
		result[i] = set1[i] & set2[i];
}

void sub_set(char *result, char *set1, char *set2){
	int i;
	for(i = 0; i < SET_SIZE; i++)
		result[i] = set1[i] & ~set2[i];
}

void symdiff_set(char *result, char *set1, char *set2){
	int i;
	for(i = 0; i < SET_SIZE; i++)
		result[i] = set1[i] ^ set2[i];
}