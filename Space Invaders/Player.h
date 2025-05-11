#pragma once
#include "GameObject.h"
#include "Bullet.h"
class Player : public GameObject
{
public:
	Player();
	Player(const Player& obj);
	Player& operator=(const Player& other);

	Player operator+(int points) const;
	Player operator-(int points) const;

	void moveLeft();
	void moveRight();
	Bullet* shoot();

	int getLives() const;
	int getScore() const;

	void setLives(int lives);
	void setScore(int score);
	void render() override;
private:
	int lives;
	int score;

};

