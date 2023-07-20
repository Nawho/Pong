#include <SDL.h>
#include <SDL_ttf.h>
#include "Paddle.h"
#include "Ball.h"
#include <vector>
#include "AudioManager.h"
#pragma once
class Game
{
public:

	bool Init();
	void GameLoop();
	void ShutDown();

	void HandleEvents();
	void Update();
	void Draw();

private:
	int isRunning = true;
	int gameState = 0;
	int plr1Score = 0;
	int CPUScore = 0;
	int roundStartTime = 0;

	Paddle* leftPaddle;
	Paddle* rightPaddle;
	Ball* ball;

	SDL_Rect middleLine;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* textFont;
	TTF_Font* timerFont;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture1, * textTexture2, * timerTexture, * plrScoreTexture, * CPUScoreTexture;
	SDL_Rect textRect1, textRect2, timerRect, plrScoreRect, CPUScoreRect; 

	AudioManager audioManager = AudioManager::getInstance();

	void CheckAndUpdateScore();
	void CheckGameEnd();
	void CPUPaddleMovement(Paddle* cpuPaddle, Ball* ball);
	void SetTextToRect(int x, int y, const char* text,
		TTF_Font* font, SDL_Texture** texture, SDL_Rect* rect);
};

