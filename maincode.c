#include <stdio.h>
#include "asciiart.h"
#include <string.h>
#include <stdlib.h>

/* This function clears the terminal screen for the user. */
void clearscreen() {

	system("clear");

}


int main() {

	clearscreen();
	printf("Welcome to the chatbot!\n");
	printf("This game will allow you to build relationships with a variety of people and learn more about them.\n");

return 0; }
