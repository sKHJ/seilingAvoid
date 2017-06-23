#include "player.h"


Player ::Player(int x_, int y_) {
	x = x_; y = y_;
}

void Player :: xPlus() { x++; }
void Player :: xMinus() { x--; }
int Player :: getX() { return x; }
int Player :: getY() { return y; }