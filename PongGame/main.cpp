#include "Game.h"
#include <SDL.h>
#include "iostream"

int main(int argc, char *argv[]) {
	Game game;
	
	if (game.Init()) {
		game.GameLoop();
	}
	else {
		std::cerr << "Error: Initalization failed" << std::endl;
	}
	return 0;
}

