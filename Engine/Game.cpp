/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <windows.h>
#include <mmsystem.h>
#include <cstdlib>
#include <time.h>
#include "SpriteCodex.h"
Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
	
	//bing(L"bing.wav"),
	//bong(L"bong.wav")
	
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	
	srand(time(NULL));
	runCounter++;
	if (runCounter % 2 == 1) {
		userPaddle.findVX1 = userPaddle.x;
		if (runCounter != 1) {
			userPaddle.vx = userPaddle.findVX1 - userPaddle.findVX2;
		}
	}
	if (runCounter % 2 == 0) {
		userPaddle.findVX2 = userPaddle.x;
		userPaddle.vx = userPaddle.findVX2 - userPaddle.findVX1;
	}
	


////////////////////////////////       user input     ////////////////////



	userPaddle.x = wnd.mouse.GetPosX() - (userPaddle.width/2);
	atariTrump.x = wnd.mouse.GetPosX() - (atariTrump.width / 2);

	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		atariScore.total = 0;
		atariBall.number = 0;
		atariScore.color[1] = 255;
		atariScore.color[2] = 255;
		atariScore.color[3] = 255;
		gameOn == false;
		resetBricks();
	}

	if (wnd.mouse.LeftIsPressed() && gameOn == false && atariBall.number < 5) {
		gameOn = true;
		atariBall.number++;
		
		//// making sure things go back to normal /////
		speedTrigger = false;
		atariBall.hitBlueBrick = false;
		atariBall.vx = 3;
		atariBall.vy = 4;
		atariBall.inShrinkSection = false;
		userPaddle.shrunk = false;

		atariBall.x = atariBall.startX;
		atariBall.y = atariBall.startY;
		//////////////////////////////////////////////R





///////////////////////////////////////////////////////////////////////////////////




////////////////////////////// starting comments //////////////////////////////////
		startQuotePicker = 1 + rand() % 5;
		switch (startQuotePicker) {
		case 1:
			PlaySound(TEXT("suffer.wav"), NULL, SND_ASYNC);				//suffer
			break;
		case 2:
			PlaySound(TEXT("best_words.wav"), NULL, SND_ASYNC);			//best words
			break;
		case 3:
			PlaySound(TEXT("beat_china.wav"), NULL, SND_ASYNC);			//beat china
			break;
		case 4:
			PlaySound(TEXT("mexico_pays.wav"), NULL, SND_ASYNC);		//mexico pays

			break;
		case 5:
			PlaySound(TEXT("really_rich.wav"), NULL, SND_ASYNC);		//really rich
			break;

		}

	}
	////////////////////////////////////////////////////////////////////////////////
	 





	if (atariScore.total > 0 && atariScore.total % 460 == 0) {
		gameOn == false;
		atariBall.number -= 1;															// add more bricks if all gone
		resetBricks();

	}










