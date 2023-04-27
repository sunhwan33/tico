#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
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
    NOINST,//15
}; */
void runinstruction(int max_number);
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
    } else {
        return NOINST;
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

char *extractString( char* str) {
    char* newStr = malloc(sizeof(char) * strlen(str)); // allocate memory for new string
    int startIndex = strchr((char*)str, '\"') - (char*)str + 1; // find index of first quote and add 1 to skip it
    int endIndex = strchr((char*)(str + startIndex), '\"') - (char*)str; // find index of second quote
    strncpy((char*)newStr, (char*)(str + startIndex), endIndex - startIndex); // copy substring between quotes to new string
    newStr[endIndex - startIndex] = '\0'; // null-terminate new string
    return newStr;
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
            val_check[i]=-1; // Basic number of val_check is -1
            continue;
        }

        if (!is_all_whitespace(strings_array[i])) { // is_all_whitespace == false
            
            
            //printf("%d : ", i);
            //printf("%s\n", strings_array[i]);
            //printf("len : %d\n", strlen(strings_array[i]));
            p = strtok(strings_array[i], " "); 
            //printf("%s\n", p); //-> ex. READ    "1"  WRITE
            
            
            
            if(p[0]=='"') { // value is number
               
                char * only_num = extractString(p);
                //printf("only num : %s\n", only_num);
                Value[i].num = atoi(only_num); //"1" -> 1
                val_check[i] = 1;
                free(only_num);
               // printf("num : %d\n", Value[i].num);   
            }
            
            else{
                val_check[i]=2;
                memcpy(token, p, 6);
                
                if(token[0]=='T' && strlen(token)==5) token[strlen(p)-1]='\0'; // if TERM && len = 5 error //it's only for solving error in example.txt
                else token[strlen(p)] = '\0'; // READ ( <- ex. READ 1 )

                //printf("token : %s\n", token);
                //printf("len_token : %d\n",strlen(token));
                Value[i].inst.operator= get_op(token);
                printf("%d's OP : %u\n", i, Value[i].inst.operator );
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
                        if(Value[i].inst.operator== 2) { // if ASSIGN
                            char * only_num = extractString(p); //"" !!!!!!!!!!!!!

                            Value[i].inst.operand2=atoi(only_num);
                            free(only_num);
                        }
                        else 
                            Value[i].inst.operand2=atoi(p);
                        printf("%d's op2 : %u\n",i, Value[i].inst.operand2);
                    } else if(count==3) {
                        Value[i].inst.operand3=atoi(p);
                        printf("%d's op3 : %u\n",i, Value[i].inst.operand3);
                    }
                    count++;        
                }
            }
        }
        else { // strings_array = space 
            //printf("%d : empty space\n" , i);
                val_check[i] = 0;
                strcpy(token, " ");
                //printf("token : %s\n", token);
            
        }
    
}


