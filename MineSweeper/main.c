#include<stdio.h>
#include"MineSweeper.h"

// https://im-developer.tistory.com/116

void main() {
	//char** res = generate(9, 9, 10);
	//for (int i = 0; i < 9; i++) {
	//	for (int j = 0; j < 9; j++) printf("%c", res[i][j]);
	//	printf("\n");
	//}
	MineSweeper data;
	data.x = 9;
	data.y = 9;
	data.mine = 10;
	data.map = generate(data.x, data.y, data.mine);
	data.player = empty(data.x, data.y);
	data.status = 1;

	gotoxy(0, data.y+3);
	print(data.x, data.y, data.player);

	select_mine(0, 0, &data);
	//gotoxy(0, 0);
	//print(data.x, data.y, data.player);
}