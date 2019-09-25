#include "Paddle.h"
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <cstdlib>
void Paddle::update() {

	if (x <= 32) {
		x = 32;
	}
	if (x + width >= Graphics::ScreenWidth - 34) {
		x = Graphics::ScreenWidth - 34 - width;
	}



	if (shrunk == true) {
		width = 28;
	}

	else {
		width = 100;
	}
	
}



int Paddle::checkBallCollision(int& ballX, int& ballY, int ballHeight, int ballWidth, int ballSlope)
{
	srand(time(NULL));
	int quotePicker = 1 + rand() % 2;
	subX = ballX;
	subY = ballY;
	if (ballY + ballHeight > y && ballY < y + height && ballX + ballWidth > x && ballX < x + width) {			
		ballY = y - ballHeight - 1;																							// tell game that ball hit paddle
		ballX = ((subY - ballY) / ballSlope) + subX - 6;			//adjusting ball x so it doesn't seem to jump


		hitNumber++; //counts times ball is hit in live


		if (hitNumber != 1) {					// making sure that quote isn't already playing



			switch (quotePicker) {					// randomly pick quote
			case 1:
				PlaySound(TEXT("bad_hombres.wav"), NULL, SND_ASYNC);
				break;
			case 2:
				PlaySound(TEXT("they_rapists.wav"), NULL, SND_ASYNC);
				
				break;
			}


		}
		

		return 1;
	}
	/*else if (ballY + ballHeight >= y && ballX >= x + (width/4) && ballX + ballWidth < x + (width *(3/4))) {
		ballY = y -  - 1;																							
		ballX = ((subY - ballY) / ballSlope) + ballX;
		return 1;
	}
	else if (ballY + ballHeight >= y && ballX >= x + (width * (3/ 4)) && ballX + ballWidth < x + width + ballWidth) {
		ballY = y - ballHeight - 1;
		ballX = ((subY - ballY) / ballSlope) + ballX;																	
		return 1;
	}
	else if (ballX + ballWidth >= x && ballX <= x + width && ballY + ballHeight >= y)  {
		ballY = y - ballHeight - 1;
		ballX = ((subY - ballY) / ballSlope) + ballX;
		return 1;
	}*/
	else {
		return 4;
	}
}


