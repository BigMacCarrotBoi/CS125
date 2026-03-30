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

// ================= BUFFER CLEAR =================
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ================= CLEAR SCREEN =================
void clearscreen() {
    system("clear");
}

// ================= VALIDATION =================
int validateSaveName(const char *name) {
    int i;

    if (strlen(name) == 0) {
        printf("Save name cannot be empty.\n");
        return 0;
    }

    for (i = 0; name[i] != '\0'; i++) {
        if (!(name[i] >= 'A' && name[i] <= 'Z') &&
            !(name[i] >= 'a' && name[i] <= 'z') &&
            !(name[i] >= '0' && name[i] <= '9') &&
            name[i] != '_') {

            printf("Invalid character detected.\n");
            printf("Only letters, numbers, and underscores allowed.\n");
            return 0;
        }
    }

    return 1;
}

// ================= NAME EXISTS =================
int nameExists(const char *name) {
    int i;

    for (i = 0; i < MAX_SAVES; i++) {
        FILE *f = fopen(saveFiles[i], "r");

        if (f) {
            char existing[50];

            if (fgets(existing, sizeof(existing), f)) {
                existing[strcspn(existing, "\n")] = 0;

                if (strcmp(existing, name) == 0) {
                    fclose(f);
                    return 1;
                }
            }

            fclose(f);
        }
    }

    return 0;
}

// ================= SAVE =================
void saveGame(int slot, Progress *p) {
    FILE *f;

    if (slot < 0 || slot >= MAX_SAVES) return;

    f = fopen(saveFiles[slot], "w");
    if (!f) {
        printf("Error saving file.\n");
        return;
    }

    fprintf(f, "%s\n", p->saveName);

    fprintf(f, "%d %d %d %d\n", p->d1, p->d2, p->d3, p->d4);
    fprintf(f, "%d %d %d %d\n", p->c1, p->c2, p->c3, p->c4);
    fprintf(f, "%d %d %d %d\n", p->j1, p->j2, p->j3, p->j4);

    fprintf(f, "%d %d\n", p->e_currentDialogue, p->e_inChoice);
    fprintf(f, "%d %d\n", p->c_currentDialogue, p->c_inChoice);
    fprintf(f, "%d %d\n", p->j_currentDialogue, p->j_inChoice);

    fprintf(f, "%d %d %d\n", p->epsteinDone, p->clintonDone, p->jacksonDone);

    fclose(f);

    printf("\n--Data Autosaved to slot %d (%s)\n", slot + 1, p->saveName);
}

