#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(int x, int y, char symbol, COLORS color, int direction);
	Bullet(Bullet& obj);
	Bullet& operator=(const Bullet& other);

	void update() override;
	void render() override;
	void Enemyshoot();

	int getDirection() const;
	void setDirection(int direction);

private:
	int direction;
};

