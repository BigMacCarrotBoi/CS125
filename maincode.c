#include <stdio.h>
#include "asciiart.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* This function clears the terminal screen for the user. */
void clearscreen() {

	system("clear");

}


int main() {

	clearscreen();
	printf("Welcome to the chatbot!\n");
	printf("This game will allow you to build relationships with a variety of people and learn more about them.\n");
	// sleep(3);
	// include ascii art of the characters one by one
	
	int choice=0; char character[20]="";
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
