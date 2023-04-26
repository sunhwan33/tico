#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ticoSimulator.h"

void convertStruct(char **strings_array, int max_numbers)
{ // a function to convert element in array, into struct instruct

    unionLine *lineArray[max_numbers];
    char token[64];
    int i;
    for (i = 0; i <= max_numbers; i++)
    {
        lineArray[i] = malloc(sizeof(unionLine));
        char *p;
        //printf("%d %s\n", i, strings_array[i]); // delete it later, just to check array element by index
        if (strings_array[i] != NULL)
        {
            printf("%d : ", i);
            printf("%s\n", strings_array[i]);

            p = strchr(strings_array[i], ' ');
            if (p != NULL)
            {
                memcpy(token, strings_array[i], p - strings_array[i]);
                token[p - strings_array[i]] = '\0';
            }
            else
            {
                strcpy(token, strings_array[i]);
            }
        }
        else
        {
            token[0] = '\0';
        }

        char *value = strings_array[i];

        unionLine *l = malloc(sizeof(unionLine));
        instrucToken *k = (instrucToken *)malloc(sizeof(instrucToken));

        if (strcmp(token, "READ") == 0)
        {
            k->instruction = READ;
            char *ins = strtok(strings_array[i], " ");
            char *address_str = strtok(NULL, " ");
            int address = atoi(address_str);
            k->md = address;
        }
        else if (strcmp(token, "WRITE") == 0)
        {
            k->instruction = WRITE;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
        }
        else if (strcmp(token, "ASSIGN") == 0)
        {
            k->instruction = ASSIGN;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *word = strtok(NULL, " ");
            k->c = word;
        }
        else if (strcmp(token, "MOVE") == 0)
        {
            k->instruction = MOVE;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *source = strtok(NULL, " ");
            k->ms = atoi(source);
        }
        else if (strcmp(token, "LOAD") == 0)
        {
            k->instruction = LOAD;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *source = strtok(NULL, " ");
            k->ms = atoi(source);
        }
        else if (strcmp(token, "STORE") == 0)
        {
            k->instruction = STORE;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *source = strtok(NULL, " ");
            k->ms = atoi(source);
        }
        else if (strcmp(token, "ADD") == 0)
        {
            k->instruction = ADD;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *first = strtok(NULL, " ");
            k->mx = atoi(first);
            char *second = strtok(NULL, " ");
            k->my = atoi(second);
        }
        else if (strcmp(token, "MINUS") == 0)
        {
            k->instruction = MINUS;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *first = strtok(NULL, " ");
            k->mx = atoi(first);
            char *second = strtok(NULL, " ");
            k->my = atoi(second);
        }
        else if (strcmp(token, "MULT") == 0)
        {
            k->instruction = MULT;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *first = strtok(NULL, " ");
            k->mx = atoi(first);
            char *second = strtok(NULL, " ");
            k->my = atoi(second);
        }
        else if (strcmp(token, "MOD") == 0)
        {
            k->instruction = MOD;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *first = strtok(NULL, " ");
            k->mx = atoi(first);
            char *second = strtok(NULL, " ");
            k->my = atoi(second);
        }
        else if (strcmp(token, "EQ") == 0)
        {
            k->instruction = EQ;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *first = strtok(NULL, " ");
            k->mx = atoi(first);
            char *second = strtok(NULL, " ");
            k->my = atoi(second);
        }
        else if (strcmp(token, "LESS") == 0)
        {
            k->instruction = LESS;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *first = strtok(NULL, " ");
            k->mx = atoi(first);
            char *second = strtok(NULL, " ");
            k->my = atoi(second);
        }
        else if (strcmp(token, "JUMP") == 0)
        {
            k->instruction = JUMP;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
        }
        else if (strcmp(token, "JUMPIF") == 0)
        {
            k->instruction = JUMPIF;
            k->instruction = JUMP;
            char *instruction = strtok(strings_array[i], " ");
            char *address = strtok(NULL, " ");
            k->md = atoi(address);
            char *source = strtok(NULL, " ");
            k->ms = atoi(source);
        }
        else if (strcmp(token, "TERM") == 0)
        {
            k->instruction = TERM;
        }
        else
        {
            if (token[0] == '\0')
            {
                k->c = "null";
                l->value = "null";
            }
            else
            {
                k->instruction = TEXT;
                k->c = value;
                l->value = value;
            }
        }

        l->instructLine = k;
        lineArray[i] = l;
    }

    printf("out of loop\n");  //not going out of loop, stuck at the last index

    if (lineArray != NULL)
    {
        printf("redirecting to cursor...\n");
        cursor(lineArray);
    }
    else
    {
        printf("Something went wrong!\n");
        exit(-1);
    }

    for (i = 0; i <= max_numbers; i++)
    {
        free(lineArray[i]->instructLine);
        free(lineArray[i]);
    }
}

void cursor(unionLine **lineArray)
{
    int cc = 0;
    while(lineArray[cc] != NULL) {
        switch (lineArray[cc]->instructLine->instruction)
        {
        case READ:
            /* code */
            cc++;
            continue;
        case WRITE:
            /* code */
            cc++;
            continue;
        case ASSIGN:
            /* code */
            cc++;
            continue;
        case MOVE:
            /* code */
            cc++;
            continue;
        case LOAD:
            /* code */
            cc++;
            continue;
        case STORE:
            /* code */
            cc++;
            continue;
        case ADD:
            /* code */
            cc++;
            continue;
        case MINUS:
            /* code */
            cc++;
            continue;
        case MULT:
            /* code */
            cc++;
            continue;
        case MOD:
            /* code */
            cc++;
            continue;
        case EQ:
            /* code */
            cc++;
            continue;
        case LESS:
            /* code */
            cc++;
            continue;
        case JUMP:
            /* code */
            cc = lineArray[cc]->instructLine->md;
            continue;
        case JUMPIF:
            /* code */
            continue;
        case TERM:
            exit(EXIT_SUCCESS);
            continue;
        default:
            cc++;
            continue;
        }
    }
}

void welcome()
{
    printf("          (                 )   \n");
    printf("  *   )   )\\ )     (     ( /(   \n");
    printf("` )  /(  (()/(     )\\    )\\())  \n");
    printf(" ( )(_))  /(_))  (((_)  ((_)\\   \n");
    printf("(_(_())  (_))    )\\___    ((_)  \n");
    printf("|_   _|  |_ _|  ((/ __|  / _ \\  \n");
    printf("  | |     | |    | (__  | (_) | \n");
    printf("  |_|    |___|    \\___|  \\___/  \n\n");
}