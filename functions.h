#pragma once

#include "ceilng.h"
#include "player.h"

int gameSTART();
bool resetCeiling(Ceiling *ceil, char* level);
void playerMove(Player* player);
bool ceilHitCheck(Ceiling ceil, Player player);
void printPlayer(Player player);
void printCeil(Ceiling* ceil);
void loadScore(int score);
void loadMenu();
BOOL IsKeyDown(int Key);
void gotoxy(int x, int y);