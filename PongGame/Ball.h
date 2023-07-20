#pragma once

#include<SDL.h>
#include "Constants.h"
#include "Utils.h"
#include "Paddle.h"
#include <SDL_mixer.h>
#include "AudioManager.h"

class Ball
{
public:
	Ball();
	void Update(Paddle* leftPaddle, Paddle* rightPaddle);
	void CheckCollision(Paddle* paddle);
	SDL_Rect* GetRect();
	int GetVerticalDirection();
	void ResetPos();
	
private:
	int size = BALL_SIZE;
	float speed;
	Vec2 pos, vel;
	SDL_Rect rect;

	AudioManager audioManager = AudioManager::getInstance();

	Mix_Chunk* wallCollisionSound;
	Mix_Chunk* paddleCollisionSound;
	Mix_Chunk* cpuPointSound;
	Mix_Chunk* plrPointSound;
};

