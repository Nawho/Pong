
#include "Game.h"
#include "Ball.h"
#include "Constants.h"
#include <SDL_mixer.h>
#include "iostream"
#include <SDL_ttf.h>
#include "AudioManager.h"


bool Game::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;
	if (TTF_Init() != 0) return false;

	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window) return false;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) return false;

	leftPaddle = new Paddle(1);
	rightPaddle = new Paddle(2);
	ball = new Ball();

	middleLine.w = 10;
	middleLine.h = SCREEN_HEIGHT;
	middleLine.x = SCREEN_WIDTH / 2 - middleLine.w / 2;
	middleLine.y = 0;	

	const std::string ArcadeFont = Paths::FONTS + "ARCADE_I.TTF";

	textFont = TTF_OpenFont(ArcadeFont.c_str(), FONT_SIZE);
	timerFont = TTF_OpenFont(ArcadeFont.c_str(), FONT_SIZE + 20);

	if (!textFont || !timerFont) return false;

	plr1Score = 0;
	CPUScore = 0;
	gameState = 0;

	roundStartTime = SDL_GetTicks();

	SetTextToRect((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 - 50), MENU_TEXT_1.c_str(), textFont, &textTexture1, &textRect1);
	SetTextToRect((SCREEN_WIDTH / 2), (textRect1.y + textRect1.h + 20), MENU_TEXT_2.c_str(), textFont, &textTexture2, &textRect2);

	return true;
}

void Game::GameLoop() {
	while (isRunning) {
		Game::HandleEvents();
		Game::Update();
		Game::Draw();
	}
}

void Game::Draw() {
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	if (gameState == 0) {
		SDL_RenderCopy(renderer, textTexture1, NULL, &textRect1);
		SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

	} else if (gameState == 1) {
		SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
		SDL_RenderFillRect(renderer, leftPaddle->GetRect());

		SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
		SDL_RenderFillRect(renderer, rightPaddle->GetRect());

		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 160);
		SDL_RenderFillRect(renderer, &middleLine);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, ball->GetRect());

		SDL_RenderCopy(renderer, timerTexture, NULL, &timerRect);
		SDL_RenderCopy(renderer, plrScoreTexture, NULL, &plrScoreRect);
		SDL_RenderCopy(renderer, CPUScoreTexture, NULL, &CPUScoreRect);
	}
	else if (gameState == 2) {
		SDL_RenderCopy(renderer, textTexture1, NULL, &textRect1);
		SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);
	}

	SDL_RenderPresent(renderer);
}

void Game::Update() {
	if (gameState == 0) {
		plr1Score = 0;
		CPUScore = 0;
	}
	else if (gameState == 1) {
		leftPaddle->Update();
		rightPaddle->Update();
		ball->Update(leftPaddle, rightPaddle);
		CheckAndUpdateScore();
		CheckGameEnd();
		CPUPaddleMovement(rightPaddle, ball);
	}
}

void Game::CheckAndUpdateScore() {
	if (ball->GetRect()->x < 0) {
		CPUScore++;
		ball->ResetPos();
	}
	else if (ball->GetRect()->x > SCREEN_WIDTH) {
		plr1Score++;
		ball->ResetPos();
	}
}

void Game::HandleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) isRunning = false;

		const Uint8* keyStates = SDL_GetKeyboardState(NULL);

		//Salir [ESC]
		if (keyStates[SDL_SCANCODE_ESCAPE]) {
			isRunning = false;
		}

		//Movimiento de jugador + controles de menú: [W], [S]
		leftPaddle->SetDir(0);
		if (keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP]) {
			//Setea la posición de la paleta del jugador para arriba (-1)
			leftPaddle->SetDir(-1);

			if (gameState == 0) {
				gameState = 1;
				ball->ResetPos();
				roundStartTime = SDL_GetTicks();
			}
		}
		else if (keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN]) {
			//Setea la posición de la paleta del jugador para abajo (1)
			leftPaddle->SetDir(1);

			if (gameState == 2) {
				SDL_Delay(1000);
				gameState = 0;

				SetTextToRect((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 - 50), MENU_TEXT_1.c_str(), textFont, &textTexture1, &textRect1);
				SetTextToRect((SCREEN_WIDTH / 2), (textRect1.y + textRect1.h + 20), MENU_TEXT_2.c_str(), textFont, &textTexture2, &textRect2);
			}
		}
	}
}


void Game::SetTextToRect(int x, int y, const char* text,
	TTF_Font* font, SDL_Texture** texture, SDL_Rect* rect) {
	int text_width;
	int text_height;
	SDL_Surface* surface;
	SDL_Color textColor = { 255, 255, 255, 255 };

	surface = TTF_RenderText_Solid(font, text, textColor);
	*texture = SDL_CreateTextureFromSurface(renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);

	rect->x = x - text_width / 2;
	rect->y = y;
	rect->w = text_width;
	rect->h = text_height;
}

void  Game::CheckGameEnd() {
	uint32_t currTime = SDL_GetTicks();
	int elapsedTime = (currTime - roundStartTime) / 1000;

	SetTextToRect((SCREEN_WIDTH / 2), 20, std::to_string(ROUND_DURATION - elapsedTime).c_str(), timerFont, &timerTexture, &timerRect);
	SetTextToRect((SCREEN_WIDTH / 4), 40, std::to_string(plr1Score).c_str(), timerFont, &plrScoreTexture, &plrScoreRect);
	SetTextToRect((SCREEN_WIDTH / 4 * 3), 40, std::to_string(CPUScore).c_str(), timerFont, &CPUScoreTexture, &CPUScoreRect);

	if (elapsedTime == ROUND_DURATION || plr1Score == 11 || CPUScore == 11) {
		std::string winnerMessage;
		std::string gameEndMessage = "Presiona [S] para volver al menu.";

		if (plr1Score > CPUScore) {
			winnerMessage = "Has ganado! :D";
		}
		else if (plr1Score < CPUScore) {
			winnerMessage = "Has perdido! :(";
		}
		else {
			winnerMessage = "Empate!";
		}

		roundStartTime = currTime;
		gameState = 2;

		SetTextToRect((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 - 50), winnerMessage.c_str(), textFont, &textTexture1, &textRect1);
		SetTextToRect((SCREEN_WIDTH / 2), textRect1.y + textRect1.h + 20, gameEndMessage.c_str(), textFont, &textTexture2, &textRect2);
	}
}

void Game::CPUPaddleMovement(Paddle* cpuPaddle, Ball* ball) {
	if (ball->GetRect()->y + ball->GetRect()->h > cpuPaddle->GetRect()->y && 
		ball->GetRect()->y < cpuPaddle->GetRect()->y + cpuPaddle->GetRect()->h) {
		//pelota pegará contra paleta, quedarse quieto
	}
	else {
		if (ball->GetVerticalDirection() == -1) {
			cpuPaddle->SetDir(-1);
		}
		else if (ball->GetVerticalDirection() == 1) {
			cpuPaddle->SetDir(1);
		}
	}
}

void Game::ShutDown() {
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture2);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

