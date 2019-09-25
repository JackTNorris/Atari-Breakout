#pragma once

#include "Graphics.h"
class Paddle {
public:
	const int height = 10;
	int width = 100;
	const int vy = 0;

	int x = (Graphics::ScreenWidth/2) - (width / 2);
	int y = Graphics::ScreenHeight - 60 - height;

	int vx = 0;

	int findVX1 = 0;
	int findVX2 = 0;
	int hitNumber = 0;	// used to make sure 1st quote isn't cut off when hitting paddle


	bool hitBall = false;
	bool shrunk = false;


	void update();
	int checkBallCollision(int& ballX, int& ballY, int ballHeight, int ballWidth, int ballSlope);
private:
	int subX;
	int subY;
};