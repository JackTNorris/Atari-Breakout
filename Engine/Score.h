#pragma once
#pragma once
class Score {
public:
	int thousands;
	int hundreds;
	int tens;
	int ones;
	int total = 0;
	int digits = 4;
	int width = 27;
	int height = 52;
	int y = 25;
	int x = 25;

	int color[4] = { 0, 255, 255, 255 };
	void update();
private:
};