// ================= DELETE =================
void deleteSave() {
    int slot;

    while (1) {
        printf(">> Enter save slot to delete (1-3): ");

        if (scanf("%d", &slot) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        if (slot < 1 || slot > 3) {
            printf("Invalid slot.\n");
            continue;
        }

        break;
    }

    clearInputBuffer();

    if (remove(saveFiles[slot - 1]) == 0)
        printf("Save deleted.\n");
    else
        printf("No save found in that slot.\n");
}

// ================= LIST SAVES =================

int listSaves() {
    int i;
    int hasSave = 0;

    printf("\nSave Slots:\n");

    for (i = 0; i < MAX_SAVES; i++) {
        FILE *f = fopen(saveFiles[i], "r");

        if (f) {
            Progress temp = {0};
            hasSave = 1;

            fgets(temp.saveName, sizeof(temp.saveName), f);
            temp.saveName[strcspn(temp.saveName, "\n")] = 0;

            fscanf(f, "%d %d %d %d", &temp.d1, &temp.d2, &temp.d3, &temp.d4);
            fscanf(f, "%d %d %d %d", &temp.c1, &temp.c2, &temp.c3, &temp.c4);
            fscanf(f, "%d %d %d %d", &temp.j1, &temp.j2, &temp.j3, &temp.j4);

            fscanf(f, "%d %d", &temp.e_currentDialogue, &temp.e_inChoice);
            fscanf(f, "%d %d", &temp.c_currentDialogue, &temp.c_inChoice);
            fscanf(f, "%d %d", &temp.j_currentDialogue, &temp.j_inChoice);

            fscanf(f, "%d %d %d", &temp.epsteinDone, &temp.clintonDone, &temp.jacksonDone);

            fclose(f);

            printf("%d. %s [E:%s] [C:%s] [J:%s]\n",
                i + 1,
                temp.saveName,
                temp.epsteinDone ? "Done" : "Pending",
                temp.clintonDone ? "Done" : "Pending",
                temp.jacksonDone ? "Done" : "Pending"
            );
        } else {
            printf("%d. [Empty]\n", i + 1);
        }
    }

    if (!hasSave) {
        printf("\nNo save files found.\n");
        return -1;
    }

    int choice;

    // choose slot for load/save
    while (1) {
        printf("Choose slot (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        if (choice < 1 || choice > 3) {
            printf("Invalid slot.\n");
            continue;
        }

        clearInputBuffer();

        // check if file exists
        FILE *test = fopen(saveFiles[choice - 1], "r");
        if (!test) {
            printf("\nThat slot is empty. Returning to menu.\n");
            return -1;
        }

        fclose(test);
        break;
    }

    return choice - 1;
}

int listSavesNew() {
    int i;
    int hasSave = 0;

    printf("\nSave Slots:\n");

    for (i = 0; i < MAX_SAVES; i++) {
        FILE *f = fopen(saveFiles[i], "r");

        if (f) {
            Progress temp = {0};
            hasSave = 1;

            fgets(temp.saveName, sizeof(temp.saveName), f);
            temp.saveName[strcspn(temp.saveName, "\n")] = 0;

            fscanf(f, "%d %d %d %d", &temp.d1, &temp.d2, &temp.d3, &temp.d4);
            fscanf(f, "%d %d %d %d", &temp.c1, &temp.c2, &temp.c3, &temp.c4);
            fscanf(f, "%d %d %d %d", &temp.j1, &temp.j2, &temp.j3, &temp.j4);

            fscanf(f, "%d %d", &temp.e_currentDialogue, &temp.e_inChoice);
            fscanf(f, "%d %d", &temp.c_currentDialogue, &temp.c_inChoice);
            fscanf(f, "%d %d", &temp.j_currentDialogue, &temp.j_inChoice);

            fscanf(f, "%d %d %d", &temp.epsteinDone, &temp.clintonDone, &temp.jacksonDone);

            fclose(f);

            printf("%d. %s [E:%s] [C:%s] [J:%s]\n",
                i + 1,
                temp.saveName,
                temp.epsteinDone ? "Done" : "Pending",
                temp.clintonDone ? "Done" : "Pending",
                temp.jacksonDone ? "Done" : "Pending"
            );
        } else {
            printf("%d. [Empty]\n", i + 1);
        }
    }

	int listSaves() {
    int i;
    int hasSave = 0;

    printf("\nSave Slots:\n");

    for (i = 0; i < MAX_SAVES; i++) {
        FILE *f = fopen(saveFiles[i], "r");

        if (f) {
            Progress temp = {0};
            hasSave = 1;

            fgets(temp.saveName, sizeof(temp.saveName), f);
            temp.saveName[strcspn(temp.saveName, "\n")] = 0;

            fscanf(f, "%d %d %d %d", &temp.d1, &temp.d2, &temp.d3, &temp.d4);
            fscanf(f, "%d %d %d %d", &temp.c1, &temp.c2, &temp.c3, &temp.c4);
            fscanf(f, "%d %d %d %d", &temp.j1, &temp.j2, &temp.j3, &temp.j4);

            fscanf(f, "%d %d", &temp.e_currentDialogue, &temp.e_inChoice);
            fscanf(f, "%d %d", &temp.c_currentDialogue, &temp.c_inChoice);
            fscanf(f, "%d %d", &temp.j_currentDialogue, &temp.j_inChoice);

            fscanf(f, "%d %d %d", &temp.epsteinDone, &temp.clintonDone, &temp.jacksonDone);

            fclose(f);

            printf("%d. %s [E:%s] [C:%s] [J:%s]\n",
                i + 1,
                temp.saveName,
                temp.epsteinDone ? "Done" : "Pending",
                temp.clintonDone ? "Done" : "Pending",
                temp.jacksonDone ? "Done" : "Pending"
            );
        } else {
            printf("%d. [Empty]\n", i + 1);
        }
    }
		
    int choice;

    // choose slot for load/save
    while (1) {
        printf("Choose slot (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        if (choice < 1 || choice > 3) {
            printf("Invalid slot.\n");
            continue;
        }

        clearInputBuffer();
		
        break;
    }

    return choice - 1;
}


    if (!hasSave) {
        printf("\nNo save files found.\n");
        return -1;
    }

    int choice;

    // choose slot for load/save
    while (1) {
        printf("Choose slot (1-3): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        if (choice < 1 || choice > 3) {
            printf("Invalid slot.\n");
            continue;
        }

        clearInputBuffer();

        break;
    }

    return choice - 1;
}

// ================= LOAD =================
Progress loadGame(int slot) {
    Progress p = {0};
    FILE *f;

    if (slot < 0 || slot >= MAX_SAVES) return p;

    f = fopen(saveFiles[slot], "r");
    if (!f) return p;

    fgets(p.saveName, sizeof(p.saveName), f);
    p.saveName[strcspn(p.saveName, "\n")] = 0;

    fscanf(f, "%d %d %d %d", &p.d1, &p.d2, &p.d3, &p.d4);
    fscanf(f, "%d %d %d %d", &p.c1, &p.c2, &p.c3, &p.c4);
    fscanf(f, "%d %d %d %d", &p.j1, &p.j2, &p.j3, &p.j4);

    fscanf(f, "%d %d", &p.e_currentDialogue, &p.e_inChoice);
    fscanf(f, "%d %d", &p.c_currentDialogue, &p.c_inChoice);
    fscanf(f, "%d %d", &p.j_currentDialogue, &p.j_inChoice);

    fscanf(f, "%d %d %d", &p.epsteinDone, &p.clintonDone, &p.jacksonDone);

    fclose(f);

    return p;
}

// ================= NEW GAME =================
int newGame(Progress *p) {
    int slot;

    p->epsteinDone = 0;
    p->clintonDone = 0;
    p->jacksonDone = 0;

    while (1) {
        printf(">> Enter save name (letters/numbers/_ only): ");

        if (!fgets(p->saveName, sizeof(p->saveName), stdin))
            continue;

        p->saveName[strcspn(p->saveName, "\n")] = 0;

        if (!validateSaveName(p->saveName))
            continue;

        if (nameExists(p->saveName)) {
            printf("Name already exists.\n");
            continue;
        }

        break;
    }

    printf(">> Choose a slot to save:\n");
    slot = listSavesNew();

	saveGame(slot, p);

    return slot;
}

// ================= MENU =================
int menu() {
    int choice;

    while (1) {
        printf("\n1. New Game\n2. Load Game\n3. Delete Save\n4. Quit\nChoice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        if (choice < 1 || choice > 4) {
            printf("Invalid choice.\n");
            continue;
        }

        break;
    }

    clearInputBuffer();
    return choice;
}

// Reads the content of a text file into a dynamically allocated string.
 
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
        printf("\n[NEUTRAL ENDING]\nYou parted ways quietly.\n");
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
        printf("\n[CLINTON: NEUTRAL ENDING]\nYou parted ways quietly.\n");
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
        printf("\n[JACKSON: NEUTRAL ENDING]\nYou parted ways quietly.\n");
    }
}

