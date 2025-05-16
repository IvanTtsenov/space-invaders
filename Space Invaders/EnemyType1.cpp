#include "EnemyType1.h"

EnemyType1::EnemyType1(){}

EnemyType1::EnemyType1(int x, int y, char symbol, COLORS color, int direction, int updateCounter, int slowEnemySpeed)
	: Enemy(x, y, symbol, color, direction, updateCounter, slowEnemySpeed) {
}