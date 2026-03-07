/***************************************
This file contains all the user-made
functions that will be called later
in the maincode.c program.
***************************************/

#include <stdio.h>
#include "asciiart.h"
#include "progressStruct.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/* This function clears the terminal screen for the user. */
void clearscreen() {

        system("clear");

}


void loadFile() {

        printf("");

}


void menu() {

        int choice=0;
        printf("\nMenu\n1. New Game\n2. Load Game\n3. Quit Game\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
                case 1:
                        break;
                case 2:
                        loadFile();
                case 3:
                        printf("Goodbye\n");
                        exit(EXIT_SUCCESS);
                default:
                        printf("Please try again and choose 1, 2, or 3.\n");
                        exit(EXIT_SUCCESS);
                }
}


