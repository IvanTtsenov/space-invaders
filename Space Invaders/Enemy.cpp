#include "Enemy.h"

Enemy::Enemy() 
	: GameObject(), direction(1) {
}

Enemy::~Enemy(){}

Enemy::Enemy(int x, int y, char symbol, COLORS color, int direction)
:GameObject(x,y,symbol,color),direction(direction){}


Enemy::Enemy(const Enemy& obj)
	:GameObject(obj), direction(obj.direction) {}

Enemy& Enemy::operator=(const Enemy& other) {
	if (this != &other) {
		GameObject::operator=(other);
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
		if (getY() <= POLE_ROWS) {
			render();
		}
	}

void Enemy::render() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BACKGROUND_COLOR);
}
