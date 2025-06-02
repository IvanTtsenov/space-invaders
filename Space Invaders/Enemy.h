#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(int x, int y, char symbol, COLORS color, int direction);
	Enemy(const Enemy& obj);
	virtual ~Enemy();
	Enemy& operator=(const Enemy& other);
	void update() override = 0;
	void render() override = 0;
	int getDirection() const;
	void setDirection(int direction);

private:
	int direction;
};
