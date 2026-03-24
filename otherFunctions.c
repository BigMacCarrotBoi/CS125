/***************************************
This file contains all the user-made
functions that will be called later
in the maincode.c program.
***************************************/

#include <stdio.h>
#include "asciiArt.h"
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
	// Add ascii art here.
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



/**
 * Reads the content of a text file into a dynamically allocated string.
 * Remember to free() the returned pointer!
 */

/**
 * Loads three frames and cycles through them.
 */
 
 char* frame(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open %s\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, file);
        buffer[length] = '\0';
    }
    fclose(file);
    return buffer;
}
 
void menuIntro(int loops, int speed_ms) {
    const char* f1 = "heart1.txt";
    const char* f2 = "heart2.txt";
    const char* f3 = "heart3.txt";
    const char* f4 = "epsteinq.txt";
    const char* f5 = "clinnon.txt";
    const char* f6 = "jackon.txt";
    
    char* frames[6];
    frames[0] = frame(f1);
    frames[1] = frame(f2);
    frames[2] = frame(f3);
    frames[3] = frame(f4);
    frames[4] = frame(f5);
    frames[5] = frame(f6);

    int i = 0; int j = 0;

    // Error checking
    for (i = 0; i < 6; i++) {
        if (frames[i] == NULL) return; 
    }

    printf("\033[?25l"); // Hide cursor

    for (i = 0; i < loops; i++) {
        for (j = 0; j < 6; j++) {
            // Move cursor to top-left and clear screen
            printf("\033[H\033[J");
            printf("%s\n", frames[j]);
            fflush(stdout);
            usleep(speed_ms * 1000);
		clearscreen();
        }
    }

    printf("\033[?25h"); // Show cursor

    // Clean up memory
    for (i = 0; i < 6; i++) {
        free(frames[i]);
    } 

    const char *text = "Welcome to the chatbot!\nThis game allows you to talk to a variety of people and build relationships with them.\n";

    while (*text != '\0') {
        printf("%c", *text);
        fflush(stdout);
        usleep(30000); 
        text++;
    }
}
