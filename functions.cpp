
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "ceilng.h"
#include "player.h"

// ȭ���� Ư�� ��ġ�� �̵��� �ִ� �Լ�.
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
	printf("��  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	printf("TO START");

	gotoxy(6, 21);
	printf("     PRESS ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	printf("��  ");
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

	// ��� ����
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
	printf("��  ");
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
				printf("��");
			}
			else printf("��");
		}
	}


}

void printPlayer(Player player) {
	gotoxy(0, player.getY());

	for (int i = 0; i <= 19; i++) {
		if (player.getX() == i) {
			printf("��");
		}
		else printf("��");

	}
}

bool ceilHitCheck(Ceiling ceil, Player player) {
	// hit�� false return


	// �浹���� 1. ���� user y�� �����԰�,
	//          2. user�� hole�� ���� �ʾƾ���
	if (ceil.getY() == player.getY()) {
		if (player.getX() == ceil.getHole1() || player.getX() == ceil.getHole2() || player.getX() == ceil.getHole3()) {

		}
		else {
			// �浹 -> ������ ���, ��������
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
		// + ���� �ʱ�ȭ
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

	// ������ġ�� 3�̸� 10clock ��ŭ �ڿ� �����Ǵ� ceiling, hole�� 3���̸� �������� ��������.
	Ceiling ceil(3, 15, rand() % 19 + 1, rand() % 19 + 1, rand() % 19 + 1);

	Ceiling ceil2(3, 0, rand() % 19 + 1, rand() % 19 + 1, rand() % 19 + 1);
	Ceiling ceil3(3, 30, rand() % 19 + 1, rand() % 19 + 1, rand() % 19 + 1);



	while (onGame) {


		// ���Ӽӵ� ����
		int speed = 120;
		Sleep(speed);

		// �������̽�
		system("cls");
		gotoxy(0, 0);
		printf("[--------------------------------------]\n");
		printf("SCORE : [  %d  ]  LEVEL : [  %s  ]", score, level);


		// �÷��̾� ���� ����
		playerMove(&player);

		// ��� ���
		printPlayer(player);

		// õ�� ���
		printCeil(&ceil);
		printCeil(&ceil2);
		printCeil(&ceil3);
		
		// LEVEL ����
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


		// �浹 üũ hit�� false
		// 1���� FALSE�̸� FALSE ���̴� 
		onGame = !(!ceilHitCheck(ceil, player) || !ceilHitCheck(ceil2, player) || !ceilHitCheck(ceil3, player));

		// õ���� ������ ����������

		if (resetCeiling(&ceil, level) == true) 	score = score + 10;
		if (resetCeiling(&ceil2, level) == true) 	score = score + 10;
		if (resetCeiling(&ceil3, level) == true) 	score = score + 10;



	}

	return score;
}