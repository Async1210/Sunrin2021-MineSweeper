#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clear(int x,int height) {
	gotoxy(x, 0);
	for (int i = 0; i < height; i++) printf("                                                                                                     \n");
	gotoxy(x, 0);
}