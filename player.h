#pragma once

class Player {

private:

	int x;
	int y;
public:
	Player(int _x, int _y);
	void xPlus();
	void xMinus();
	int getX();
	int getY();

};
