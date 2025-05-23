#include "Player.h"
using namespace std;
Player::Player() : GameObject(), lives(3), score(0) {
};

Player::~Player() {};

Player::Player(int x, int y, char symbol, COLORS color, int lives, int score)
	: GameObject(x, y, symbol, color), lives(lives), score(score) {
}

Player::Player(const Player& obj) 
	:GameObject(obj), lives(obj.lives), score(obj.score) {
}

Player& Player::operator=(const Player& other) {
	if (this != &other) {
		GameObject::operator=(other);
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
		draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);

		setX(getX() - 1);
	}
}

void Player::moveRight() {
	if (getX() < POLE_COLS) { 
		draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
		setX(getX() + 1);
	}
}

Bullet* Player::shoot() {
	Bullet* b = new Bullet(getX(),getY(),'^',RED,-1);
	return b;
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
	draw_char(getSymbol(), getY(), getX(), getColor(), BACKGROUND_COLOR);
}