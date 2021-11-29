#include<stdio.h>
#include<stdlib.h>
#include"Mouse.h"

char** empty(int x, int y) {
	char** res = (char**)malloc(sizeof(char*) * x);
	for (int i = 0; i < y; i++) res[i] = (char*)malloc(sizeof(char) * y);
	for (int i = 0; i < x; i++) for (int j = 0; j < y; j++) res[i][j] = 'n';
	return res;
}

char** generate(int x, int y, int mine) {
	char** res = (char**)malloc(sizeof(char*)*x);
	for (int i = 0; i < y; i++) res[i] = (char*)malloc(sizeof(char)*y);
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
					} else {
						continue;
					}
				}
			}
		}
	}
	return res;
}

void print(char** data) {
	for (int i = 0; i < sizeof(data) / sizeof(data[i]); i++) {
		for (int j = 0; j < sizeof(data[i]) / sizeof(data[i][j]); j++) printf("%c", data[i][j]);
		printf("\n");
	}
}