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
    struct
    {
        char *name;
        void (*func)(void);
    } cmd[] = {
            {"read_set",read_set},
            {"print_set",print_set},
            {"union_set",union_set},
            {"intersect_set",intersect_set},
            {"sub_set",sub_set},
            {"symdiff",symdiff}
    };
}
