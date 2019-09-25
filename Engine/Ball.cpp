#include "Ball.h"
#include "Graphics.h"
#include <windows.h>
#include <mmsystem.h>
void Ball::update() {



//////////////////////////  checking boundaries /////////////////
	if (x <= 32) {
		x = 33;
		vx *= -1;
	}
	if (x + width >= Graphics::ScreenWidth - 34) {
		x = Graphics::ScreenWidth - 35 - width;
		vx *= -1;
	}
	if (y >= Graphics::ScreenHeight - height - 5) {
		y = Graphics::ScreenHeight - height - 1;
		hitBottom = true;
	}

	if (y <= 100) {
		y = 101;
		vy *= -1;
	}
///////////////////////////////////////////////////////////////











/////////////////////////  checking ball's direction of travel ////////////////////////////////////
	if (vx < 0) {
		travelingLeft = true;
		travelingRight = false;
	}
	if (vx > 0) {
		travelingRight = true;
		travelingLeft = false;
	}
///////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////       changing ball velocity if hitting certain parts of paddle   ////////////////////////////
	if (hitLeftSidePaddle) {
		if (travelingRight) {
			vx *= -1;
			vy *= -1;
		}
		if (travelingLeft) {
			vy *= -1;
		}
		hitLeftSidePaddle = false;
	}

	if (hitRightSidePaddle) {
		if (travelingRight) {
			vy *= -1;
		}
		if (travelingLeft) {
			vy *= -1;
			vx *= -1;
		}
		hitRightSidePaddle = false;
	}
	if (hitCenterPaddle) {
		vy *= -1;
		hitCenterPaddle = false;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//////////////////////// changing brick velocity if hitting brick //////////////////////////////
	if (hitBrickSurface && hitBrickSide == false) {
		vy *= -1;
		hitBrickSurface = false;

	}
	if (hitBrickSide && hitBrickSurface == false) {
		vx *= -1;
		hitBrickSide = false;
	}
////////////////////////////////////////////////////////////////////////////////////////////






	if (y < 200 /*determine this value based on top of bricks*/) {
		inShrinkSection = true;
	}
	
}