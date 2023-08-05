#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>	
#include <stdlib.h>														//Used libraries
#include <time.h>
#include <Windows.h>
#include <locale.h>

#define MAP_ROWS 5
#define MAP_COLS 15

char map[MAP_ROWS][MAP_COLS];

enum MapElement {
	EMPTY = ' ',
	MINE = 'x',
	CHARACTER = 4
};


int printMap(char map[MAP_ROWS][MAP_COLS]) {										//Function for printing map
	system("cls");
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			printf("  %c  ", map[i][j]);
		}
		printf("|");
		printf("\n\n");
	}

}

void printstart() {
	printf("\n\n\t\tWelcome !!\n\n\n\t\tThe purpose of the game is reaching to the end by going through less x and move number\n");
	printf("\n\n\t\tW A S D for movement\n\n\n");
	system("pause");
}

void printIngame(int moveNumber, int score) {
	printf("\n\t\t ^ \n\t\t(W)\n\n\t<-(A)\t      (D)->\n\n\t\t(S)\n\t\t V\n\n");
	printf("\nNumber Of Move: %d\t\t\t", moveNumber);
	printf("score: %d\n", score);
}

void printend(int mapCounter, int moveNumber, int score, int lastscore) {

	system("cls");

	printf("\n\n\n\t\t\tSuccessfully completed !\t\t\t Map:%d \n\n", mapCounter);
	printf("\t\t\tNumber of moves: %d \t\t\t\n", moveNumber);



	printf("\t\t\t\t\t\t\t\t\tPlayer 1: %d\n", score);
	printf("\t\t\t\t\t\t\t\t\tPlayer 2: %d\n", lastscore);

	printf("\n\t\t\tScore: %d \t\t\t\n\n\n", score);
	printf("\t\t\tFor different map (1)\n\t\t\tWith same map (2)\n\t\t\tTo quit (3)\n");


}

void makeMap(char map[MAP_ROWS][MAP_COLS]) {
																	//Function for making random matrix map
	for (int i = 0; i < MAP_ROWS; i++) {
		for (int j = 0; j < MAP_COLS; j++) {
			map[i][j] = EMPTY;
			int randomNumber = rand() % 2;							//Choses randomly 0 or 1 
			if (randomNumber == 1)							   	    //If random number equals to 1, places x to that coordinate 
				map[i][j] = MINE;
		}
	}


}

void printmenu(int *selected, int *mapCounter){

	while (*selected == 1) {							     	 // 49 for 1, 50 for 2, 51 for 3 (ASCII)
		*selected = _getch();
		if (*selected == 49) {							     //Different map
			srand(time(NULL));							     //Sets random
			*mapCounter++;
			break;
		}
		else if (*selected == 50) {							 //Same map
			srand(1);
			break;
		}
		else if (*selected == 51) {							//Quit
			break;
		}
		else
			*selected = 1;
	}


}

int moveCharacter(char map[MAP_ROWS][MAP_COLS], int* currentRow, int* currentColumn, int* score, int* moveNumber, int *oldValue) {

	char wasdCoordinateChange = _getch();

	map[*currentRow][*currentColumn] = *oldValue;

	switch (wasdCoordinateChange) {
	case 'd':
	case 'D':
		(*currentColumn)++;
		break;
	case 'a':
	case 'A':
		(*currentColumn)--;
		break;
	case 's':
	case 'S':
		(*currentRow)++;
		break;
	case 'w':
	case 'W':
		(*currentRow)--;
		break;
	default:
		printf("Please enter a valid value\n");
		Sleep(200);
		return 0;
	}

	*oldValue = map[*currentRow][*currentColumn];
	map[*currentRow][*currentColumn] = CHARACTER;

	//Handle Map Borders 

	if (*currentRow < 0 || *currentRow > 4) {						//If it goes on top of the map, it throws it under. If it comes out from under the map, it throws it on top of it.
		*currentRow = (*currentRow < 0) ? 4 : 0;					//If row number is less than 0 that means CHARACTER went over the map sets new value to the bottom.
		*oldValue = map[*currentRow][*currentColumn];				//If isnt less than zero, its more than 4 this means CHARACTER went under the map sets new value to the top.
		map[*currentRow][*currentColumn] = CHARACTER;
	}

	if (*oldValue == 'x')									//If CHARACTER pressed to mine, lower the score by 5.
		*score -= 5;

	*moveNumber += 1;
	*score -= 1;

}

void main() {

	printstart();
						
	srand(time(NULL));										//For random number.

	int selected = 1, mapCounter = 1;

	while (selected != 51) {


		int currentRow = 2, currentColumn = 0, score = 100, lastScore = 0, moveNumber = 0, oldValue = 0, CHARACTER = 4;

		char wasdCoordinateChange;


		makeMap(map);

		selected = 1;                                                   //Selected reset.

		oldValue = map[0][2];											//Sets the oldValue's value where CHARACTER will begin.
		map[2][0] = CHARACTER;											//Put CHARACTER in to the left center of the map.



		while (currentColumn < MAP_COLS && currentColumn >= 0) {				//Continues as long as the CHARACTER does not finish the map


			printMap(map);

			printIngame(moveNumber, score);

			moveCharacter(map, &currentRow, &currentColumn, &score, &moveNumber, &oldValue);		


		}

		printend(mapCounter, moveNumber, score, lastScore);

		printmenu(&selected, &mapCounter);





	}
}
