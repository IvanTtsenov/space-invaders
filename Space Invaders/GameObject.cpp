#include "GameObject.h"
#include <iostream>

GameObject::GameObject() {

};

GameObject::~GameObject() {
}

GameObject::GameObject(GameObject& obj) {
	this->x = obj.x;
	this->y = obj.y;
	this->symbol = obj.symbol;
	this->color = obj.color;
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
	// Update logic for GameObject
}

void GameObject::setColor(COLORS color) {
	this->color = color;
}

COLORS GameObject::getColor() const {
	return color;
}

void GameObject::render() {
}