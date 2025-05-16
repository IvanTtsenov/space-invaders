#include "EnemyType4.h"
EnemyType4::EnemyType4() {

}

EnemyType4::EnemyType4(int x, int y, char symbol, COLORS color, int direction, int updateCounter, int slowEnemySpeed)
	: Enemy(x, y, symbol, color, direction, updateCounter, slowEnemySpeed) {
}