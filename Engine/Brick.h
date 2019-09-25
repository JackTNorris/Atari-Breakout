#pragma once
#include <string>


class Brick {
public:
	const int height = 10;
	const int width = 30;
	const int topOfBricks = 200;
	const int spacing = 2;

	int x;
	int y;
	int color[4] = {0,0,0,0};
	bool isBroken = false;
	void setColor(std::string brick);



	int counter = 1;
private:
	
};