// ================= EPSTEIN ROUTER =================
void runEpstein(Progress *p, int slot) {
    int exitFlag = 0;

    // Start from saved dialogue
    switch (p->e_currentDialogue) {
        case 0:
        case 1:
            exitFlag = epsteinD1(p->d1, p, slot);
            if (exitFlag) return;
        case 2:
            exitFlag = epsteinD2(p->d2, p, slot);
            if (exitFlag) return;
        case 3:
            exitFlag = epsteinD3(p->d3, p, slot);
            if (exitFlag) return;
        case 4:
            exitFlag = epsteinD4(p->d4, p, slot);
            if (exitFlag) return;
    }

    // Ending
    checkEpsteinEnding(p);

    // Reset after completion
    p->epsteinDone = 1;
    p->e_inChoice = 0;
    saveGame(slot, p);
}
// ================= CLINTON ROUTER =================
void runClinton(Progress *p, int slot) {
    int exitFlag = 0;

    // Start from saved dialogue
    switch (p->c_currentDialogue) {
        case 0:
        case 1:
            exitFlag = clintonD1(p->c1, p, slot);
            if (exitFlag) return;
        case 2:
            exitFlag = clintonD2(p->c2, p, slot);
            if (exitFlag) return;
        case 3:
            exitFlag = clintonD3(p->c3, p, slot);
            if (exitFlag) return;
        case 4:
            exitFlag = clintonD4(p->c4, p, slot);
            if (exitFlag) return;
    }

    // Ending
    checkClintonEnding(p);

    p->clintonDone = 1;
	p->c_inChoice = 0;
    saveGame(slot, p);
}

// ================= JACKSON ROUTER =================
void runJackson(Progress *p, int slot) {
    int exitFlag = 0;

    // Start from saved dialogue
    switch (p->j_currentDialogue) {
        case 0:
        case 1:
            exitFlag = jacksonD1(p->j1, p, slot);
            if (exitFlag) return;
        case 2:
            exitFlag = jacksonD2(p->j2, p, slot);
            if (exitFlag) return;
        case 3:
            exitFlag = jacksonD3(p->j3, p, slot);
            if (exitFlag) return;
        case 4:
            exitFlag = jacksonD4(p->j4, p, slot);
            if (exitFlag) return;
    }

    // Ending
    checkJacksonEnding(p);

    // Reset after completion
    p->jacksonDone = 1;
    p->j_inChoice = 0;
    saveGame(slot, p);
}
