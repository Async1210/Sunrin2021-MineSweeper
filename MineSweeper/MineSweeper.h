#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Mouse.h"

typedef struct MineSweeper {
	int x;
	int y;
	int mine;
	int status; //0 : game over, 1 : running, 2 : win
	char** player;
	char** map;
} MineSweeper;

//int select(int x, int y, MineSweeper* data);

char** empty(int x, int y) {
	char** res = (char**)malloc(sizeof(char*) * x);
	for (int i = 0; i < y; i++) res[i] = (char*)malloc(sizeof(char) * y);
	for (int i = 0; i < x; i++) for (int j = 0; j < y; j++) res[i][j] = 'n';
	return res;
}

char** generate(int x, int y, int mine) {
	char** res = (char**)malloc(sizeof(char*)*x);
	for (int i = 0; i < y; i++) res[i] = (char*)malloc(sizeof(char)*y);
	for (int i = 0; i < x; i++) for (int j = 0; j < y; j++) res[i][j] = '0';
	for (int i = 0; i < mine; i++) {
		int rx = rand() % x;
		int ry = rand() % y;
		if (res[rx][ry] == 'm') i--;
		else {
			res[rx][ry] = 'm';
			for (int tx = -1; tx < 2; tx++) {
				for (int ty = -1; ty < 2; ty++) {
					if (rx + tx >= 0 && rx + tx < x && ry + ty >= 0 && ry + ty < y && res[rx + tx][ry + ty] != 'm') {
						res[rx + tx][ry + ty]++;
					}
				}
			}
		}
	}
	return res;
}

void print(int x,int y,char** data) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) printf("%c", data[i][j]);
		printf("\n");
	}
}

void gameover(MineSweeper* data) {
	gotoxy(data->x + 1, 0);
	printf("Game Over!");
	data->status = 0;
}

void select_mine(int x, int y, MineSweeper* data) {
	printf("%c", data->map[x][y]);
	data->player[x][y] = data->map[x][y];
	if (data->map[x][y] == 'm') {
		gameover(data);
	} else {
		int isMine = 0;
		gotoxy(0, 0);
		for (int tx = -1; tx < 2; tx+=2) for (int ty = -1; ty < 2; ty+=2) {
			printf("tx : %d, ty : %d\n", tx, ty);
		}
		if (isMine==0) for (int tx = -1; tx < 2; tx+=2) for (int ty = -1; ty < 2; ty+=2) {
			printf("isMine : 0, tx : %d, ty : %d\n", tx, ty); 
		}
	}
}