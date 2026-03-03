#include <stdio.h>
#include "asciiart.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/* This function clears the terminal screen for the user. */
void clearscreen() {

	system("clear");

}


void loadFile() {

	printf("");

}


int main() {

	srand(time(NULL));
	clearscreen();
	int choice=0;

	/* This prints the menu and allows the user to pick a save file. */
	printf("Welcome to the dating simulator chatbot!\n");
	printf("This game will allow you to build relationships with a variety of people and learn more about them.\n");
	printf("/nMenu/n1. New Game/n2. Load Game/n3. Quit Game/n");
	printf("Choice: ");
	scanf("%d", %choice);
	switch (choice) {
		case 1:
			break;
		case 2:
			loadFile();
		case 3:
			break;
		default:
			printf("Please choose 1, 2, or 3.\n");
		}

        /* This lets the user choose who they want to talk to. */
	// sleep(3);
	// include ascii art of the characters one by one
	char character[20]="";
	while (choice < 1 || choice > 3) {
		printf("Which character do you want to talk to? (1, 2, or 3): ");
		scanf("%d", &choice); }
	if (choice==1)
		strcpy(character, "Epstein");
	if (choice==2)
		strcpy(character, "Diddy");
	if (choice==3)
		strcpy(character, "Donald Trump");
	printf("You chose to talk to %s!\n", character);
	
return 0; }
