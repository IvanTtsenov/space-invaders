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

private:
	int direction;

};

//Наследници: -EnemyType1, EnemyType2, EnemyType3, EnemyType4(различни визуализации)
