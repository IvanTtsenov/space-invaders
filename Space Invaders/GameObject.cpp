#include "GameObject.h"

GameObject::GameObject() {
};

GameObject::GameObject(int x, int y, char symbol, COLORS color)
	: x(x), y(y), symbol(symbol), color(color) {
}


GameObject::~GameObject() {
}

GameObject::GameObject(const GameObject& obj)
	: x(obj.x), y(obj.y), symbol(obj.symbol), color(obj.color) {

}

GameObject& GameObject::operator=(const GameObject& other) {
	if (this != &other) {
		x = other.x;
		y = other.y;
		symbol = other.symbol;
		color = other.color;
	}
	return *this;
}

void GameObject::setX(int x) {
	this->x = x;
}

int GameObject::getX() const {
	return x;
}

void GameObject::setY(int y) {
	this->y = y;
}

int GameObject::getY() const {
	return y;
}

void GameObject::setSymbol(char symbol) {
	 this->symbol = symbol;
}

char GameObject::getSymbol() const {
	return symbol;
}

void GameObject::update() {
}

void GameObject::setColor(COLORS color) {
	this->color = color;
}

COLORS GameObject::getColor() const {
	return color;
}

void GameObject::render() {
}