#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "visualisation.h"
#include "Bullet.h"
#include "Player.h"

Game::Game() {
	setLevel(1);

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
		if (enemies.size() <= 118) {
			Enemy* newEnemy = enemy.createEnemies();
			newEnemy->setX(rand() % 119);
			newEnemy->setY(2);
			newEnemy->setSlowEnemySpeed(100, getLevel());
			enemies.push_back(newEnemy);
		}
}


void Game::input() {
		if (_kbhit()) {
			int key = _getch();
			if (key == 'a' || key == 'A') {
				player.moveLeft();
			}
			else if (key == 'd' || key == 'D') {
				player.moveRight();
			}
			else if (key == ' ' || key == 'w' || key == 'W') {
				bullets.push_back(player.shoot());
			}
			if (key == 224) { 
				key = _getch();
				if (key == 75) {
					player.moveLeft();
				}
				else if (key == 77) {
					player.moveRight();
				}
				else if (key == 72) {
					bullets.push_back(player.shoot());

			}
			draw_char(player.getSymbol(), player.getY(), player.getX(), player.getColor(), BACKGROUND_COLOR);
		}
	}
}

void Game::update() {

	for (auto it = bullets.begin(); it != bullets.end(); ) {
		auto b = *it;
		b->update();
		if (b->getY() < 2) {
			delete b;
			it = bullets.erase(it);
		}
		else {
			++it; 
		}
	}

		for (auto it = enemies.begin(); it != enemies.end(); ) {
			auto e = *it;
			e->update();
			if (e->getY() > 29) {
				delete e;
				it = enemies.erase(it);
			}
			else {
				++it;
			}
		}
	}

void Game::checkCollisions() {
	// Check for collisions here
}

void Game::render() {
	player.render();
}

void Game::run()
{
	cout <<"Level: " << getLevel() << string((118 - 36) / 2, ' ') << "Score: " << player.getScore() << "     " << "Lives: " << player.getLives() << endl;
	cout << string(118, '-') << endl;
	setRunning(true);
	while (isRunning())
	{
		render();
		input();
		update();
		checkCollisions();
		initializeEnemies();
		Sleep(10);
	}
}