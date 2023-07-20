#include "Paddle.h"
#include "Constants.h"
#include "iostream"

Paddle::Paddle(int plr) {
	if (plr == 1) pos.x = 0;
	else pos.x = SCREEN_WIDTH - width;

	speed = 15.f;
	pos.y = SCREEN_HEIGHT / 2 - height / 2;

	rect.w = width;
	rect.h = height;
	rect.x = pos.x;
	rect.y = pos.y;
}

void Paddle::Update() {
	pos.y += yDir * speed;

	if (pos.y <= 0) pos.y = 0;
	else if (pos.y >= SCREEN_HEIGHT - height) pos.y = (SCREEN_HEIGHT - height);

	rect.y = pos.y;
}

void Paddle::SetDir(int dir) {
	yDir = dir;
}

SDL_Rect* Paddle::GetRect() {
	return &rect;
}