#include "Enemy.h"

Enemy::Enemy() 
	: GameObject(), direction(1), updateCounter(0), slowEnemySpeed(100) {

}

Enemy::~Enemy(){}

Enemy::Enemy(int x, int y, char symbol, COLORS color, int direction, int updateCounter, int slowEnemySpeed)
:GameObject(x,y,symbol,color),direction(direction),updateCounter(updateCounter),slowEnemySpeed(slowEnemySpeed){}


Enemy::Enemy(const Enemy& obj)
	:GameObject(obj), direction(obj.direction), updateCounter(obj.updateCounter), slowEnemySpeed(obj.slowEnemySpeed) {}

Enemy& Enemy::operator=(const Enemy& other) {
	if (this != &other) {
		GameObject::operator=(other);
		direction = other.direction;
		updateCounter = other.updateCounter;
		slowEnemySpeed = other.slowEnemySpeed;
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
	if (updateCounter >= 10) {
		draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
		setY(getY() + getDirection());
		if (getY() <= POLE_ROWS) {
			render();
		}
		updateCounter = 0;
	}
}

void Enemy::render() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BACKGROUND_COLOR);
}
