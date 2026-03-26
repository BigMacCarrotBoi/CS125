#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void drawGirl()
{
    printf("\n:)\n");
}

void drawFrown()
{
    printf("\n:(\n");
}

void drawShocked()
{
    printf("\n:O\n");
}

void drawDead()
{
    printf("\nX_X\n");
}



void saveTheGame(char UserData[9], int user)
{
    char likeToSaveGame;
    char filename[20];
    FILE *file;
    int i;

    printf("Would you like to save your game? (Y)es or (N)o? >> ");
    scanf(" %c", &likeToSaveGame);

    likeToSaveGame = toupper(likeToSaveGame);

    while (likeToSaveGame != 'Y' && likeToSaveGame != 'N')
    {
        printf("Invalid option\n");
        scanf(" %c", &likeToSaveGame);
        likeToSaveGame = toupper(likeToSaveGame);
    }

    if (likeToSaveGame == 'Y')
    {
        sprintf(filename, "player%d.txt", user);

        file = fopen(filename, "w");

        for (i = 0; i < 9; i++)
        {
            fprintf(file, "%c\n", UserData[i]);
        }

        fclose(file);

        printf("Game Saved.\n");
    }
}



void explainGame()
{
    printf("\nHow To Play:\n");
    printf("You will be put in situations where you are forced to react!\n");
    printf("Choose options using letters.\n");
    printf("Your choices affect the ending.\n");
    printf("Good luck!\n");
}



void ContinueOrReset(int user, char UserData[9], char *choice)
{
    char filename[20];
    FILE *file;
    int i;

    printf("Would you like to (C)ontinue or (R)eset save slot %d ? >> ", user);

    scanf(" %c", choice);

    *choice = toupper(*choice);

    while (*choice != 'C' && *choice != 'R')
    {
        printf("Invalid\n");
        scanf(" %c", choice);
        *choice = toupper(*choice);
    }

    sprintf(filename, "player%d.txt", user);

    if (*choice == 'C')
    {
        file = fopen(filename, "r");

        if (file == NULL)
        {
            for (i = 0; i < 9; i++)
                UserData[i] = '0';
            return;
        }

        for (i = 0; i < 9; i++)
        {
            fscanf(file, " %c", &UserData[i]);
        }

        fclose(file);
    }

    if (*choice == 'R')
    {
        file = fopen(filename, "w");

        for (i = 0; i < 9; i++)
        {
            UserData[i] = '0';
            fprintf(file, "0\n");
        }

        fclose(file);
    }
}



void initialChoices(int *User, char UserData[9], char *ContinueChoice)
{
    char tutorial;

    printf("Would you like explanation? (Y/N) >> ");
    scanf(" %c", &tutorial);

    tutorial = toupper(tutorial);

    while (tutorial != 'Y' && tutorial != 'N')
    {
        printf("Invalid\n");
        scanf(" %c", &tutorial);
        tutorial = toupper(tutorial);
    }

    if (tutorial == 'Y')
        explainGame();

    printf("Choose save file (1,2,3) >> ");
    scanf("%d", User);

    while (*User < 1 || *User > 3)
    {
        printf("Invalid\n");
        scanf("%d", User);
    }

    ContinueOrReset(*User, UserData, ContinueChoice);
}



void mainMenu(int *User, char UserData[9], char *ContinueChoice)
{
    printf("Hello And Welcome To Situation Simulator!\n");

    initialChoices(User, UserData, ContinueChoice);
}
void mainGame(char data[9], int user);


void startGame(char UserData[9], char ContinueChoice, int user)
{
    if (ContinueChoice == 'R')
    {
        int i;
        for (i = 0; i < 9; i++)
            UserData[i] = '0';
    }

    mainGame(UserData, user);
}



