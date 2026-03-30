/****************************************************************************
* File:    mainCode.c
* Authors:  Brooke Angel, Sophia Eads, Jhonny Li
* Purpose: This is a famous people talking simulator game.
* Version:    1.0 March 1, 2026
* Resources: Coding sites, C language handbooks, youtube.
****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "progressStruct.h"
#include "otherFunctions.c"
#include "epsteinRoute.h"
#include "clintonRoute.h"
#include "jacksonRoute.h"
#include "asciiArt.h"

// ================= MAIN =================
int main() {
    srand(time(NULL));
    clearscreen();

    menuIntro(2, 300);

    Progress progress = {0};
    int slot = -1;

    while (postChoic != 4) {
        int menuChoice = menu();

        if (menuChoice == 1) {
            slot = newGame(&progress);
        }
        else if (menuChoice == 2) {
            slot = listSaves();
            progress = loadGame(slot);
        }
        else if (menuChoice == 3) {
            deleteSave();
            continue;
        }
        else {
            return 0;
        }

        // ================= GAME LOOP =================
        while (postChoice != 4) {
            clearscreen();

            int choice = 0;
            char artFile[32];
            char character[20];

            printf("\nChoose character:\n");
            if (choice == 1 && progress.epsteinDone) {
                printf("\nYou have already completed Epstein's route.\n");
                continue;
            }
            if (choice == 2 && progress.clintonDone) {
                printf("\nYou have already completed Clinton's route.\n");
                continue;
            }
            if (choice == 3 && progress.jacksonDone) {
                printf("\nYou have already completed Jackson's route.\n");
                continue;
            }
            printf("1. Epstein\n2. Bill Clinton\n3. Michael Jackson\n4. Back to Menu\n");
            printf("Choice: ");
            scanf("%d", &choice);

            if (choice == 4) break;

            if (choice == 1) strcpy(character, "Epstein");
            if (choice == 2) strcpy(character, "Bill Clinton");
            if (choice == 3) strcpy(character, "Michael Jackson");

            printf("\nYou walk up to %s catching their attention...\n", character);

            if (choice == 1) strcpy(artFile, "artDir/epstein.txt");
            if (choice == 2) strcpy(artFile, "artDir/clinton.txt");
            if (choice == 3) strcpy(artFile, "artDir/jackson.txt");

            printChArt(artFile, 35);

            // ===== ROUTES =====
            if (choice == 1) {
                runEpstein(&progress, slot);
            }
            else if (choice == 2) {
                runClinton(&progress, slot);
            }
            else if (choice == 3) {
                runJackson(&progress, slot);
            }

            printf("\n1. Talk to someone else\n2. Save & Continue\n3. Main Menu\n4. Quit\nChoice: ");
            int postChoice;
            scanf("%d", &postChoice);

            saveGame(slot, &progress);

            if (postChoice == 1) continue;
            if (postChoice == 2) continue;
            if (postChoice == 3) break;
            if (postChoice == 4) return 0;
        }
    }

    return 0;
}
