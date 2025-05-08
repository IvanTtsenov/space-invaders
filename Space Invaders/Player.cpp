#include "Player.h"
#include <iostream>
#include "Bullet.h"
#include "visualisation.h"
using namespace std;
Player::Player() {
};

Player::Player(const Player& obj) {
	this->lives = obj.lives;
	this->score = obj.score;
}

Player& Player::operator=(const Player& other) {
	if (this != &other) {
		lives = other.lives;
		score = other.score;
	}
	return *this;
}

Player Player::operator+(int points) const {
	Player temp = *this;
	temp.score += points;
	return temp;
}

Player Player::operator-(int points) const {
	Player temp = *this;
	temp.score -= points;
	return temp;
}

void Player::moveLeft() {
	if (getX() > 0) {
	// Check if not at the left edge
	setX(getX() - 1); // Move left
	}

}

void Player::moveRight() {
	if (getX() < POLE_COLS) { // Check if not at the right edge
		setX(getX() + 1); // Move right
	}
}

void Player::shoot() {
	Bullet b;
	b.render();
}

int Player::getLives() const {
	return lives;
}

int Player::getScore() const {
	return score;
}

void Player::setLives(int lives) {
	this->lives = lives;
}

void Player::setScore(int score) {
	this->score = score;
}

void Player::render() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BLACK);
	}