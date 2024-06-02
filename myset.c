#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
	set SETA, SETB, SETC, SETD, SETE, SETF;
	struct
	{
		char name;
		set *set;
	} sets[]= {
		{'SETA',&SETA},
		{'SETB',&SETB},
		{'SETC',&SETC},
		{'SETD',&SETD},
		{'SETE',&SETE},
		{'SETF',&SETF},
        {'#',NULL}
	};
	struct {
		char *s;
		void (*func)(set, set, set);
	} cmd[] = {
		{"union_set", union_set},
		{"intersect_set", intersect_set},
		{"sub_set", sub_set},
		{"symdiff_set", symdiff_set},
		{NULL, NULL}  // Terminator for the array
	};
	// Example usage:
	const int valuesA[] = {1, 2, 3, -1};  // Example values for SETA
	read_set(SETA, valuesA);

	// Print SETA
	print_set(SETA);

	// Perform union of SETA and SETB into SETC
	cmd[0].func(SETC, SETA, SETB);
	print_set(SETC);

	// Perform other operations as needed
	// Example: Symmetric difference of SETA and SETB into SETD
	cmd[3].func(SETD, SETA, SETB);
	print_set(SETD);

	return 0;