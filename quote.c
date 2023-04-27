#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extractString( char* str) {
    char* newStr = malloc(sizeof(char) * strlen(str)); // allocate memory for new string
    int startIndex = strchr((char*)str, '\"') - (char*)str + 1; // find index of first quote and add 1 to skip it
    int endIndex = strchr((char*)(str + startIndex), '\"') - (char*)str; // find index of second quote
    strncpy((char*)newStr, (char*)(str + startIndex), endIndex - startIndex); // copy substring between quotes to new string
    newStr[endIndex - startIndex] = '\0'; // null-terminate new string
    return newStr;
}

int main() {
    char *str = "\"5\"";
    printf("Original string: %s\n", str);
    char *result = extractString(str);
    printf("%d\n",atoi(result));
    free(result); // free dynamically allocated memory
    return 0;
}