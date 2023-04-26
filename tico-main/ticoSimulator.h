#include <stdio.h>

enum instructions {
    READ,
    WRITE, 
    ASSIGN,
    MOVE,
    LOAD,
    STORE,
    ADD,
    MINUS,
    MULT,
    MOD,
    EQ,
    LESS,
    JUMP,
    JUMPIF,
    TERM,
    TEXT,
};

typedef struct instruct {
    enum instructions instruction;
    int mx;
    int my;
    int md;
    int ms;
    char * c;
} instrucToken;

typedef union line {
    instrucToken * instructLine;
    char * value;
} unionLine;

void welcome();

void convertStruct(char ** strings_array, int max_number);

void cursor (unionLine ** lineArray);