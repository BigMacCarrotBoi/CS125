/****************************************************************************
* File:    mainCode.c
* Authors:  Brooke Angel, Sophia Eads, Jhonny Li
* Purpose: This is a famous people talking simulator game.
* Version:    1.0 March 1, 2026
* Resources: Coding sites, C language handbooks, youtube.
****************************************************************************/
/****************************************************************************
* File: mainCode.c
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

// ================= MENU =================
int main() {
    srand(time(NULL));
    clearscreen();

    menuIntro(2, 300);

    Progress progress = {0};
    int slot = -1;
    int menuChoice = 0;

    while (menuChoice != 4) {

        menuChoice = menu();

        if (menuChoice == 1) {
            slot = newGame(&progress);
        }
        else if (menuChoice == 2) {
            slot = listSaves();

            if (slot == -1) continue;

            progress = loadGame(slot);
        }
        else if (menuChoice == 3) {
            slot = listSaves();
            
            if (slot == -1) continue;
            
            deleteSave();
            
            continue;
        }
        else {
            return 0;
        }

        int postChoice = 0;

        // ================= GAME LOOP =================
        while (postChoice != 3) {
            clearscreen();

            int choice = 0;
            char artFile[32];
            char character[20];
            // choose character
            printf("\nChoose character:\n");
            printf("1. Epstein\n2. Bill Clinton\n3. Michael Jackson\n4. Back to Menu\n");
            printf("Choice: ");

            if (scanf("%d", &choice) != 1) {
                printf("Invalid input.\n");
                clearInputBuffer();
                continue;
            }

            clearInputBuffer();

            if (choice == 4) break;
            // checks story progress
            if (choice == 1 && progress.epsteinDone) {
                printf("\nYou already completed Epstein.\n");
                sleep(1);
                continue;
            }
            if (choice == 2 && progress.clintonDone) {
                printf("\nYou already completed Clinton.\n");
                sleep(1);
                continue;
            }
            if (choice == 3 && progress.jacksonDone) {
                printf("\nYou already completed Jackson.\n");
                sleep(1);
                continue;
            }

            if (choice == 1) strcpy(character, "Epstein");
            if (choice == 2) strcpy(character, "Bill Clinton");
            if (choice == 3) strcpy(character, "Michael Jackson");

            printf("\nYou walk up to %s...\n", character);
            // prints character art
            if (choice == 1) strcpy(artFile, "artDir/epstein.txt");
            if (choice == 2) strcpy(artFile, "artDir/clinton.txt");
            if (choice == 3) strcpy(artFile, "artDir/jackson.txt");

            printChArt(artFile, 35);

            // ================ ROUTES ========================
            if (choice == 1) runEpstein(&progress, slot);
            else if (choice == 2) runClinton(&progress, slot);
            else if (choice == 3) runJackson(&progress, slot);

            printf("\n1. Talk to someone else\n2. Main Menu\n3. Quit\nChoice: ");

            if (scanf("%d", &postChoice) != 1) {
                printf("Invalid input.\n");
                clearInputBuffer();
                continue;
            }

            clearInputBuffer();

            if (postChoice == 1) continue;
            if (postChoice == 2) break;
            if (postChoice == 3) return 0;
        }
    }

    return 0;
}
