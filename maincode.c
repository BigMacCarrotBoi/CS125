#include <stdio.h>
#include "otherFunctions.c"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {

	srand(time(NULL));
	clearscreen();
	int choice=0;
	printf("Welcome to the chatbot!\nThis game allows you to talk to a variety of people and build relationships with them.\n");

	/* This prints the menu and allows the user to pick a save file. */
	menu();
	
	clearscreen();
	
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
		strcpy(character, "Bill Clinton");
	if (choice==3)
		strcpy(character, "Micheal Jackson");
	printf("You walk up to talk to %s!\n", character);
	printf("You catch %s's attention as they turn to you.\n", character);
	// prints character art based on choice
	if (choice==1) strcpy(artFile, "epstein.txt");
	if (choice==2) strcpy(artFile, "clinton.txt");
	if (choice==3) strcpy(artFile, "jackson.txt");
	printChArt(artFile, 35);
	
return 0; }