void mainGame(char data[9], int user)
{
    char choice;
    int i;

    printf("The game has started...\n");

    drawGirl();


/* ======================
   CHOICE 1
====================== */

    if (data[0] == '0')
    {
        printf("You see a girl sitting in a field.\n");
        printf("(S) Smile\n");
        printf("(Y) Yell\n");
        printf("(W) Watch\n");
        printf("(I) Ignore\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'S' &&
            choice != 'Y' &&
            choice != 'W' &&
            choice != 'I'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[0] = choice;

        if (choice == 'S')
        {
            printf("You smile.\n");
            drawGirl();
        }
        else
        {
            printf("She is upset.\n");
            drawFrown();
        }

        saveTheGame(data, user);
    }



/* ======================
   CHOICE 2
====================== */

    if (data[1] == '0')
    {
        printf("She dances.\n");

        printf("(S) Slap\n");
        printf("(L) Laugh\n");
        printf("(R) Dance\n");
        printf("(A) Applaud\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'S' &&
            choice != 'L' &&
            choice != 'R' &&
            choice != 'A'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[1] = choice;

        if (choice == 'S')
            drawShocked();

        if (choice == 'L')
            drawFrown();

        saveTheGame(data, user);
    }



/* ======================
   CHOICE 3
====================== */

    if (data[2] == '0')
    {
        drawShocked();

        printf("Helicopter overhead.\n");

        printf("(Q) Question\n");
        printf("(M) Make fun\n");
        printf("(P) Pretend helicopter\n");
        printf("(O) Offer hug\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'Q' &&
            choice != 'M' &&
            choice != 'P' &&
            choice != 'O'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[2] = choice;

        if (choice == 'M')
            drawFrown();

        saveTheGame(data, user);
    }
/* ======================
   CHOICE 4
====================== */

    if (data[3] == '0')
    {
        printf("She asks if you like kombucha.\n");

        printf("(L) Lie\n");
        printf("(T) Truth\n");
        printf("(I) Ignore\n");
        printf("(M) Make fun\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'L' &&
            choice != 'T' &&
            choice != 'I' &&
            choice != 'M'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[3] = choice;

        if (choice == 'M')
            drawFrown();

        saveTheGame(data, user);
    }



/* ======================
   CHOICE 5
====================== */

    if (data[4] == '0')
    {
        drawShocked();

        printf("She falls off a cliff!\n");

        printf("(T) Throw rocks\n");
        printf("(R) Rescue\n");
        printf("(C) Call help\n");
        printf("(F) Fall too\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'T' &&
            choice != 'R' &&
            choice != 'C' &&
            choice != 'F'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[4] = choice;

        saveTheGame(data, user);
    }



/* ======================
   CHOICE 6 (death possible)
====================== */

    if (data[5] == '0')
    {
        drawShocked();

        printf("She is choking!\n");

        printf("(G) Heimlich\n");
        printf("(S) Do nothing\n");
        printf("(P) Punch\n");
        printf("(D) CPR\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'G' &&
            choice != 'S' &&
            choice != 'P' &&
            choice != 'D'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[5] = choice;

        if (choice == 'S')
        {
            drawDead();
            printf("ENDING 1\n");
            saveTheGame(data, user);
            return;
        }

        saveTheGame(data, user);
    }



/* ======================
   CHOICE 7
====================== */

    if (data[6] == '0')
    {
        printf("She wants to race.\n");

        printf("(W) Win\n");
        printf("(L) Lose\n");
        printf("(T) Refuse\n");
        printf("(C) Cheat\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'W' &&
            choice != 'L' &&
            choice != 'T' &&
            choice != 'C'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[6] = choice;

        saveTheGame(data, user);
    }



/* ======================
   CHOICE 8
====================== */

    if (data[7] == '0')
    {
        printf("She asks your hobby.\n");

        printf("(S) Scuba\n");
        printf("(R) Rock climb\n");
        printf("(G) Ski\n");
        printf("(W) Games\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'S' &&
            choice != 'R' &&
            choice != 'G' &&
            choice != 'W'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[7] = choice;

        saveTheGame(data, user);
    }
/* ======================
   CHOICE 9
====================== */

    if (data[8] == '0')
    {
        printf("Go home?\n");

        printf("(U) Uber\n");
        printf("(T) Run\n");
        printf("(S) Stay\n");
        printf("(F) Follow\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        while (
            choice != 'U' &&
            choice != 'T' &&
            choice != 'S' &&
            choice != 'F'
        )
        {
            printf("Invalid\n");
            scanf(" %c", &choice);
            choice = toupper(choice);
        }

        data[8] = choice;

        saveTheGame(data, user);
    }



/* ======================
   ENDINGS
====================== */

    printf("\nEnding reached.\n");

    if (data[5] == 'S')
    {
        printf("Ending 1\n");
    }
    else if (data[0] == 'Y' && data[1] == 'S')
    {
        printf("Bad ending\n");
    }
    else if (data[0] == 'S' && data[5] == 'G')
    {
        printf("Good ending\n");
    }
    else
    {
        printf("Okay ending\n");
    }
}



/* ======================
   MAIN
====================== */

int main()
{
    int User;
    char ContinueChoice;
    char UserData[9];
    int i;

    for (i = 0; i < 9; i++)
        UserData[i] = '0';

    mainMenu(&User, UserData, &ContinueChoice);

    startGame(UserData, ContinueChoice, User);

    printf("\nGame Over\n");

    return 0;
}
