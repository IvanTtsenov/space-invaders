#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(int x, int y, char symbol, COLORS color, int direction, int updateCounter, int slowEnemySpeed);
	Enemy(const Enemy& obj);
	virtual ~Enemy();
	Enemy& operator=(const Enemy& other);
	void update() override;
	void render() override;
	int getDirection() const;
	void setDirection(int direction);
	int getUpdateCounter() const;
	void setUpdateCounter(int updateCounter = 0);
	int getSlowEnemySpeed() const;
	void setSlowEnemySpeed(int slowEnemySpeed, int level);
private:
	int direction;
	int updateCounter;
	int slowEnemySpeed;
};
