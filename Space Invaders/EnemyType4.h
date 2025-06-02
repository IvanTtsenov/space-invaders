#pragma once
#include "Enemy.h"
class EnemyType4 : public Enemy
{
public:
	EnemyType4();
	EnemyType4(int x, int y, char symbol, COLORS color, int direction);
	void update() override;
	void render() override;
};

