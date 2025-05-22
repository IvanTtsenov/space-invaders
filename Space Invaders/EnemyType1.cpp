#include "EnemyType1.h"

EnemyType1::EnemyType1(){}

EnemyType1::EnemyType1(int x, int y, char symbol, COLORS color, int direction)
	: Enemy(x, y, symbol, color, direction) {
}