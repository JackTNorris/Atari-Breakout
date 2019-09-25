#pragma once
#include "Graphics.h"
class Trump {
public:
	int x = 400;
	
	const int width = 100;
	const int height = 60;
	int y = Graphics::ScreenHeight - 1 - height;
	void update();


	bool travelLeft = false;
	bool travelRight = true;
private:

};