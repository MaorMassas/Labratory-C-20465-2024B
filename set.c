#include "set.h"
#include <stdio.h>
#include <string.h>

void read_set(set s, const int *values){
	 /* Initialize set to empty*/
	 int i,value;
	 memset(s, 0, SET_SIZE);
	 for(i = 0; values[i] != -1;i++){
	 	value = values[i];
	 	if(value >= 0 && value < 128)
	 		s[value/8] |= (1 << (value % 8));
	 	else
	 		printf(stderr,"invalid set number - value out of range: %d\n",value);
	 		return;
	 }
}

void print_set(set s){
	int i,count;
	for(i = 0;i < 128;i++){
		if(s[i/8] & (1 << (i % 8))){
			if(count && count % 16 == 0){
				printf("\n");
			}
			printf("%d ", i);
			count++;
		}
	}
	if(count ==  0){
		printf("The set is empty\n");
	}else{
		printf("\n");
	}
}

void union_set(set result, set set1, set set2) {
    for (int i = 0; i < SET_SIZE; i++) {
        result[i] = set1[i] | set2[i];
    }
}

void intersect_set(set result, set set1, set set2) {
    for (int i = 0; i < SET_SIZE; i++) {
        result[i] = set1[i] & set2[i];
    }
}

void sub_set(set result, set set1, set set2) {
    for (int i = 0; i < SET_SIZE; i++) {
        result[i] = set1[i] & ~set2[i];
    }
}

void symdiff_set(set result, set set1, set set2) {
    for (int i = 0; i < SET_SIZE; i++) {
        result[i] = set1[i] ^ set2[i];
    }
}