#include "Enemy.h"
#include "Game.h"
#include <iostream>
using namespace std;
Enemy::Enemy() {

};

Enemy::Enemy(Enemy& obj) {
	this->direction = obj.direction;
}

Enemy& Enemy::operator=(const Enemy& other) {
	if (this != &other) {
		direction = other.direction;
	}
	return *this;
}

int Enemy::getDirection() const {
	return direction;
}

void Enemy::setDirection(int direction) {
	this->direction = direction;
}

int Enemy::getUpdateCounter() const {
	return updateCounter;
}

void Enemy::setUpdateCounter(int updateCounter) {
	this->updateCounter = updateCounter;
}

int Enemy::getSlowEnemySpeed() const {
	return slowEnemySpeed;
}

void Enemy::setSlowEnemySpeed(int slowEnemySpeed, int level) {
	if (level == 1) {
		this->slowEnemySpeed = slowEnemySpeed;
	}
	else if (level == 2) {
		this->slowEnemySpeed = slowEnemySpeed - 25;
	}
	else if (level == 3) {
		this->slowEnemySpeed = slowEnemySpeed - 50;
	}
}

void Enemy::update() {
	updateCounter++;

	if (updateCounter >= slowEnemySpeed) {
		draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
		setY(getY() + getDirection());
		if (getY() <= 29) {
			render();
		}
		updateCounter = 0;
	}
}

void Enemy::render() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BACKGROUND_COLOR);
}

Enemy* Enemy::createEnemies() {
	Enemy* enemy = new Enemy();
	enemy->setX(0 + getDirection());
	enemy->setY(2);
	enemy->setDirection(1);
	enemy->setSymbol('K');
	enemy->setColor(BLUE);
	return enemy;
}