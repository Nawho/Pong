#include "Ball.h"
#include "Constants.h"
#include "Paddle.h"
#include "iostream"
#include <SDL_mixer.h>
#include "AudioManager.h"

Ball::Ball() {
	pos.y = SCREEN_HEIGHT / 2 - size / 2;
	pos.x = SCREEN_WIDTH / 2 - size / 2;
	rect.w = size;
	rect.h = size;
	rect.x = pos.x;
	rect.y = pos.y;
	vel.x = 1;
	vel.y = 1;
	speed = BALL_INIT_SPEED;

	audioManager = AudioManager::getInstance();

	paddleCollisionSound = audioManager.loadAudio("PaddleBounce.wav");
	wallCollisionSound = audioManager.loadAudio("WallBounce.wav");
	plrPointSound = audioManager.loadAudio("PlrPoint.wav");
	cpuPointSound = audioManager.loadAudio("cpuPoint.wav");
}


void Ball::Update(Paddle* leftPaddle, Paddle* rightPaddle) {
	pos.x += vel.x * speed;
	pos.y += vel.y * speed;

	if (rect.x <= 0) {
		audioManager.playAudio(cpuPointSound);
	} else if (pos.x + size > SCREEN_WIDTH) {
		audioManager.playAudio(plrPointSound);
	}

	if (pos.y <= 0) { 
		pos.y = 1; 
		vel.y *= -1;
		audioManager.playAudio(wallCollisionSound);
	} else if ((pos.y + size) >= SCREEN_HEIGHT) {
		pos.y = SCREEN_HEIGHT - size - 1;
		vel.y *= -1;
		audioManager.playAudio(wallCollisionSound);
	}
	
	rect.x = pos.x;
	rect.y = pos.y;

	CheckCollision(leftPaddle);
	CheckCollision(rightPaddle);
}

void Ball::CheckCollision(Paddle* paddle) {
	if (SDL_HasIntersection(&rect, paddle->GetRect())) {
		vel.x *= -1;
		pos.x += 2 * vel.x;

		//touch with lower and upper ends
		if (pos.y == (paddle->GetRect()->y + paddle->GetRect()->h)) {
			pos.y += 2;
			vel.y = 1;
		} else if (pos.y + size == paddle->GetRect()->y) {
			pos.y -= 2;
			vel.y = -1;
		}

		if (speed + 1 < BALL_MAX_SPEED) speed++;

		audioManager.playAudio(paddleCollisionSound);
	}
}


SDL_Rect* Ball::GetRect() {
	return &rect;
}

void Ball::ResetPos() {
	pos.y = SCREEN_HEIGHT / 2 - size / 2;
	pos.x = SCREEN_WIDTH / 2 - size / 2;

	vel.x = 1;
	vel.y = 1;

	speed = BALL_INIT_SPEED;
}

int Ball::GetVerticalDirection() {
	return vel.y;
}