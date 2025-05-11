#include "Bullet.h"
#include <iostream>
Bullet::Bullet() {
	setSymbol('^');
	setColor(RED);
	//setY(getY() - 1);
	//setX(getX());
};

Bullet::Bullet(int x, int y, int direction, char symbol) : GameObject() {
	setSymbol(symbol);
	setColor(RED);
	setY(y);
	setX(x);
	this->direction = direction;
	if (direction == 1) {
		setY(getY() - 1);
	}
	else if (direction == 2) {
		setY(getY() + 1);
	}
	else if (direction == 3) {
		setX(getX() - 1);
	}
	else if (direction == 4) {
		setX(getX() + 1);
	}
}

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
	//setX(getX());
	cout << "Bullet at " << "Symbol: " << getSymbol() << " Y: " << getY() << " X: " << getX() << " Color: " << getColor() << endl;
	draw_char(getSymbol(), getY(), getX(), getColor(), BLACK);
}

void Bullet::update() {

	render();
	Sleep(100);
	if (getY() >= 0) {
		//cout << "Bullet fired! at " << "Symbol: " << getSymbol() << " Y: " << getY() << " X: " << getX() << " Color: " << getColor() << endl;

		draw_char(' ', getY(), getX(), BLACK, BLACK);
		setY(getY() - 1);
	}
}