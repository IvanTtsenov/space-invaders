#include "EnemyType2.h"
EnemyType2::EnemyType2() {

}

EnemyType2::EnemyType2(int x, int y, char symbol, COLORS color, int direction)
	: Enemy(x, y, symbol, color, direction) {
}

void EnemyType2::update() {

	draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
	setY(getY() + getDirection());
	if (getY() <= POLE_ROWS) {
		render();
	}
};
void EnemyType2::render() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BACKGROUND_COLOR);
};