/********************************
This is our file for ascii art.
********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void epstein() {
    FILE *fptr;
    char ch;

    fptr = fopen("epstein.txt", "r");

    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }

    fclose(fptr);

    return 0;
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

    return 0;
}


void mj() {
    FILE *fptr;
    char ch;

    fptr = fopen("mj.txt", "r");

    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    while ((ch = fgetc(fptr)) != EOF) {
        putchar(ch);
    }

    fclose(fptr);

    return 0;
}

