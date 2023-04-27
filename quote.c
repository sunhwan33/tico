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

int main() {
    unsigned char str[] = "\"5\"";
    printf("Original string: %s\n", str);
    unsigned char* result = extractString(str);
    printf("%s\n", result);
    free(result); // free dynamically allocated memory
    return 0;
}
