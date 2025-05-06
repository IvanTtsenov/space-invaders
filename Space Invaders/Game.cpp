#include "Game.h"
#include <iostream>

Game::Game() {

}

void Game::run()
{
	Player player;
	player.setSymbol('A');
	player.setX(118 / 2);
	player.setY(29);
	player.setColor(GREEN);
	player.render();
}