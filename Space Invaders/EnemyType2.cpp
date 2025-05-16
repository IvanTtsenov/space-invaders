#include "EnemyType2.h"
EnemyType2::EnemyType2() {

}

//EnemyType2::EnemyType2(int x, int y, int direction, int updateCounter, int slowEnemySpeed)
//	: Enemy(x, y, '&',CYAN, direction, updateCounter, slowEnemySpeed) {
//
//}

EnemyType2::EnemyType2(int x, int y, char symbol, COLORS color, int direction, int updateCounter, int slowEnemySpeed)
	: Enemy(x, y, symbol, color, direction, updateCounter, slowEnemySpeed) {
}