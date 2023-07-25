
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>	
#include <stdlib.h>														//Used libraries
#include <time.h>
#include <Windows.h>
#include<locale.h>

char map[5][15];

int printMap(char map[5][15]) {										//Function for printing map
	system("cls");		
	for (int i = 0; i < 5; i++) {									
		for (int j = 0; j < 15; j++) {
			printf("  %c  ", map[i][j]);
		}
		printf("|");
		printf("\n\n");										    	
	}

}

void showControls() {
	printf("\n\t\t ^ \n\t\t(W)\n\n\t<-(A)\t      (D)->\n\n\t\t(S)\n\t\t V\n\n");
}

void makeMap(char map[5][15]) {
																	//Function for making random matrix map
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 15; j++) {
			map[i][j] = ' ';
			int randomNumber = rand() % 2;							//Choses randomly 0 or 1 
			if (randomNumber == 1)							   	    //If random number equals to 1, places x to that coordinate 
				map[i][j] = 'x';
		}
	}


}															

void main() {		

	


	printf("\n\n\t\tWelcome !!\n\n\n\t\tThe purpose of the game is reaching to the end by going through less x and move number\n");
	printf("\n\n\t\tW A S D for movement\n");
	printf("\n\n\t\tPress any key\n\n");

	time_t t;
	srand(time(NULL));

	system("pause");

	int selected = 1;
	

	while (selected != 51) {

		makeMap(map);

		int oldValue, newValue = 2, character = 49;

		selected = 1;                                                    //Selected reset

		oldValue = map[0][2];											//Sets the oldValue's value where character will begin
		map[2][0] = character;											//Put character in to the left center of the map

		char wasdCoordinateChange;

		int rowMove = 2, columnMove = 0, score = 100, moveNumber = 0;

		while (columnMove <= 14 && columnMove >= 0) {				//Continues as long as the character does not finish the map

			

			printMap(map);
			showControls();



			printf("\nNumber Of Move: %d\t\t\t", moveNumber);
			printf("score: %d\n", score);

			wasdCoordinateChange = _getch(); 
			 
			if (wasdCoordinateChange == 100 || wasdCoordinateChange == 68) {				     //d & D
				map[rowMove][columnMove] = oldValue;            //Puts the old value to the characters place
				columnMove += 1;							    //Increase the character's column by 1								
				oldValue = map[rowMove][columnMove];			//Holds the value of where character will go
				map[rowMove][columnMove] = character;			//Puts the character to its new value
			}



			else if (wasdCoordinateChange == 97 || wasdCoordinateChange == 65) {				//a & A
				map[rowMove][columnMove] = oldValue;										
				columnMove -= 1;					            //Decrease the character's column by 1
				if (columnMove < 0)
					columnMove = 0;
				oldValue = map[rowMove][columnMove];
				map[rowMove][columnMove] = character;
			}



			else if (wasdCoordinateChange == 115 || wasdCoordinateChange == 83) {				//s & S
				map[rowMove][columnMove] = oldValue;
				rowMove += 1;					            	//Decrease the line with the character by 1
				oldValue = map[rowMove][columnMove];
				map[rowMove][columnMove] = character;
			}

			else if (wasdCoordinateChange == 119 || wasdCoordinateChange == 87) {				//w &  W
				map[rowMove][columnMove] = oldValue;
				rowMove -= 1;					            	//Increase the line with the character by 1
				oldValue = map[rowMove][columnMove];
				map[rowMove][columnMove] = character;
			}


			else {
				printf("Please enter a valid value\n");
				Sleep(200);
				continue;
			}


			if (rowMove < 0) {						           //If it goes on top of the map, it throws it under
				rowMove = 4;
				oldValue = map[rowMove][columnMove];
				map[rowMove][columnMove] = character;
			}

			else if (rowMove > 4) {                           //If it comes out from under the map, it throws it on top of it.
				rowMove = 0;
				oldValue = map[rowMove][columnMove];
				map[rowMove][columnMove] = character;
			}

			if (oldValue == 'x')
				score -= 5;

			moveNumber += 1;
			score -= 1;

		}

		system("cls");
		printf("\n\n\n\t\t\tSuccessfully completed !\t\t\t \n\n");
		printf("\t\t\tNumber of moves: %d \t\t\t\n\n", moveNumber);
		printf("\t\t\tScore: %d \t\t\t\n\n\n", score);
		printf("\t\t\tFor different map (1)\n\t\t\tWith same map (2)\n\t\t\tTo quit (3)\n");


		while (selected == 1) {							     	 // 49 for 1, 50 for 2, 51 for 3 (ASCII)
			selected = _getch();
			if (selected == 49) {							     //Different map
				srand(time(NULL));							     //Sets random
				break;
			}			                                        
			else if (selected == 50) {							 //Same map
				srand(1);
				break;
			}
			else if (selected == 51) {							//Quit
				break;
			}
			else
				selected = 1;
		}
	}
}


