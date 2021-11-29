#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clear() {
	gotoxy(0, 0);
	for (int i = 0; i < 30; i++) printf("                                                                                                     \n");
}