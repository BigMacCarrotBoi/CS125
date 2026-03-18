//   New ascii art header file that prints line by line

#ifndef ASCII_PRINTER_H
#define ASCII_PRINTER_H

#include <stdio.h>
#include <unistd.h> // Required for usleep()

/**
 * Prints a file line-by-line with a delay.
 * @param filename  Path to the .txt file.
 * @param delay_ms  Milliseconds to wait between lines.
 */
void print_ascii_lines(const char *filename, int delay_ms) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char buffer[1024]; // Buffer for one line of art
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
        
        // Force output to terminal immediately
        fflush(stdout);
        
        // usleep uses microseconds (1 ms = 1000 us)
        usleep(delay_ms * 1000);
    }

    fclose(file);
}

#endif
