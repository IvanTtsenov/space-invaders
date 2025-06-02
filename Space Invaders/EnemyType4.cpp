#include "EnemyType4.h"
EnemyType4::EnemyType4() {

}

EnemyType4::EnemyType4(int x, int y, char symbol, COLORS color, int direction)
	: Enemy(x, y, symbol, color, direction) {
}

void EnemyType4::update() {

	draw_char(' ', getY(), getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
	setY(getY() + getDirection());
	if (getY() <= POLE_ROWS) {
		render();
	}
};
void EnemyType4::render() {
	draw_char(getSymbol(), getY(), getX(), getColor(), BACKGROUND_COLOR);
};