#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawGirl() {
    printf("\n(^_^)\n");
}

void drawFrown() {
    printf("\n(-_-)\n");
}

void drawShocked() {
    printf("\n(O_O)\n");
}

void drawDead() {
    printf("\n(X_X)\n");
}

void explainGame() {
    printf("\nHow To Play:\n");
    printf("You will be put in situations where you are forced to react!\n");
    printf("Choose options by typing letters.\n");
    printf("Your choices affect the ending.\n");
}

void saveGame(char data[9], int user) {

    char filename[20];
    sprintf(filename, "player%d.txt", user);

    FILE *f = fopen(filename, "w");

    if (!f) {
        printf("Error saving file\n");
        return;
    }
	
    int i;
    for (i = 0; i < 9; i++) {
        fprintf(f, "%c\n", data[i]);
    }

    fclose(f);

    printf("Game saved.\n");
}

void loadGame(char data[9], int user) {

    char filename[20]; int i;
    sprintf(filename, "player%d.txt", user);

    FILE *f = fopen(filename, "r");

    if (!f) {
        for (i = 0; i < 9; i++)
            data[i] = '0';
        return;
    }

    for (i = 0; i < 9; i++) {
        if (fscanf(f, " %c", &data[i]) != 1)
            data[i] = '0';
    }

    fclose(f);
}

void mainGame(char data[9], int user) {

    char choice;

    printf("\nGame started...\n");

    if (data[0] == '0') {

        drawGirl();

        printf("You see a girl in a field.\n");
        printf("(S)mile (Y)ell (W)atch (I)gnore\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[0] = choice;

        if (choice == 'S')
            drawGirl();
        else
            drawFrown();

        saveGame(data, user);
    }

    if (data[1] == '0') {

        drawGirl();

        printf("\nShe dances.\n");
        printf("(S)lap (L)augh (R)equest dance (A)pplaud\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[1] = choice;

        if (choice == 'S')
            drawShocked();

        saveGame(data, user);
    }

    if (data[2] == '0') {

        drawShocked();

        printf("\nHelicopter sound.\n");
        printf("(Q)uestion (M)ake fun (P)retend heli (O)ffer hug\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[2] = choice;

        if (choice == 'M')
            drawFrown();

        saveGame(data, user);
    }

    if (data[3] == '0') {

        printf("\nShe asks about kombucha.\n");
        printf("(L)ie (T)ruth (I)gnore (M)ake fun\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[3] = choice;

        if (choice == 'M')
            drawFrown();

        saveGame(data, user);
    }

    if (data[4] == '0') {

        drawShocked();

        printf("\nShe falls off cliff!\n");
        printf("(T)hrow rocks (R)escue (C)all (F)all too\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[4] = choice;

        saveGame(data, user);
    }

    if (data[5] == '0') {

        drawShocked();

        printf("\nShe is choking!\n");
        printf("(G) Heimlich (S) nothing (P) punch (D) CPR\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[5] = choice;

        if (choice == 'S') {
            drawDead();
            printf("Ending 1\n");
            return;
        }

        saveGame(data, user);
    }

    if (data[6] == '0') {

        printf("\nRace?\n");
        printf("(W)in (L)ose (T)No (C)heat\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[6] = choice;

        saveGame(data, user);
    }

    if (data[7] == '0') {

        printf("\nHobby?\n");
        printf("(S)cuba (R)ock (G)ski (W)games\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[7] = choice;

        saveGame(data, user);
    }

    if (data[8] == '0') {

        printf("\nGo home?\n");
        printf("(U)ber (T)run (S)stay (F)follow\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        data[8] = choice;

        saveGame(data, user);
    }

    printf("\nEnding reached.\n");

    if (data[5] == 'S') {
        printf("Ending 1\n");
    }
    else if (data[0]=='Y' && data[1]=='S')
        printf("Bad ending\n");
    else if (data[0]=='S' && data[5]=='G')
        printf("Good ending\n");
    else
        printf("Okay ending\n");
}

int main() {

    int user;
    char data[9];

    printf("Situation Simulator (C version)\n");

    printf("User slot (1-3): ");
    scanf("%d", &user);

    loadGame(data, user);

    mainGame(data, user);

    return 0;
}

