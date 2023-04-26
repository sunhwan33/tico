#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ticoSimulator.h"

int main(int argc, char **argv) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **strings_array = NULL;
    int max_number = -1;

    // initialize the array to all zeros
    strings_array = calloc(1, sizeof(char *));

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        int number;
        char string[100];
        int result = sscanf(line, "%d : %[^\n]", &number, string);
        if (result == 2) {
            // allocate memory for the string in the array
            strings_array = realloc(strings_array, (number + 1) * sizeof(char *));
            // allocate memory for the new string itself
            strings_array[number] = malloc((strlen(string) + 1) * sizeof(char));
            // copy the string to the array
            strcpy(strings_array[number], string);
            // update the maximum number seen so far
            if (number > max_number) {
                max_number = number;
            }
        } else if (result == 1) {
            // allocate memory for the empty string in the array
            strings_array = realloc(strings_array, (number + 1) * sizeof(char *));
            // allocate memory for the new empty string itself
            strings_array[number] = malloc(sizeof(char));
            // set the empty string in the array
            strings_array[number][0] = '\0';
            // update the maximum number seen so far
            if (number > max_number) {
                max_number = number;
            }
        }
    }

    // cleanup
    fclose(fp);
    if (line) free(line);
	// welcome();
    
	// //print the strings in the array
	// printf("%s's content has been successfully extracted\n", argv[1]);
    // for (int i = 0; i <= max_number; i++) {
    //     if (strings_array[i] != NULL) {
    //         printf("%d : %s\n", i, strings_array[i]);
    //         //free(strings_array[i]);
    //     }
    // }

    // //try to make a gap between printing the file and trying to convert them
    // printf("\n\n");
	
    //convert lines into unionLine according to the first word on every line
	convertStruct(strings_array, max_number);
    free(strings_array);

    return 0;
}