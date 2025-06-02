#include "EnemyType3.h"
EnemyType3::EnemyType3() {

}

EnemyType3::EnemyType3(int x, int y, char symbol, COLORS color, int direction)
	: Enemy(x, y, symbol, color, direction) {
}

void EnemyType3::update() {

	draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
	setY(getY() + getDirection());
	if (getY() <= POLE_ROWS) {
		render();
	}
};
void EnemyType3::render() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BACKGROUND_COLOR);
};