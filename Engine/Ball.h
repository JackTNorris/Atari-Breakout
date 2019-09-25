#pragma once
class Ball {
public:
	const int width = 8;
	const int height = 8;
	int ballBrickBoost = 1;
	int vx = 3;
	int vy = 4;
	int number = 0;
	
	int slope = vy / vx;
	int startX = 100;
	int startY = 330;
	int x = startX;
	int y = startY;
	int color[4] = { 0,0,0,0 };

	bool hitBlueBrick = false;
	bool travelingRight = true;
	bool travelingLeft = false;
	bool hitRightSidePaddle = false;
	bool hitLeftSidePaddle = false;
	bool hitCenterPaddle = false;
	bool hitBrickSurface = false; //top and bottom of brick
	bool hitBrickSide = false; //left and right of brick
	bool hitBottom = false;
	bool inShrinkSection = false;

	void update();
 
private:
};