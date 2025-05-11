#include <iostream>
#include <conio.h>
#include "Game.h"
#include "visualisation.h"
#include "Bullet.h"
#include "Player.h"
Game::Game() {
	player.render();
}

Game::Game(Game& obj) {
	this->player = obj.player;
	this->enemies = obj.enemies;
	this->bullets = obj.bullets;
	this->score = obj.score;
	this->level = obj.level;
	this->running = obj.running;
}

void Game::setRunning(bool running) {
	this->running = running;
}

bool Game::isRunning() const {
	return running;
}

void Game::setScore(int score) {
	this->score = score;
}

int Game::getScore() const {
	return score;
}

void Game::setLevel(int level) {
	this->level = level;
}

int Game::getLevel() const {
	return level;
}

void Game::initializeEnemies() {
	// Initialize enemies here
}

void Game::input() {
		if (_kbhit()) {
			int key = _getch();
			if (key == 224) {        // First code for arrow keys
				key = _getch();      // Second code tells which arrow
				if (key == 75) {
					player.moveLeft(); // Move right
				}
				else if (key == 77) {
					player.moveRight();
				}
				else if (key == 72) {
					bullets.push_back(player.shoot());
			}
			//cout << "Player at " << "Symbol: " << player.getSymbol() << "Y: " << player.getY() << "X: " << player.getX() << "Color: " << player.getColor() << endl;

			draw_char(player.getSymbol(), player.getY(), player.getX(), player.getColor(), BLACK);
		}
	}
}

void Game::update() {
	for (auto b : bullets) {
		b->update();
	}
	bullets.clear();
	//bullets.erase(
	//	std::remove_if(bullets.begin(), bullets.end(), [](Bullet* b) {
	//		if (b->getY() < 0) {
	//			delete b;
	//			return true;
	//		}
	//		return false;
	//		}),
	//	bullets.end()
	//);
	//for (auto b : enemies) {
	//	b->update();
	//}
}

void Game::checkCollisions() {
	// Check for collisions here
}

void Game::render() {
	player.render();
}

void Game::run()
{
	Game game;
	setRunning(true);
	while (isRunning())
	{
		game.render();
		game.input();
		game.update();
		game.checkCollisions();
		game.initializeEnemies();
	}
}