#include<stdio.h>
#include"MineSweeper.h"

void main() {
	//char** res = generate(9, 9, 10);
	//for (int i = 0; i < 9; i++) {
	//	for (int j = 0; j < 9; j++) printf("%c", res[i][j]);
	//	printf("\n");
	//}
	print(9, 9, generate(9, 9, 10));
}