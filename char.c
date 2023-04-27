#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned char* extractString(unsigned char* str) {
    unsigned char* newStr = malloc(sizeof(unsigned char) * strlen(str)); // allocate memory for new string
    int startIndex = strchr((char*)str, '\"') - (char*)str + 1; // find index of first quote and add 1 to skip it
    int endIndex = strchr((char*)(str + startIndex), '\"') - (char*)str; // find index of second quote
    strncpy((char*)newStr, (char*)(str + startIndex), endIndex - startIndex); // copy substring between quotes to new string
    newStr[endIndex - startIndex] = '\0'; // null-terminate new string
    return newStr;
}

int  main(){
    char s[3];
    //scanf("%s", s);
    //gets(s);
    unsigned char c[] = "\"127\"";
    unsigned char b = 3;
    printf("%s\n", extractString(c));
    /*for (int i =0;i<10;i++){
        printf("%d", c%b);
        
        //printf("%d\n", i);
        //if(i==1) i = 8;
    }*/
    //int a = atoi(c);
    printf("%d\n", c);
}