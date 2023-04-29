#include <stdio.h>
#include <stdint.h>

enum instructions {
    READ, //0
    WRITE,  //1
    ASSIGN,//2
    MOVE,//3
    LOAD,//4
    STORE,//5
    ADD,//6
    MINUS,//7
    MULT,//8
    MOD,//9
    EQ,//10
    LESS,//11
    JUMP,//12
    JUMPIF,//13
    TERM,//14
    NOINST//15
};

struct Instruction{ 
  enum instructions operator;
  
  unsigned char operand1; 
  unsigned char operand2;  
  unsigned char operand3;  
};

union { 
  int8_t num; 
  struct Instruction inst; 
} Value[256];

void convertStruct(char ** strings_array, int max_number);
void runinstruction(int max_number);

char *extractString( char* str) ;