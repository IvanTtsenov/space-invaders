#pragma once
#include "Enemy.h"
class EnemyType1 : public Enemy 
{
public:
	EnemyType1();
	EnemyType1(int x, int y, char symbol, COLORS color, int direction, int updateCounter, int slowEnemySpeed);
};

