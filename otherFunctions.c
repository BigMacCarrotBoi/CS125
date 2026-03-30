/***************************************
This file contains all the user-made
functions that will be called later
in the maincode.c program.
***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "asciiArt.h"
#include "progressStruct.h"

#define MAX_SAVES 3

const char *saveFiles[MAX_SAVES] = {
  "save1.txt", "save2.txt", "save3.txt"
};

void clearscreen() {
  system("clear");
}

void saveGame(int slot, Progress *p) {
  FILE *f = fopen(saveFiles[slot], "w");
    if (!f) return;

    fprintf(f, "%s\n", p->saveName);

    fprintf(f, "%d %d %d %d\n", p->d1, p->d2, p->d3, p->d4);
    fprintf(f, "%d %d %d %d\n", p->c1, p->c2, p->c3, p->c4);
    fprintf(f, "%d %d %d %d\n", p->j1, p->j2, p->j3, p->j4);

    fprintf(f, "%d %d\n", p->currentDialogue, p->inDialogueChoice);

    fclose(f);
}

void deleteSave() {
  int slot;
    printf("Enter save slot to delete (1-3): ");
    scanf("%d", &slot);

    if (slot < 1 || slot > 3) return;
      remove(saveFiles[slot - 1]);
      printf("Save deleted.\n");
}

int listSaves() {
    printf("\nSave Slots:\n");
    int i = 0;

    for (i = 0; i < MAX_SAVES; i++) {
        FILE *f = fopen(saveFiles[i], "r");
        if (f) {
            char name[50];
            fgets(name, sizeof(name), f);
            name[strcspn(name, "\n")] = 0;
            printf("%d. %s\n", i + 1, name);
            fclose(f);
        } else {
            printf("%d. [Empty]\n", i + 1);
        }
    }

    int choice;
    printf("Choose slot: ");
    scanf("%d", &choice);

    return choice - 1;
}

Progress loadGame(int slot) {
    Progress p = {0};

    FILE *f = fopen(saveFiles[slot], "r");
    if (!f) return p;

    fgets(p.saveName, sizeof(p.saveName), f);
    p.saveName[strcspn(p.saveName, "\n")] = 0;

    fscanf(f, "%d %d %d %d", &p.d1, &p.d2, &p.d3, &p.d4);
    fscanf(f, "%d %d %d %d", &p.c1, &p.c2, &p.c3, &p.c4);
    fscanf(f, "%d %d %d %d", &p.j1, &p.j2, &p.j3, &p.j4);

    fscanf(f, "%d %d", &p.currentDialogue, &p.inDialogueChoice);

    fclose(f);
    return p;
}

int newGame(Progress *p) {
    printf("Enter save name: ");
    scanf("%49s", p->saveName);

    int slot = listSaves();
    saveGame(slot, p);

    return slot;
}

int menu() {
    int choice;

    printf("\n1. New Game\n2. Load Game\n3. Delete Save\n4. Quit\nChoice: ");
    scanf("%d", &choice);

    return choice;
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
    	const char* f1 = "artDir/heart1.txt";
    	const char* f2 = "artDir/heart2.txt";
    	const char* f3 = "artDir/heart3.txt";
    	const char* f4 = "artDir/epsteinq.txt";
    	const char* f5 = "artDir/clinnon.txt";
    	const char* f6 = "artDir/jackon.txt";
    
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

// ================= EPSTEIN ENDING =================
void checkEpsteinEnding(Progress *p) {
    if (p->d1 == 1 && p->d2 == 1 && p->d3 == 1 && p->d4 == 1) {
        printf("\n[OBLIVIOUS ENDING]\n");
    }
    else if (p->d1 == 2 && p->d2 == 2 && p->d3 == 2 && p->d4 == 2) {
        printf("\n[GOOD ENDING]\n");
    }
    else if (p->d1 == 3 && p->d2 == 3 && p->d3 == 3 && p->d4 == 3) {
        printf("\n[BAD ENDING]\n");
    }
    else {
        printf("\n[NEUTRAL ENDING]\n");
    }
}

// ================= CLINTON ENDING =================
void checkClintonEnding(Progress *p) {
    if (p->c1 == 1 && p->c2 == 1 && p->c3 == 1 && p->c4 == 1) {
        printf("\n[CLINTON: OBLIVIOUS ENDING]\n");
    }
    else if (p->c1 == 2 && p->c2 == 2 && p->c3 == 2 && p->c4 == 2) {
        printf("\n[CLINTON: GOOD ENDING]\n");
    }
    else if (p->c1 == 3 && p->c2 == 3 && p->c3 == 3 && p->c4 == 3) {
        printf("\n[CLINTON: BAD ENDING]\n");
    }
    else {
        printf("\n[CLINTON: NEUTRAL ENDING]\n");
    }
}

// ================= JACKSON ENDING =================
void checkJacksonEnding(Progress *p) {
    if (p->j1 == 1 && p->j2 == 1 && p->j3 == 1 && p->j4 == 1) {
        printf("\n[JACKSON: OBLIVIOUS ENDING]\n");
    }
    else if (p->j1 == 2 && p->j2 == 2 && p->j3 == 2 && p->j4 == 2) {
        printf("\n[JACKSON: GOOD ENDING]\n");
    }
    else if (p->j1 == 3 && p->j2 == 3 && p->j3 == 3 && p->j4 == 3) {
        printf("\n[JACKSON: BAD ENDING]\n");
    }
    else {
        printf("\n[JACKSON: NEUTRAL ENDING]\n");
    }
}

// ================= EPSTEIN ROUTER =================
void runEpstein(Progress *p, int slot) {
    int exitFlag = 0;

    // Resume support
    if (p->currentDialogue == 1) exitFlag = epsteinD1(p->d1, p, slot);
    if (!exitFlag && p->currentDialogue <= 1) exitFlag = epsteinD1(p->d1, p, slot);

    if (!exitFlag && p->currentDialogue <= 2) exitFlag = epsteinD2(p->d2, p, slot);
    if (!exitFlag && p->currentDialogue <= 3) exitFlag = epsteinD3(p->d3, p, slot);
    if (!exitFlag && p->currentDialogue <= 4) exitFlag = epsteinD4(p->d4, p, slot);

    if (!exitFlag) {
        checkEpsteinEnding(p);
    }
}

// ================= CLINTON ROUTER =================
void runClinton(Progress *p, int slot) {
    int exitFlag = 0;

    if (p->currentDialogue == 1) exitFlag = clintonD1(p->c1, p, slot);
    if (!exitFlag && p->currentDialogue <= 1) exitFlag = clintonD1(p->c1, p, slot);

    if (!exitFlag && p->currentDialogue <= 2) exitFlag = clintonD2(p->c2, p, slot);
    if (!exitFlag && p->currentDialogue <= 3) exitFlag = clintonD3(p->c3, p, slot);
    if (!exitFlag && p->currentDialogue <= 4) exitFlag = clintonD4(p->c4, p, slot);

    if (!exitFlag) {
        checkClintonEnding(p);
    }
}

// ================= JACKSON ROUTER =================
void runJackson(Progress *p, int slot) {
    int exitFlag = 0;

    if (p->currentDialogue == 1) exitFlag = jacksonD1(p->j1, p, slot);
    if (!exitFlag && p->currentDialogue <= 1) exitFlag = jacksonD1(p->j1, p, slot);

    if (!exitFlag && p->currentDialogue <= 2) exitFlag = jacksonD2(p->j2, p, slot);
    if (!exitFlag && p->currentDialogue <= 3) exitFlag = jacksonD3(p->j3, p, slot);
    if (!exitFlag && p->currentDialogue <= 4) exitFlag = jacksonD4(p->j4, p, slot);

    if (!exitFlag) {
        checkJacksonEnding(p);
    }
}
