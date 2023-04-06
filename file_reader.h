#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

/*
 *
 * Precondition:
 *   @param char* filename: defines the file name that is going to read
 *   @param char* data: data pointer for storing the related data into it
 *
 * Postcondition:
 *   user gets the related data by giving the first data's address.
 */

void readCSV(char *filename, char** data)
{

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(0);
    }

    char line[MAX_LINE_LENGTH];
    int index = 0;
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        data[index] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
        if (line != NULL)
        {
            strcpy(data[index], line);
            index++;
            
        }
    }

    fclose(fp);
}