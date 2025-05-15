#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Enemy& obj);
	Enemy& operator=(const Enemy& other);
	Enemy* createEnemies();
	void update();
	void render();
	int getDirection() const;
	void setDirection(int direction);
	int getUpdateCounter() const;
	void setUpdateCounter(int updateCounter = 0);
	int getSlowEnemySpeed() const;
	void setSlowEnemySpeed(int slowEnemySpeed, int level);
private:
	int direction;
	int updateCounter = 0;
	int slowEnemySpeed = 100;
};

//Наследници: -EnemyType1, EnemyType2, EnemyType3, EnemyType4(различни визуализации)
