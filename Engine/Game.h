/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include "Score.h"
#include "Trump.h"
#include "Sound.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	
	Brick greenBrick[51];
	Brick blueBrick[51];
	Brick purpleBrick[51];
	Brick redBrick[51];
	Ball atariBall;
	Paddle userPaddle;
	Score atariScore;
	Trump atariTrump;
	
	void drawBrick(int x, int y, int width, int height, int r, int g, int b);
	void updateBricks();
	void checkBricks();
	void drawDigit(int digit,int x, int y, int width, int height, int color1, int color2, int color3);
	void resetBricks();
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/

	int runCounter = 0;

	const int topOfBricksY = 200;
	int subBallVY = 4;
	int subBallVX = 3;
	bool velocityChange = false;
	bool gameOn = false;
	bool speedTrigger = false;
	int subBallY;
	int subBallX;
	
	int startQuotePicker;


	int brickSubVX;
	int brickSubVY;
	int brickCounter = 0;
	/*
	Sound nope;
	Sound fired;
	Sound bing;
	Sound bong;
	*/
	/*  User Variables              */
	/********************************/
};