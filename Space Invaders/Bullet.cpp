#include "Bullet.h"
#include <iostream>
Bullet::Bullet() {};

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
	while (getY() > 0) {
	setSymbol('^');
	setColor(RED);
	setY(getY() - 1);
	setX(getX());
	//cout << "Bullet fired! at " << "Symbol: " << getSymbol() << "Y: " << getY() << "X: " << getX() << "Color: " << getColor() << endl;
	update();
	Sleep(100);
	draw_char(getSymbol(), getY(), getX(), BLACK, BLACK);
	}
	draw_char(getSymbol(), getY(), getX(), BLACK, BLACK);

}

void Bullet::update() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BLACK);
}