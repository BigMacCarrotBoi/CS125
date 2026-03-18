//Printing text letter by letter
//useful for representing character speech

#ifndef ASCII_SPEAK_H
#define ASCII_SPEAK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

void speak(const char *filename, const char *start_phrase, const char *stop_phrase) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read file into memory
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    if (buffer == NULL) {
        fclose(file);
        return;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);

    // 1. Find the start phrase
    char *start_ptr = strstr(buffer, start_phrase);
    if (start_ptr == NULL) {
        printf("Start phrase '%s' not found.\n", start_phrase);
        free(buffer);
        return;
    }

    // 2. Offset to start after the start phrase to omit it from printing
    start_ptr += strlen(start_phrase);

    // 3. Find the stop phrase (searching only from the start_ptr onwards)
    char *stop_ptr = strstr(start_ptr, stop_phrase);
    if (stop_ptr == NULL) {
        printf("\nStop phrase '%s' not found. Printing to end of file...\n", stop_phrase);
    }

    // 4. Print letter by letter until we hit the stop_ptr
    // If stop_ptr is NULL, it will print until the end of the string ('\0')
    while (*start_ptr != '\0' && start_ptr != stop_ptr) {
        printf("%c", *start_ptr);
        fflush(stdout);
        usleep(30000); 
        start_ptr++;
    }

    free(buffer);
}

#endif
//#include "print1.h"

//int main() {
//  Print letter by letter starting after the phrase "SECTION1".
//  You can choose what to start printing after

//  speak("art.txt", "SECTION1", "SECTION1END");

//  return 0;
//}

