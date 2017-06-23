
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "ceilng.h"
#include "player.h"

// 화면의 특정 위치로 이동해 주는 함수.
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}

void loadMenu() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	gotoxy(0, 1);
	//printf("[--------------------------------------]");
	printf("[------------ Ceiling Avoid -----------]");
	gotoxy(6, 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);

	printf(" AVOID FROM FALLING CEILINGS!");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	gotoxy(6, 10);
	printf(" HOW LONG CAN YOU SURVIVE??? ");

	gotoxy(6, 19);
	printf("     PRESS ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	printf("↑  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	printf("TO START");

	gotoxy(6, 21);
	printf("     PRESS ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	printf("↓  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	printf("TO EXIT");

	gotoxy(0, 29);
	printf("[--------------------------------------]");

}

void loadScore(int score) {



	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	gotoxy(0, 1);
	//printf("[--------------------------------------]");
	printf("[------------ Ceiling Avoid -----------]");

	gotoxy(6, 10);
	printf(" YOUR SCORE IS.... ");
	gotoxy(6, 13);
	printf("[   %d   ]", score);

	gotoxy(6, 16);

	// 기록 저장
	printf("ENTER YOUR NAME     ");

	char name[20];
	char* temp;
	scanf_s("%s", name, 20);

	FILE* fp = fopen("record.txt", "at");
	if (!fp == NULL) {
		fprintf(fp, "NAME : %s          SCORE : %d \n", name, score);
	}
	fclose(fp);

	gotoxy(6, 19);
	printf("     PRESS ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	printf("↑  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	printf("TO TRY AGAIN ");



	gotoxy(0, 29);
	printf("[--------------------------------------]");
	int check = 1;
	while (check) {
		if (IsKeyDown(VK_UP)) {
			check = 0;
		}

	}
}

void printCeil(Ceiling* ceil) {
	if (ceil->getWait() > 0) { ceil->waitMinus(); }
	else {
		ceil->DownCeiling();
		gotoxy(0, ceil->getY());
		for (int i = 0; i <= 19; i++) {
			if (ceil->getHole1() == i || ceil->getHole2() == i || ceil->getHole3() == i) {
				printf("　");
			}
			else printf("■");
		}
	}


}

void printPlayer(Player player) {
	gotoxy(0, player.getY());

	for (int i = 0; i <= 19; i++) {
		if (player.getX() == i) {
			printf("◎");
		}
		else printf("　");

	}
}

bool ceilHitCheck(Ceiling ceil, Player player) {
	// hit시 false return


	// 충돌조건 1. 벽이 user y로 내려왔고,
	//          2. user가 hole에 있지 않아야함
	if (ceil.getY() == player.getY()) {
		if (player.getX() == ceil.getHole1() || player.getX() == ceil.getHole2() || player.getX() == ceil.getHole3()) {

		}
		else {
			// 충돌 -> 비프음 출력, 게임종료
			printf("\a");
			return false;
		}
	}

	return true;

}

void playerMove(Player* player) {
	if (IsKeyDown(VK_LEFT))
	{
		if (player->getX() >= 1)
		{
			player->xMinus();
		}
	}
	if (IsKeyDown(VK_RIGHT))
	{
		if (player->getX() <= 18)
		{
			player->xPlus();
		}
	}
}

bool resetCeiling(Ceiling *ceil, char* level) {
	if (ceil->getY() >= 28)
	{
		// + 구멍 초기화
		if (level == "ENDLESS") ceil->resetCeiling(6);
		else
			ceil->resetCeiling(15);
		return true;
	}
}

int gameSTART() {
	int score = 0;;
	char* level = "EASY";
	bool onGame = true;
	system("cls");

	Player player(10, 27);

	// 시작위치가 3이며 10clock 만큼 뒤에 생성되는 ceiling, hole은 3개이며 랜덤으로 정해진다.
	Ceiling ceil(3, 15, rand() % 19 + 1, rand() % 19 + 1, rand() % 19 + 1);

	Ceiling ceil2(3, 0, rand() % 19 + 1, rand() % 19 + 1, rand() % 19 + 1);
	Ceiling ceil3(3, 30, rand() % 19 + 1, rand() % 19 + 1, rand() % 19 + 1);



	while (onGame) {


		// 게임속도 조절
		int speed = 120;
		Sleep(speed);

		// 인터페이스
		system("cls");
		gotoxy(0, 0);
		printf("[--------------------------------------]\n");
		printf("SCORE : [  %d  ]  LEVEL : [  %s  ]", score, level);


		// 플레이어 조작 관리
		playerMove(&player);

		// 사람 출력
		printPlayer(player);

		// 천장 출력
		printCeil(&ceil);
		printCeil(&ceil2);
		printCeil(&ceil3);
		
		// LEVEL 관리
		if (score == 0) {
			printf("WELCOME TO LEVEL EASY");
		}
		if (score == 50) {
			speed = 100;
			printf("LEVEL UP!");
			level = "NORMAL";
		}
		if (score == 100) {
			speed = 40;
			printf("HARDEST LEVEL!");
			level = "ENDLESS";
		}


		// 충돌 체크 hit시 false
		// 1개라도 FALSE이면 FALSE 값이다 
		onGame = !(!ceilHitCheck(ceil, player) || !ceilHitCheck(ceil2, player) || !ceilHitCheck(ceil3, player));

		// 천장이 완전히 내려왔을때

		if (resetCeiling(&ceil, level) == true) 	score = score + 10;
		if (resetCeiling(&ceil2, level) == true) 	score = score + 10;
		if (resetCeiling(&ceil3, level) == true) 	score = score + 10;



	}

	return score;
}