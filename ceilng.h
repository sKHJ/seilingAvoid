#pragma once
#include <windows.h>

class Ceiling {

private:
	int y;
	int wait;
	int hole1;
	int hole2;
	int hole3;
public:

	Ceiling(int y_, int wait_, int hole1_, int hole2_, int hole3_);
		
	int getY();
	int getWait();
	int getHole1();
	int getHole2();
	int getHole3();

	void DownCeiling();
	void waitMinus();
	void resetCeiling(int _wait);

};