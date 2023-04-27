#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sunticoSimulator.h"

void convertStruct(char ** strings_array, int max_number);
void runinstruction(int max_number);
int main(int argc, char **argv) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **strings_array=NULL;
    int max_number = -1;
    
    // initialize the array to all zeros
    //strings_array = calloc(1, sizeof(char *));

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        int address_number;
        char string[100];
        int result = sscanf(line, "%d : %[^\n]", &address_number, string); 
        //printf("%d : %d\n", address_number, result);
       if (result == 2) {  // number & string are exist.
            // allocate memory for the string in the array
            strings_array = realloc(strings_array, (address_number + 1) * sizeof(char *));
            // allocate memory for the new string itself
            strings_array[address_number] = malloc((strlen(string) + 1) * sizeof(char));
            // copy the string to the array
            strcpy(strings_array[address_number], string);
            // update the maximum number seen so far
            if (address_number > max_number) {
                max_number = address_number;
            }
        } else if (result == 1) { // 빈칸이면.
            // allocate memory for the empty string in the array
            strings_array = realloc(strings_array, (address_number + 1) * sizeof(char *));
            // allocate memory for the new empty string itself
            strings_array[address_number] = malloc(sizeof(char));
            // set the empty string in the array
            strings_array[address_number][0] = '\0';
            // update the maximum number seen so far
            if (address_number > max_number) {
                max_number = address_number;
            }
        }
        //printf("txt str : %s\n", string);
        //printf("txt num : %d\n", address_number);
        //printf("address arr%p\n", strings_array);
        printf("str arr : %s\n\n", strings_array[address_number]);


}
fclose(fp);
convertStruct(strings_array, max_number);
free(strings_array);

runinstruction(max_number);

return 0;
}