/*for(int i=0;i<=max_numbers;i++){
    printf("%d : %s\n", i, Value[i].num);
    printf("%d : %u\n", i, Value[i].inst.operator);
    printf("%d : %u\n", i, Value[i].inst.operand1);
    printf("%d : %u\n", i, Value[i].inst.operand2);
    printf("%d : %u\n", i, Value[i].inst.operand3);
}*/
}
/*
1. address하나씩 실행. for i <=max_numbers
    1-1. value가 instruction이면 val_check ==2
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
        1-1-1. 각 instruction마다의 실행 나누기. ex. READ (0) -> receive input
        1-1-2. memory값 변경하기.
        1-1-3. invalid instruction -> perror, terminate program
    1-2. value가 number이면 // val_check == 1
    1-3. value가 없으면 // if valcheck == 0
    1-4. address도 배정된 것이 없으면) // if val_check == -1
2. 
*/
void runinstruction(int max_numbers){
    
   char v_num[3];
   int m, md, ms,mx,my;
   int8_t c;
    for (int i =0 ; i<=max_numbers ; i++){
        if(val_check[i] ==2 ){ // if value is instruction
            //printf("^^^^^^^^\n");
            switch (Value[i].inst.operator)
            {
            case 0://OK . READ [m] :receive a number from user and store it [m] (i.e., on address m)
                /* code */
                //printf("before val[0] : %u\n", Value[0].num);
                //scanf("%s", v_num);
                //gets(v_num);
                scanf("%s", v_num);
                //printf("v_num : %s\n",v_num);
                m = Value[i].inst.operand1;
                //printf("m : %d\n", m);
                Value[m].num = atoi(v_num);
                val_check[m] = 1;
                //printf("after val[m] : %u\n", Value[0].num);
                break;
            case 1://OK . WRITE[m]: print the number at [m] 
                /* code */
                m = Value[i].inst.operand1;
                
                printf("WRITE : %d\n", Value[m].num);
                
                break;
            case 2://OK. ASSIGN [m] "c": put a number c to [m] 
                /* code */
                c = Value[i].inst.operand2;
                m = Value[i].inst.operand1;
                Value[m].num = c;
                val_check[m] = 1;
                
                break;
            case 3: //OK. MOVE [md] [ms]: put the value at [ms] to [md] // move 24 20 
                /* code */
                md = Value[i].inst.operand1; //24
                ms = Value[i].inst.operand2; //20
                Value[md].num = Value[ms].num;
                val_check[md] = 1;
                
                break;
            
            case 4: //OK. LOAD [md] [ms]: read an address stored at [ms], and put the value at the address to [md] 
                /* code */
                md = Value[i].inst.operand1; //24
                ms = Value[i].inst.operand2; //20
                c = Value[ms].num;
                Value[md].num = c;
                val_check[md]=1; // value is number
                
                break;
            case 5: //OK. STORE [md] [ms]: read an address stored at [md], and put the value at [ms] to the address
                /* code */
                md = Value[i].inst.operand1; //24
                ms = Value[i].inst.operand2; //20
                c = Value[md].num;
                Value[ms].num = c;
                val_check[ms]=1; // value is number
                
                break;
            case 6: //OK. ADD [md] [mx] [my]: add the values at [mx] and [my], and put the result to [md]
                /* code */
                md = Value[i].inst.operand1; 
                mx = Value[i].inst.operand2; 
                my = Value[i].inst.operand3; 
                Value[md].num = Value[mx].num + Value[my].num;
                val_check[md]=1; // value is number
                //printf("%d\n", Value[md].num);
                break;
            case 7: //OK. MINUS [md] [mx] [my]: subtract the value at [my] from the value at [mx], and put the result to [md]
                /* code */
                md = Value[i].inst.operand1; 
                mx = Value[i].inst.operand2; 
                my = Value[i].inst.operand3; 
                Value[md].num = Value[mx].num - Value[my].num;
                val_check[md]=1; // value is number
                //printf("%d\n", Value[md].num);
               break;
            case 8://OK. MULT [md] [mx] [my]: multiply the value at [mx] by the value at [my] and put the result to [md]
                /* code */ 
                md = Value[i].inst.operand1; 
                mx = Value[i].inst.operand2; 
                my = Value[i].inst.operand3;
                Value[md].num = Value[mx].num * Value[my].num;
                val_check[md]=1; // value is number
                
                break;
            case 9: //OK. MOD [md] [mx] [my]: Put the value at [mx] modulus the value at [my] to [md]
                /* code */
                md = Value[i].inst.operand1; 
                mx = Value[i].inst.operand2; 
                my = Value[i].inst.operand3;
                Value[md].num = Value[mx].num % Value[my].num;
                val_check[md]=1; // value is number
                break;
            case 10: //OK. EQ [md] [mx] [my]: Put 1 to [md] if two values at [mx] and [my] are the same. Otherwise, put 0 to [md]
                /* code */
                md = Value[i].inst.operand1; 
                mx = Value[i].inst.operand2; 
                my = Value[i].inst.operand3;
                if(Value[mx].num==Value[my].num) 
                    Value[md].num = 1;
                else 
                    Value[md].num = 0;

                val_check[md]=1; // value is number
                //printf("%d\n", Value[md].num);
                break;
            case 11: //OK.  LESS [md] [mx] [my]: Put 1 to [md] if the value at [mx] is less than the value at [my]. Otherwise, put 0 to [md]
                /* code */
                md = Value[i].inst.operand1; 
                mx = Value[i].inst.operand2; 
                my = Value[i].inst.operand3;
                if(Value[mx].num < Value[my].num) 
                    Value[md].num = 1;
                else 
                    Value[md].num = 0;
                val_check[md]=1; // value is number
                //printf("%d\n", Value[md].num); //how 대소비교 음수양수
                break;
            case 12://OK. JUMP [m]: execute the instruction at [m] for the next turn
                /* code */
                m = Value[i].inst.operand1;
                i = m-1;
               // cc = lineArray[cc]->instructLine->md;
                break;
            case 13: //OK. JUMPIF [m][c]: execute the instruction at [m] for the next turn, if the value at [c] is not zero
                /* code */
                m = Value[i].inst.operand1;
                my =  Value[i].inst.operand2;
                c = Value[my].num;
                if(c!=0){
                    i = m-1;
                }
                break;
            case 14://TERM: terminate the program execution
                exit(EXIT_SUCCESS);
                break;
            case 15: //invalid instruction
                perror("Invalid Instruction");
                exit(1);
                break;
            
            /*default:
                //cc++;
                
                break;*/
            }
        }
        /*else if (val_check == 1) { // if value is number
            continue;
        }
        else if (val_check == 0) { // if no value
            continue;
        }
        else if (val_check == -1){ //  if no address
            continue;
        }*/
       
    }
    
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