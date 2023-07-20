#pragma once
#include <string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int PADDLE_SPEED = 15;
const int PADDLE_WIDTH = 25; 
const int PADDLE_HEIGHT = 140;

const int BALL_SIZE = 20;
const int BALL_INIT_SPEED = 7;
const int BALL_MAX_SPEED = 17;

const int ROUND_DURATION = 120;

const int FONT_SIZE = 35;

const std::string MENU_TEXT_1 = "Bienvenido a PONG!";
const std::string MENU_TEXT_2 = "Presione [W] para comenzar.";

namespace Paths {
	const std::string FONTS = "Assets\\Fonts\\";
	const std::string AUDIO = "Assets\\Audio\\";
	const std::string IMAGES = "Assets\\Imgs\\";
}

