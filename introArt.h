
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
 
void menuIntro(const char* f1, const char* f2, const char* f3, int loops, int speed_ms) {
    char* frames[3];
    frames[0] = frame(f1);
    frames[1] = frame(f2);
    frames[2] = frame(f3);
    int i = 0; int j = 0;

    // Error checking
    for (i = 0; i < 3; i++) {
        if (frames[i] == NULL) return; 
    }

    printf("\033[?25l"); // Hide cursor

    for (i = 0; i < loops; i++) {
        for (j = 0; j < 3; j++) {
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
    for (i = 0; i < 3; i++) {
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



#endif
