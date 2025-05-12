#include "Bullet.h"
#include <iostream>
Bullet::Bullet() {
	setSymbol('^');
	setColor(RED);
};

Bullet::Bullet(Bullet& obj) {
	this->direction = obj.direction;
}

Bullet& Bullet::operator=(const Bullet& other) {
	if (this != &other) {
		direction = other.direction;
	}
	return *this;
}

int Bullet::getDirection() const {
	return direction;
}

void Bullet::setDirection(int direction) {
	this->direction = direction;
}

void Bullet::render() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BACKGROUND_COLOR);
}

void Bullet::update() {

	render();
	Sleep(100);
	if (getY() >= 0) {
		draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
		setY(getY() - 1);
	}
}