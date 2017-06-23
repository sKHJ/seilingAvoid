#include "ceilng.h"

Ceiling :: Ceiling(int y_, int wait_, int hole1_, int hole2_, int hole3_) {
	y = y_; wait = wait_; hole1 = hole1_; hole2 = hole2; hole3 = hole3_;
}

int Ceiling:: getY() { return y; }
int Ceiling:: getWait() { return wait; }
int Ceiling:: getHole1() { return hole1; }
int Ceiling:: getHole2() { return hole2; }
int Ceiling:: getHole3() { return hole3; }

void Ceiling::DownCeiling() { y++; }
void Ceiling::waitMinus() { wait--; }
void  Ceiling::resetCeiling(int _wait) {
	wait = _wait;
	y = 3;
	hole1 = rand() % 19 + 1;
	hole2 = rand() % 19 + 1;
	hole3 = rand() % 19 + 1;
}