#include "EnemyType3.h"
EnemyType3::EnemyType3() {

}

EnemyType3::EnemyType3(int x, int y, char symbol, COLORS color, int direction, int updateCounter, int slowEnemySpeed)
	: Enemy(x, y, symbol, color, direction, updateCounter, slowEnemySpeed) {
}