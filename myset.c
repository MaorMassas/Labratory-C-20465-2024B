#include <stdio>
#include <stdlib.h>
#include <string.h>

set SETA,SETB,SETC,SETD,SETE,SETF;

struct{
    char name;
    set *set;
} sets[]={
    {'SETA',&SETA},
    {'SETB',&SETB},
    {'SETC',&SETC},
    {'SETD',&SETD},
    {'SETE',&SETE},
    {'SETF',&SETF},
    {'#',&NULL}
};

typedef struct tnode{
    set *set1;
    set *set2;
    set *result;
}parms;

parms temp_parm;

void read_set(void);
void print_set(void);
void union_set(void);
void intersect_set(void);
void sub_set(void);
void symdiff_set(void);
void stop(void);

set *get_sets(void);
void get_data(set *set)
void prn_set(set *set)

struct{
    char *name;
    void(func)(void);
}cmd[]={
    {"read_set",read_set},
    {"print_set",print_set},
    {"union_set",union_set},
    {"intersect_set",intersect_set},
    {"sub_set",sub_set},
    {"symdiff",symdiff},
    {"stop",stop},
    {"not_valid",not_valid}
};

void main(void)
{
    char command[MAX_CMD_LEN];
    int i;
    while(1){
        if(scanf("%s",command)==1){
            for(i=0;cmd[i].func!=NULL;i++)
                if(strcmp(command,cmd[i].name)==0)
                    break;
        }
    }
}

