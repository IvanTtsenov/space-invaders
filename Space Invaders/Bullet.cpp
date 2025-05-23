#include "Bullet.h"

Bullet::Bullet() : GameObject(),direction(-1) {
};

Bullet::~Bullet() {};

Bullet::Bullet(int x, int y, char symbol, COLORS color, int direction)
	: GameObject(x, y, symbol, color), direction(direction) {
}

Bullet::Bullet(const Bullet& obj)
	:GameObject(obj), direction(obj.direction){
}

Bullet& Bullet::operator=(const Bullet& other) {
	if (this != &other) {
		GameObject::operator=(other);
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

void Bullet::Enemyshoot() {

		draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
		setY(getY() + getDirection());
		if (getY() >= 2 && getY() <= POLE_ROWS) {
			render();
		}
}

void Bullet::update() {
	draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
	setY(getY() + direction);

	if (getY() >= 2 && getY() <= POLE_ROWS) {
		render();
	}
}