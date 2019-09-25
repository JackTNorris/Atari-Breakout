#include "Brick.h"
#include "Ball.h"



void Brick::setColor(std::string brick) {
	if (brick == "green") {
		color[1] = 10;
		color[2] = 127;
		color[3] = 43;
	}
	if (brick == "blue") {
		color[1] = 46;
		color[2] = 39;
		color[3] = 165;

	}
	if (brick == "red") {
		color[1] = 226;
		color[2] = 49;
		color[3] = 58;


	}
	if (brick == "purple") {
		color[1] = 171;
		color[2] = 16;
		color[3] = 206;


	}
}
