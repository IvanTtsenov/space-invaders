#pragma once
#include "Enemy.h"
class EnemyType3 : public Enemy
{
public:
	EnemyType3();
	EnemyType3(int x, int y, char symbol, COLORS color, int direction);
	void update() override;
	void render() override;
};