////////////////////////////////////	changing speed of ball if it hits a blue brick		//////////////////////////////////////////////////////////////////
	if (atariBall.hitBlueBrick == true && speedTrigger == false) {
		atariBall.ballBrickBoost = 2;


		////// making sure ball not too fast ///////
		if (atariBall.vx > 0) {
			atariBall.vx -= .5;
		}
		if (atariBall.vy > 0) {
			atariBall.vy -= .5;
		}
		if (atariBall.vx < 0) {
			atariBall.vx += .5;
		}
		if (atariBall.vy < 0) {
			atariBall.vy += .5;
		}
		////////////////////////////////////////////\


		atariBall.vx *= atariBall.ballBrickBoost;													
		atariBall.vy *= atariBall.ballBrickBoost;



		speedTrigger = true;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







/////////////////////   checking game status      //////////////////////////////////////////////////////////////
	if (atariBall.hitBottom == true && (atariBall.x > userPaddle.x+userPaddle.width || atariBall.x + atariBall.width < userPaddle.x)) {
		gameOn = false;
		userPaddle.hitNumber = 0;		// make sure that paddle sound won't interrupt beginning sound
		atariBall.hitBottom = false;
		if (atariBall.number < 5) {
			PlaySound(TEXT("nope.wav"), NULL, SND_ASYNC); 		//Nope!
		}
		if (atariBall.number == 5) {
			atariScore.color[1] = 255;
			atariScore.color[2] = 0;							//Make the numbers red!						
			atariScore.color[3] = 0;
			PlaySound(TEXT("you_fired.wav"), NULL, SND_ASYNC);											//You're Fired!
			
		}
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////










////////////////////////     checking what part of paddle ball hits to determine new velocity ////////////////////////////////////////////////
	switch (userPaddle.checkBallCollision(atariBall.x, atariBall.y, atariBall.height, atariBall.width, atariBall.slope)) {
	case 1:
		//atariBall.hitLeftSidePaddle = true;
		atariBall.hitCenterPaddle = true;

		
		if (atariBall.vx + userPaddle.vx != 0) {
			atariBall.vx += userPaddle.vx;
		}


		///////////////////  changing velocity if addition make ball way too fast //////////////////////////
		if (atariBall.vx + userPaddle.vx > 6 || atariBall.vx + userPaddle.vx < -6) {
			if (atariBall.vx + userPaddle.vx > 6) {
				atariBall.vx = 6;
			}
			if (atariBall.vx + userPaddle.vx < -6) {
				atariBall.vx = -6;
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////


		break;

	case 4:
		break;
	default:
		atariBall.hitCenterPaddle = true;
		break;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	if (atariBall.inShrinkSection == true) {
		userPaddle.shrunk = true;						//if ball is above bricks, shrink it
	}


	if (userPaddle.vx > 0) {
		atariTrump.travelRight = true;
		atariTrump.travelLeft = false;
	}
	if (userPaddle.vx < 0) {
		atariTrump.travelRight = false;
		atariTrump.travelLeft = true;
	}


	updateBricks();
	checkBricks();
	atariTrump.update();
	userPaddle.update();
	atariScore.update();

	


	if (gameOn == true ) {
		atariBall.update();							//only update ball if the game is in progress
	}


}









void Game::drawBrick(int x, int y, int width, int height, int r, int g, int b)
{

	for (int i = y; i < y + height; i++) {
		for (int j = x; j < x + width; j++) {
			gfx.PutPixel(j, i, r, g, b);
		}
	}
}











void Game::ComposeFrame()
{
	if (atariTrump.travelRight == true) {
		SpriteCodex::drawTrumpRight(atariTrump.x, atariTrump.y, gfx);
	}
	if (atariTrump.travelLeft == true) {
		SpriteCodex::drawTrumpLeft(atariTrump.x, atariTrump.y, gfx);
	}
	


/////////////////////////			drawing bricks			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 1; i <= 50; i++) {
		if (greenBrick[i].isBroken == false) {
			drawBrick(greenBrick[i].x, greenBrick[i].y, greenBrick[i].width, greenBrick[i].height, greenBrick[i].color[1], greenBrick[i].color[2], greenBrick[i].color[3]);
		}
		if (purpleBrick[i].isBroken == false) {
			drawBrick(purpleBrick[i].x, purpleBrick[i].y, purpleBrick[i].width, purpleBrick[i].height, purpleBrick[i].color[1], purpleBrick[i].color[2], purpleBrick[i].color[3]);
		
		}
		if (blueBrick[i].isBroken == false) {
			drawBrick(blueBrick[i].x, blueBrick[i].y, blueBrick[i].width, blueBrick[i].height, blueBrick[i].color[1], blueBrick[i].color[2], blueBrick[i].color[3]);

		}
		if (redBrick[i].isBroken == false) {
			drawBrick(redBrick[i].x, redBrick[i].y, redBrick[i].width, redBrick[i].height, redBrick[i].color[1], redBrick[i].color[2], redBrick[i].color[3]);

		}
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	if (gameOn == true && atariBall.hitBottom == false) {
		drawBrick(atariBall.x, atariBall.y, atariBall.width, atariBall.height, 255, 255, 255);//drawing atariBAll if game is on
	}


	/////////////////////////////// border ///////////////////////////////////////////////////
	drawBrick(userPaddle.x, userPaddle.y, userPaddle.width, userPaddle.height, 164, 193, 34);//drawing userPaddle
	drawBrick(0, 0, gfx.ScreenWidth - 1, 100, 108, 118, 135);// top border
	drawBrick(0, 0, 32, gfx.ScreenHeight - 1, 108, 118, 135); // left border
	drawBrick(gfx.ScreenWidth - 32, 0, 32, gfx.ScreenHeight - 1, 108, 118, 135); //right border
	////////////////////////////////////////////////////////////////////////////////////////


	SpriteCodex::drawTrumpTitle(200, 1, gfx);	//draw title




	////////////////////////////////   drawing score   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	drawDigit(atariScore.thousands, atariScore.x, atariScore.y, atariScore.width, atariScore.height, atariScore.color[1], atariScore.color[2], atariScore.color[3]);
	drawDigit(atariScore.hundreds, atariScore.x + (atariScore.width+(atariScore.width/4)), atariScore.y,atariScore.width, atariScore.height, atariScore.color[1], atariScore.color[2], atariScore.color[3]);
	drawDigit(atariScore.tens, atariScore.x + atariScore.width + (atariScore.width + (atariScore.width / 4)) + (atariScore.width/4), atariScore.y, atariScore.width, atariScore.height, atariScore.color[1], atariScore.color[2], atariScore.color[3]);
	drawDigit(atariScore.ones, atariScore.x + atariScore.width + 2 * (atariScore.width + (atariScore.width / 4)) + (atariScore.width / 4), atariScore.y, atariScore.width, atariScore.height, atariScore.color[1], atariScore.color[2], atariScore.color[3]);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	drawDigit(atariBall.number, gfx.ScreenWidth - atariScore.width - atariScore.x, atariScore.y, atariScore.width, atariScore.height, atariScore.color[1], atariScore.color[2], atariScore.color[3]);	// draw ball count

}




void Game::updateBricks() {
	int iCompensator = 0;




	/////////// setting color ////////
	for (int i = 1; i <= 50; i++) {
		greenBrick[i].setColor("green");
		blueBrick[i].setColor("blue");
		purpleBrick[i].setColor("purple");
		redBrick[i].setColor("red");
	}
	///////////////////////////////





	for (int i = 1; i <= 50; i++) {





		/////		setting the y of bricks in the array	///////
		if (i > 25) {
			redBrick[i].y = topOfBricksY;
			blueBrick[i].y = topOfBricksY + 24;
			purpleBrick[i].y = topOfBricksY + 48;
			greenBrick[i].y = topOfBricksY + 72;
			iCompensator = 25;
		}
		////////////////////////////////////////////////////////////







		/////		setting the x of bricks in the array	///////
		greenBrick[i].x = 1 +((i - iCompensator - 1) * 32);
		blueBrick[i].x = 1 + (i - iCompensator - 1) * 32;
		purpleBrick[i].x = 1 + (i - iCompensator - 1) * 32;
		redBrick[i].x = 1 + (i - iCompensator - 1) * 32;
		////////////////////////////////////////////////////////////




		


		/////		setting the y of bricks in the array	///////
		if (i <= 25) {
			redBrick[i].y = topOfBricksY + 12;
			blueBrick[i].y = topOfBricksY + 36;
			purpleBrick[i].y = topOfBricksY + 60;
			greenBrick[i].y = topOfBricksY + 84;
		}
		////////////////////////////////////////////////////////////



	}
}





void Game::checkBricks()
{
	int brokenBricks = 0;

	for (int i = 1; i <= 50; i++) {
		subBallY = atariBall.y;
		subBallX = atariBall.x;



		

/////////////////////////////////////////////////////          green                 ///////////////////////////////////////////////////////////
	if (atariBall.vy < 0) {
			if (atariBall.y <= greenBrick[i].y + greenBrick[i].height && atariBall.y - atariBall.vy >= greenBrick[i].y + greenBrick[i].height && atariBall.x + (atariBall.width/2) >= greenBrick[i].x && atariBall.x + (atariBall.width/2) <= greenBrick[i].x + greenBrick[i].width & greenBrick[i].isBroken == false && brokenBricks == 0) {
				greenBrick[i].isBroken = true;
				atariBall.hitBrickSurface = true;
				
				atariBall.y = greenBrick[i].y + greenBrick[i].height;
				atariBall.x = ((subBallY - atariBall.y) / atariBall.slope) + atariBall.x;		//changing the x of the ball so it doesn't appear to jump
				brokenBricks++;
				atariScore.total++;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					////bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					////bong.Play();
				}
				
			}
		}
		if (atariBall.vx < 0) {
			if (atariBall.x <= greenBrick[i].x + greenBrick[i].width && atariBall.x - atariBall.vx >= greenBrick[i].x + greenBrick[i].width && atariBall.y + (atariBall.height / 2) >= greenBrick[i].y && atariBall.y + (atariBall.height / 2) <= greenBrick[i].y + greenBrick[i].height & greenBrick[i].isBroken == false && brokenBricks == 0) {
				greenBrick[i].isBroken = true;
				atariBall.hitBrickSide = true;
				atariBall.x = greenBrick[i].x + greenBrick[i].width;
				atariBall.y = ((subBallX - atariBall.x) * atariBall.slope) + atariBall.y;
				brokenBricks++;
				atariScore.total++;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vy > 0) {
			if (atariBall.y + atariBall.height >= greenBrick[i].y && atariBall.y + atariBall.height - atariBall.vy <= greenBrick[i].y && atariBall.x + (atariBall.width / 2) >= greenBrick[i].x && atariBall.x + (atariBall.width / 2) <= greenBrick[i].x + greenBrick[i].width & greenBrick[i].isBroken == false && brokenBricks == 0) {
				greenBrick[i].isBroken = true;
				atariBall.hitBrickSurface = true;
				atariBall.y = greenBrick[i].y - atariBall.height;

				atariBall.x = ((subBallY - atariBall.y) / atariBall.slope) + atariBall.x;

				brokenBricks++;
				atariScore.total++;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vx > 0) {
			if (atariBall.x + atariBall.width >= greenBrick[i].x && atariBall.x + atariBall.width - atariBall.vx <= greenBrick[i].x && atariBall.y + (atariBall.height / 2) >= greenBrick[i].y && atariBall.y + (atariBall.height / 2) <= greenBrick[i].y + greenBrick[i].height & greenBrick[i].isBroken == false && brokenBricks == 0) {
				greenBrick[i].isBroken = true;
				atariBall.hitBrickSide = true;
				atariBall.x = greenBrick[i].x - atariBall.width;
				atariBall.y = ((subBallX - atariBall.x) * atariBall.slope) + atariBall.y;
				brokenBricks++;
				atariScore.total++;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











////////////////////////////////////////////////         purple          ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (atariBall.vy < 0) {
			if (atariBall.y <= purpleBrick[i].y + purpleBrick[i].height && atariBall.y - atariBall.vy >= purpleBrick[i].y + purpleBrick[i].height && atariBall.x + (atariBall.width / 2) >= purpleBrick[i].x && atariBall.x + (atariBall.width / 2) <= purpleBrick[i].x + purpleBrick[i].width & purpleBrick[i].isBroken == false && brokenBricks == 0) {
				purpleBrick[i].isBroken = true;
				atariBall.hitBrickSurface = true;
				atariBall.y = purpleBrick[i].y + purpleBrick[i].height;
				atariBall.x = ((subBallY - atariBall.y) / atariBall.slope) + atariBall.x;
				brokenBricks++;
				atariScore.total += 2;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vx < 0) {
			if (atariBall.x <= purpleBrick[i].x + purpleBrick[i].width && atariBall.x - atariBall.vx >= purpleBrick[i].x + purpleBrick[i].width && atariBall.y + (atariBall.height / 2) >= purpleBrick[i].y && atariBall.y + (atariBall.height / 2) <= purpleBrick[i].y + purpleBrick[i].height & purpleBrick[i].isBroken == false && brokenBricks == 0) {
				purpleBrick[i].isBroken = true;
				atariBall.hitBrickSide = true;
				atariBall.x = purpleBrick[i].x + purpleBrick[i].width;
				atariBall.y = ((subBallX - atariBall.x) * atariBall.slope) + atariBall.y;
				brokenBricks++;
				atariScore.total += 2;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vy > 0) {
			if (atariBall.y + atariBall.height >= purpleBrick[i].y && atariBall.y + atariBall.height - atariBall.vy <= purpleBrick[i].y && atariBall.x + (atariBall.width / 2) >= purpleBrick[i].x && atariBall.x + (atariBall.width / 2) <= purpleBrick[i].x + purpleBrick[i].width & purpleBrick[i].isBroken == false && brokenBricks == 0) {
				purpleBrick[i].isBroken = true;
				atariBall.hitBrickSurface = true;
				atariBall.y = purpleBrick[i].y - atariBall.height;
				atariBall.x = ((subBallY - atariBall.y) / atariBall.slope) + atariBall.x;
				brokenBricks++;
				atariScore.total += 2;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vx > 0) {
			if (atariBall.x + atariBall.width >= purpleBrick[i].x && atariBall.x + atariBall.width - atariBall.vx <= purpleBrick[i].x && atariBall.y + (atariBall.height / 2) >= purpleBrick[i].y && atariBall.y + (atariBall.height / 2) <= purpleBrick[i].y + purpleBrick[i].height & purpleBrick[i].isBroken == false && brokenBricks == 0) {
				purpleBrick[i].isBroken = true;
				atariBall.hitBrickSide = true;
				atariBall.x = purpleBrick[i].x - atariBall.width;
				atariBall.y = ((subBallX - atariBall.x) * atariBall.slope) + atariBall.y;
				brokenBricks++;
				atariScore.total += 2;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










//////////////////////////////////////////////////////////                blue                //////////////////////////////////////////////////////////////////////////////////////////////////////
		if (atariBall.vy < 0) {
			if (atariBall.y <= blueBrick[i].y + blueBrick[i].height && atariBall.y - atariBall.vy >= blueBrick[i].y + blueBrick[i].height && atariBall.x + (atariBall.width / 2) >= blueBrick[i].x && atariBall.x + (atariBall.width / 2) <= blueBrick[i].x + blueBrick[i].width & blueBrick[i].isBroken == false && brokenBricks == 0) {
				blueBrick[i].isBroken = true;
				atariBall.hitBrickSurface = true;
				atariBall.y = blueBrick[i].y + blueBrick[i].height;
				atariBall.x = ((subBallY - atariBall.y) / atariBall.slope) + atariBall.x;
				brokenBricks++;
				atariBall.hitBlueBrick = true;
				atariScore.total += 3;
				brickCounter++;

				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vx < 0) {
			if (atariBall.x <= blueBrick[i].x + blueBrick[i].width && atariBall.x - atariBall.vx >= blueBrick[i].x + blueBrick[i].width && atariBall.y + (atariBall.height / 2) >= blueBrick[i].y && atariBall.y + (atariBall.height / 2) <= blueBrick[i].y + blueBrick[i].height & blueBrick[i].isBroken == false && brokenBricks == 0) {
				blueBrick[i].isBroken = true;
				atariBall.hitBrickSide = true;
				atariBall.x = blueBrick[i].x + blueBrick[i].width;
				atariBall.y = ((subBallX - atariBall.x) * atariBall.slope) + atariBall.y;
				brokenBricks++;
				atariBall.hitBlueBrick = true;
				atariScore.total += 3;
				brickCounter++;

				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vy > 0) {
			if (atariBall.y + atariBall.height >= blueBrick[i].y && atariBall.y + atariBall.height - atariBall.vy <= blueBrick[i].y && atariBall.x + (atariBall.width / 2) >= blueBrick[i].x && atariBall.x + (atariBall.width / 2) <= blueBrick[i].x + blueBrick[i].width & blueBrick[i].isBroken == false && brokenBricks == 0) {
				blueBrick[i].isBroken = true;
				atariBall.hitBrickSurface = true;
				atariBall.y = blueBrick[i].y - atariBall.height;
				atariBall.x = ((subBallY - atariBall.y) / atariBall.slope) + atariBall.x;
				brokenBricks++;
				atariBall.hitBlueBrick = true;
				atariScore.total += 3;
				brickCounter++;

				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vx > 0) {
			if (atariBall.x + atariBall.width >= blueBrick[i].x && atariBall.x + atariBall.width - atariBall.vx <= blueBrick[i].x && atariBall.y + (atariBall.height / 2) >= blueBrick[i].y && atariBall.y + (atariBall.height / 2) <= blueBrick[i].y + blueBrick[i].height & blueBrick[i].isBroken == false && brokenBricks == 0) {
				blueBrick[i].isBroken = true;
				atariBall.hitBrickSide = true;
				atariBall.x = blueBrick[i].x - atariBall.width;
				atariBall.y = ((subBallX - atariBall.x) * atariBall.slope) + atariBall.y;
				brokenBricks++;
				atariBall.hitBlueBrick = true;
				atariScore.total += 3;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		









		
//////////////////////////////////////////////////////////                red                //////////////////////////////////////////////////////////////////////////////////////////////////////
		if (atariBall.vy < 0) {
			if (atariBall.y <= redBrick[i].y + redBrick[i].height && atariBall.y - atariBall.vy >= redBrick[i].y + redBrick[i].height && atariBall.x + (atariBall.width / 2) >= redBrick[i].x && atariBall.x + (atariBall.width / 2) <= redBrick[i].x + redBrick[i].width & redBrick[i].isBroken == false && brokenBricks == 0) {
				redBrick[i].isBroken = true;
				atariBall.hitBrickSurface = true;
				atariBall.y = redBrick[i].y + redBrick[i].height;
				atariBall.x = ((subBallY - atariBall.y) / atariBall.slope) + atariBall.x;
				brokenBricks++;
				atariBall.hitBlueBrick = true;
				atariScore.total += 4;
				brickCounter++;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vx < 0) {
			if (atariBall.x <= redBrick[i].x + redBrick[i].width && atariBall.x - atariBall.vx >= redBrick[i].x + redBrick[i].width && atariBall.y + (atariBall.height / 2) >= redBrick[i].y && atariBall.y + (atariBall.height / 2) <= redBrick[i].y + redBrick[i].height & redBrick[i].isBroken == false && brokenBricks == 0) {
				redBrick[i].isBroken = true;
				atariBall.hitBrickSide = true;
				atariBall.x = redBrick[i].x + redBrick[i].width;
				atariBall.y = ((subBallX - atariBall.x) * atariBall.slope) + atariBall.y;
				brokenBricks++;
				atariBall.hitBlueBrick = true;
				atariScore.total += 4;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vy > 0) {
			if (atariBall.y + atariBall.height >= redBrick[i].y && atariBall.y + atariBall.height - atariBall.vy <= redBrick[i].y && atariBall.x + (atariBall.width / 2) >= redBrick[i].x && atariBall.x + (atariBall.width / 2) <= redBrick[i].x + redBrick[i].width & redBrick[i].isBroken == false && brokenBricks == 0) {
				redBrick[i].isBroken = true;
				atariBall.hitBrickSurface = true;
				atariBall.y = redBrick[i].y - atariBall.height;
				atariBall.x = ((subBallY - atariBall.y) / atariBall.slope) + atariBall.x;
				brokenBricks++;
				atariBall.hitBlueBrick = true;
				atariScore.total += 4;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
		if (atariBall.vx > 0) {
			if (atariBall.x + atariBall.width >= redBrick[i].x && atariBall.x  + atariBall.width - atariBall.vx <= redBrick[i].x && atariBall.y + (atariBall.height / 2) >= redBrick[i].y && atariBall.y + (atariBall.height / 2) <= redBrick[i].y + redBrick[i].height & redBrick[i].isBroken == false && brokenBricks == 0) {
				redBrick[i].isBroken = true;
				atariBall.hitBrickSide = true;
				atariBall.x = redBrick[i].x - atariBall.width;
				atariBall.y = ((subBallX - atariBall.x) * atariBall.slope) + atariBall.y;
				brokenBricks++;
				atariBall.hitBlueBrick = true;
				atariScore.total += 4;
				brickCounter++;
				if (brickCounter % 2 == 1) {
					//bing.Play()();
				}

				if (brickCounter % 2 == 0) {
					//bong.Play();
				}
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
	

	}
	if (gameOn == true) {
		atariBall.update();
		atariBall.y += atariBall.vy;
		atariBall.x += atariBall.vx;

	}

}



void Game::drawDigit(int digit, int x, int y, int width, int height, int color1, int color2, int color3)
{
	switch (digit) {
	case 0:
		
		for (int i = y; i <= y + height; i++) {
			for (int j = x; j <= x + (width / 3); j++) {											//left
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		
		for (int i = y; i <= y + (height / 4); i++) {
			for (int j = x; j <= x + width; j++) {												//top
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		
		for (int i = y; i <= y + height; i++) {
			for (int j = (x + width) - (width/3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		
		
		for (int i = y + height - (height/4); i <= y + height; i++) {
			for (int j = x; j <= x + width; j++) {												//bottom
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		
		break;
	case 1:
		for (int i = y; i <= y + height; i++) {
			for (int j = x + (width/4); j <= x + ((3*width) / 4); j++) {
				gfx.PutPixel(j, i, color1, color2, color3);	
			}
		}
		break;



	case 2:
		for (int i = y; i <= y + (height / 5); i++) {
			for (int j = x; j <= x + width; j++) {												//top
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}


		for (int i = y; i <= y + ((3*height)/5) ; i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}


		for (int i = y + ((height*2)/5); i <= y + ((height*3)/5); i++) {
			for (int j = x; j <= x + width; j++) {												//center
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}


		for (int i = y + ((height * 2) / 5); i <= y + height; i++) {
			for (int j = x; j <= x + (width / 3); j++) {											//left
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + height - (height / 5); i <= y + height; i++) {
			for (int j = x; j <= x + width; j++) {												//bottom
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		break;



	case 3:
		for (int i = y; i <= y + (height / 5); i++) {
			for (int j = x; j <= x + width; j++) {												//top
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}


		for (int i = y; i <= y + ((3 * height) / 5); i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}


		for (int i = y + ((height * 2) / 5); i <= y + ((height * 3) / 5); i++) {
			for (int j = x; j <= x + width; j++) {												//center
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + ((3 * height) / 5); i <= y + height; i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right (bottom)
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + height - (height / 5); i <= y + height; i++) {
			for (int j = x; j <= x + width; j++) {												//bottom
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		break;


	case 4:


		for (int i = y; i <= y + ((2*height)/3); i++) {
			for (int j = x; j <= x + (width / 3); j++) {											//left
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + (height / 3); i <= y + ((2 * height) / 3); i++) {
			for (int j = x; j <= x + width; j++) {													//center
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y; i <= y + height; i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		break;

	case 5:

		for (int i = y; i <= y + (height / 5); i++) {
			for (int j = x; j <= x + width; j++) {												//top
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y ; i <= y + ((height * 2) / 5); i++) {
			for (int j = x; j <= x + (width / 3); j++) {											//left
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + ((height * 2) / 5); i <= y + ((height * 3) / 5); i++) {
			for (int j = x; j <= x + width; j++) {												//center
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + ((3 * height) / 5); i <= y + height; i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + height - (height / 5); i <= y + height; i++) {
			for (int j = x; j <= x + width; j++) {												//bottom
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		break;



	case 6:
		for (int i = y; i <= y + height; i++) {
			for (int j = x; j <= x + (width / 3); j++) {											//left
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		for (int i = y + (height / 3); i <= y + (height / 2); i++) {
			for (int j = x; j <= x + width; j++) {													//center
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		for (int i = y + (height/3); i <= y + height; i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		for (int i = y + height - (height / 4); i <= y + height; i++) {
			for (int j = x; j <= x + width; j++) {												//bottom
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		break;


	case 7:


		for (int i = y; i <= y + (height / 4); i++) {
			for (int j = x; j <= x + width; j++) {												//top
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y; i <= y + height; i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}
		break;



	case 8:

		for (int i = y; i <= y + height; i++) {
			for (int j = x; j <= x + (width / 3); j++) {											//left
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y; i <= y + (height / 4); i++) {
			for (int j = x; j <= x + width; j++) {												//top
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y; i <= y + height; i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + ((height * 2) / 5); i <= y + ((height * 3) / 5); i++) {
			for (int j = x; j <= x + width; j++) {												//center
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y + height - (height / 4); i <= y + height; i++) {
			for (int j = x; j <= x + width; j++) {												//bottom
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		break;



	case 9:


		for (int i = y; i <= y + (height / 2); i++) {
			for (int j = x; j <= x + (width / 3); j++) {											//left
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y; i <= y + (height / 4); i++) {
			for (int j = x; j <= x + width; j++) {												//top
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}


		for (int i = y + (height / 3); i <= y + (height / 2); i++) {
			for (int j = x; j <= x + width; j++) {													//center
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		for (int i = y; i <= y + height; i++) {
			for (int j = (x + width) - (width / 3); j <= x + width; j++) {							//right
				gfx.PutPixel(j, i, color1, color2, color3);
			}
		}

		break;
	default:
		break;
	}
}

void Game::resetBricks()
{
	for (int i = 1; i <= 50; i++) {
		greenBrick[i].isBroken = false;
		purpleBrick[i].isBroken = false;
		blueBrick[i].isBroken = false;
		redBrick[i].isBroken = false;

	}
}



















