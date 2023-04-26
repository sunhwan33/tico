#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "sunticoSimulator.h"
/*enum instructions {
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
    TEXT,//15
}; */

int val_check[256]={-1}; // 만약 no address면 -1, empty value면 0, number value면 1 , instruction이면 2 
unsigned char get_op(char * op){
    
    if (strcmp(op, "READ") == 0) {
        return READ;
    } else if (strcmp(op, "WRITE") == 0) {
        return WRITE;
    } else if (strcmp(op, "ASSIGN") == 0) {
        return ASSIGN;
    } else if (strcmp(op, "MOVE") == 0) {
        return MOVE;
    } else if (strcmp(op, "LOAD") == 0) {
        return LOAD;
    } else if (strcmp(op, "STORE") == 0) {
        return STORE;
    } else if (strcmp(op, "ADD") == 0) {
        return ADD;
    } else if (strcmp(op, "MINUS") == 0) {
        return MINUS;
    } else if (strcmp(op, "MULT") == 0) {
        return MULT;
    } else if (strcmp(op, "MOD") == 0) {
        return MOD;
    } else if (strcmp(op, "EQ") == 0) {
        return EQ;
    } else if (strcmp(op, "LESS") == 0) {
        return LESS;
    } else if (strcmp(op, "JUMP") == 0) {
        return JUMP;
    } else if (strcmp(op, "JUMPIF") == 0) {
        return JUMPIF;
    } else if (strcmp(op, "TERM") == 0) {
        return TERM;
    } else if (strcmp(op, "TEXT") == 0) {
        return TEXT;
    }
}

bool is_all_whitespace(const char* str) {
    while (*str) {  // 문자열 끝에 도달할 때까지 반복
        if (!isspace(*str)) {  // 현재 문자가 공백이 아닌 경우
            return false;  // 문자열 전체가 공백으로 구성되어 있지 않음
        }
        str++;  // 다음 문자로 이동
    }
    return true;  // 문자열 전체가 공백으로 구성되어 있음
}
/*
1. strings_array르ㄹ 읽어오기
2. 빈칸이 아니면
    2-1. operator 구분.. p = strchr(strings_array[i], ' ');
            
            if (p != NULL) {
                printf("none empty string\n");
                memcpy(token, strings_array[i], p - strings_array[i]);
                token[p - strings_array[i]] = '\0'; // READ ( <- ex. READ 1 )
    2-2. op1 구분
    2-3. op2 구분
    2-4. op3 구분

3. 빈칸이면
*/

void convertStruct(char ** strings_array, int max_numbers) { //a function to convert element in array, into struct instruct 

    
    for (int i = 0; i <= max_numbers; i++) {
        //printf("max_num : %d\n", max_numbers);
        //printf("%d : %s\n", i, strings_array[i]);
        char *p;
        char token[6];
        if(strings_array[i]==NULL){ // no address
            continue;
        }

        if (!is_all_whitespace(strings_array[i])) { // is_all_whitespace == false
            
            
            printf("%d : ", i);
            printf("%s\n", strings_array[i]);
            printf("len : %d\n", strlen(strings_array[i]));
            p = strtok(strings_array[i], " "); 
            printf("%s\n", p); //-> ex. READ    "1"  WRITE
            
            
            /*
            we should make function to separate number value.
            now this code isn't , so segmentation fault appears
            if value is number, (not instructions). below code is not runned and only the value will be saved at Value[i].num
            
            */
            if(p[0]=='"') { // value is number
                // p = ;
                
                Value[i].num == atoi(p); //"1" -> 1
                printf("num : %d\n", Value[i].num);   //TODO remove ""
            }

            memcpy(token, p, 6);
            
            if(token[0]=='T' && strlen(token)==5) token[strlen(p)-1]='\0'; // if TERM && len = 5 error //it's only for solving error in example.txt
            else token[strlen(p)] = '\0'; // READ ( <- ex. READ 1 )

            //printf("token : %s\n", token);
            //printf("len_token : %d\n",strlen(token));
            Value[i].inst.operator= get_op(token);
            //printf("%d's OP : %u\n", i, Value[i].inst.operator );
            int count=1; // operand 1 or 2 or 3
            
            while(p != NULL ) {
               
                //printf("token's address : %p\n",token );
                //printf("%s\n", p);
                p = strtok(NULL, " ");
                if(p==NULL) break;
                memcpy(token, p, strlen(p));
                token[strlen(p)] = '\0';
                //printf("new token : %s\n", token);
                if(count==1){
                    Value[i].inst.operand1=atoi(p);
                    printf("%d's op1 : %u\n",i, Value[i].inst.operand1);
                } else if(count==2) {
                    Value[i].inst.operand2=atoi(p);
                    printf("%d's op2 : %u\n",i, Value[i].inst.operand2);
                } else if(count==3) {
                    Value[i].inst.operand3=atoi(p);
                    printf("%d's op3 : %u\n",i, Value[i].inst.operand3);
                }
                count++;        
            }
           
        }
        else { // strings_array = space 
            //printf("%d : empty space\n" , i);
                
                strcpy(token, " ");
                printf("token : %s\n", token);
            
        }
    
}

/*
1. address하나씩 실행. for i <=max_numbers
    1-1. value가 instruction이면 val_check ==2
        1-1-1. 각 instruction마다의 실행 나누기. ex. READ (0) -> receive input
        1-1-2. memory값 변경하기.
        1-1-3. invalid instruction -> perror, terminate program
    1-2. value가 number이면 // val_check == 1
    1-3. value가 없으면 // if valcheck == 0
    1-4. address도 배정된 것이 없으면) // if val_check == -1
2. 
*/
//void runinstruction(int max_number){

    //for (int i =0 ; i<=max_numbers ; i++){
        
        //if(is_all_whitespace())
        //if(Value[i].inst.)
    //}
//}
/*for(int i=0;i<=max_numbers;i++){
    printf("%d : %s\n", i, Value[i].num);
    printf("%d : %u\n", i, Value[i].inst.operator);
    printf("%d : %u\n", i, Value[i].inst.operand1);
    printf("%d : %u\n", i, Value[i].inst.operand2);
    printf("%d : %u\n", i, Value[i].inst.operand3);
}*/
}

/*if empty space
        else if number value
        else if istruction Value
            if READ scanf()
            if WIRTe
            case READ:
                scanf();
            case JUMPIF:
                if(unionArray[i]->value != 0) {
                    //to something
                }
            
        else if no adress*/