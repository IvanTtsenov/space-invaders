#pragma once
class Player
{
public:
	Player();
	Player(Player& obj);
	Player& operator=(const Player& other)
	{
		if (this != &other)
		{
			lives = other.lives;
			score = other.score;
		}
		return *this;
	}

	Player operator+(int points) const;
	Player operator-(int points) const;

	void moveLeft();
	void moveRight();
	void shoot();

	int getLives() const;
	int getScore() const;

	void setLives(int lives);
	void setScore(int score);
private:
	int lives;
	int score;

};

