#include <stdio.h>
#include <windows.h>
#include "player.h"
#include "ceilng.h"
#include "functions.h"



int main() {
	int check = 1;
	int score;
	system("mode con: cols=40 lines=30");
	loadMenu();
	while (check) {
		if (IsKeyDown(VK_UP)) { score = gameSTART(); check = 0; }
		if (IsKeyDown(VK_DOWN)) { exit(1); }
	}
	system("cls");

    loadScore(score);
	main();
	
	return 1;
}
