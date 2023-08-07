#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>	
#include <stdlib.h>														//Used libraries
#include <time.h>
#include <Windows.h>
#include<locale.h>


int waitwtf(int *number) {
	(*number)++;
}


void main() {

	int number = 1;

	printf("%d \n",number);
	waitwtf(&number);
	printf("%d \n", number);
	printf("%d \n", number);
	

}