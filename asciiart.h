/********************************
This is our file for ascii art.
********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void epstein() {
    FILE *fptr;
    char ch;

    fptr = fopen("epsteinPool.txt", "r");

    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }

    fclose(fptr);

}


void clinton() {
    FILE *fptr;
    char ch;

    fptr = fopen("clinton.txt", "r");

    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }

    fclose(fptr);

}


void mj() {
    FILE *fptr;
    char ch;

    fptr = fopen("jackson.txt", "r");

    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }

    fclose(fptr);

}

