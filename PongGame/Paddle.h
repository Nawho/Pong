#pragma once

#include<SDL.h>
#include "Constants.h"
#include "Utils.h"

class Paddle
{
public:
	Paddle(int plr);
	void Update();
	void SetDir(int dir);
	SDL_Rect* GetRect();

private:
	int yDir = 0;
	int width = PADDLE_WIDTH;
	int height = PADDLE_HEIGHT;
	float speed = PADDLE_SPEED;
	Vec2 pos;
	SDL_Rect rect;
};

