#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* extractString(char * str) {
    char* newStr = malloc(sizeof(char) * strlen(str)); // allocate memory for new string
    int startIndex = strchr(str, '\"') - str + 1; // find index of first quote and add 1 to skip it
    int endIndex = strchr(str + startIndex, '\"') - str; // find index of second quote
    strncpy(newStr, str + startIndex, endIndex - startIndex); // copy substring between quotes to new string
    newStr[endIndex - startIndex] = '\0'; // null-terminate new string
    return newStr;
}

int  main(){
    unsigned char c = "\"5\"";
    unsigned char a = extractString(c);
    printf("%d\n", atoi(a));
}
