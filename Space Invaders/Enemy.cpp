#include "Enemy.h"
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
void Enemy::update() {
	draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
	setY(getY() + getDirection());

	if (getY() <= 29) {
		render();
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