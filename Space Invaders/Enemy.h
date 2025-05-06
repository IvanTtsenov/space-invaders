#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Enemy& obj);
	Enemy& operator=(const Enemy& other)
	{
		if (this != &other)
		{
			direction = other.direction;
		}
		return *this;
	}

	void update();
	void render();

private:
	int direction;

};

//Наследници: -EnemyType1, EnemyType2, EnemyType3, EnemyType4(различни визуализации)
