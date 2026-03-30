//**************
//main code ahh
//**************

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

int main() {
    srand(time(NULL));
    clearscreen();

    menuIntro(2, 300);

    Progress progress = {0};
    int slot = -1;
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
        return 0;
    }
    else {
        return 0;
    }

    clearscreen();

    int choice = 0;
    char artFile[32];
    char character[20];

    while (choice < 1 || choice > 3) {
        printf("Choose character (1-3): ");
        scanf("%d", &choice);
    }

    if (choice == 1) strcpy(character, "Epstein");
    if (choice == 2) strcpy(character, "Bill Clinton");
    if (choice == 3) strcpy(character, "Michael Jackson");

    printf("\nYou walk %s catching their attention...\n", character);

    if (choice == 1) strcpy(artFile, "artDir/epstein.txt");
    if (choice == 2) strcpy(artFile, "artDir/clinton.txt");
    if (choice == 3) strcpy(artFile, "artDir/jackson.txt");

    printChArt(artFile, 35);

    if (choice == 1) {
        epsteinD1(progress.d1, &progress, slot);
        
        epsteinD2(progress.d2, &progress, slot);
        epsteinD3(progress.d3, &progress, slot);
        epsteinD4(progress.d4, &progress, slot);
    }

    if (choice == 2) {
        clintonD1(progress.c1, &progress, slot);
    }

    if (choice == 3) {
        jacksonD1(progress.j1, &progress, slot);
    }

    printf("Game End\n");
    return 0;
}