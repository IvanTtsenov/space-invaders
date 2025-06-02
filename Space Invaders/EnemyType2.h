#pragma once
#include "Enemy.h"
class EnemyType2 : public Enemy
{
public:
	EnemyType2();
	EnemyType2(int x, int y, char symbol, COLORS color, int direction);
	void update() override;
	void render() override;
};

