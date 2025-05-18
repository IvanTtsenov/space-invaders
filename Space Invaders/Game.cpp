#include "Game.h"

Game::Game(): player(POLE_COLS / 2, POLE_ROWS, 'A', GREEN, 3, 0), score(0), level(1), running(true){
}

Game::~Game() {
	for (auto b : bullets) delete b;
	bullets.clear();
	for (auto e : enemies) delete e;
	enemies.clear();

}

Game::Game(const Game& obj) {
	this->player = obj.player;
	this->enemies = obj.enemies;
	this->bullets = obj.bullets;
	this->score = obj.score;
	this->level = obj.level;
	this->running = obj.running;
}

void Game::setRunning(bool running) {
	this->running = running;
}

bool Game::isRunning() const {
	return running;
}

void Game::setScore(int score) {
	this->score = score;
}

int Game::getScore() const {
	return score;
}

void Game::setLevel(int level) {
	this->level = level;
}

int Game::getLevel() const {
	return level;
}

void Game::initializeEnemies() {

	for (int i = 0; i < POLE_COLS; i++) {
		Enemy* newEnemy = nullptr;
			if (i % 2 == 0) {
				newEnemy = new EnemyType1(rand() % POLE_COLS + 1, 2, '#', YELLOW, 1, 0, 100);
			}
			else if (i % 3 == 0) {
				newEnemy = new EnemyType2(rand() % POLE_COLS + 1, 2, '&', BLUE, 1, 0, 100);
			}
			else if (i % 5 == 0) {
				newEnemy = new EnemyType3(rand() % POLE_COLS + 1, 2, '$', PINK, 1, 0, 100);
			}
			else {
				newEnemy = new EnemyType4(rand() % POLE_COLS + 1, 2, '@', RED, 1, 0, 100);
			}
			enemies.push_back(newEnemy);
			newEnemy->render();
	}
}


void Game::input() {
		if (_kbhit()) {
			int key = _getch();
			if (key == 'a' || key == 'A') {
				player.moveLeft();
			}
			else if (key == 'd' || key == 'D') {
				player.moveRight();
			}
			else if (key == ' ' || key == 'w' || key == 'W') {
				bullets.push_back(player.shoot());
			}
			if (key == 224) { 
				key = _getch();
				if (key == 75) {
					player.moveLeft();
				}
				else if (key == 77) {
					player.moveRight();
				}
				else if (key == 72) {
					bullets.push_back(player.shoot());

			}
			draw_char(player.getSymbol(), player.getY(), player.getX(), player.getColor(), BACKGROUND_COLOR);
		}
	}
}

void Game::update() {

	if (score >= 500) {
		setLevel(3);
		for (auto e : enemies) {
			Enemy* enemy = dynamic_cast<Enemy*>(e);
			if (enemy) {
				enemy->setSlowEnemySpeed(100, level);
			}
		}
	}
	else if (score >= 200 && score < 500) {
		setLevel(2);
		for (auto e : enemies) {
			Enemy* enemy = dynamic_cast<Enemy*>(e);
			if (enemy) {
				enemy->setSlowEnemySpeed(100, level);
			}
		}
	}

	for (auto it = bullets.begin(); it != bullets.end(); ) {
		auto b = *it;
		b->update();
		if (b->getY() < 2) {
			delete b;
			it = bullets.erase(it);
		}
		else {
			++it; 
		}
	}

	bool newRow = false;
		for (auto it = enemies.begin(); it != enemies.end(); ) {
			auto e = *it;
			int oldY = e->getY();
			e->update();

			if (e->getY() != oldY) {
				newRow = true;
			}
			if (e->getX() == player.getX() && e->getY() == player.getY()) {
				if (player.getLives() != 0) {
					player.setLives(player.getLives() - 1);
					setRunning(false);
					break;
				}
				else {
					setRunning(false);
					break;
				}
			}

			if (e->getY() > 29) {
				delete e;
				it = enemies.erase(it);
			}
			else {
				++it;
			}
		}

		if (newRow && rows < 4) {
			initializeEnemies();
			rows++;
		}
	}

void Game::checkCollisions() {
	for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
		auto b = *bulletIt;
		bool bulletDeleted = false;

		for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
			auto e = *enemyIt;

			if (b->getX() == e->getX() && b->getY() == e->getY()) {

				if (typeid(*e).name() == typeid(EnemyType1).name()) {
					score += 10;
				}
				else if (typeid(*e).name() == typeid(EnemyType2).name()) {
					score += 20;
				}
				else if (typeid(*e).name() == typeid(EnemyType3).name()) {
					score += 30;
				}
				else if (typeid(*e).name() == typeid(EnemyType4).name()) {
					score += 40;
				}
				setScore(score);
				delete e;
				enemyIt = enemies.erase(enemyIt);
				delete b;
				bulletIt = bullets.erase(bulletIt);
				bulletDeleted = true;
				break;  // Bullet is gone, move to next bullet
			}
			else {
				++enemyIt;
			}
		}

		if (!bulletDeleted) {
			++bulletIt;
		}
	}
}

void Game::renderMenu() {
	std::cout << "\033[" << 1 << ";1H";
	std::cout << "\033[2K";
	cout << "Level: " << getLevel() << string((118 - 36) / 2, ' ') << "Score: " << getScore() << "     " << "Lives: " << player.getLives() << endl;
	cout << string(118, '-') << endl;
}

void Game::render() {
	player.render();
}

void Game::resetGame() {
	for (auto b : bullets) delete b;
	bullets.clear();
	for (auto e : enemies) delete e;
	enemies.clear();

	player = Player(POLE_COLS / 2, POLE_ROWS, 'A', GREEN, player.getLives(), getScore());
	score = getScore();
	level = getLevel();
	rows = 0;
	running = true;
	renderMenu();
}

void Game::run()
{
	int newScore = score;
	int newLevel = level;
	int newLives = player.getLives();
	renderMenu();
	initializeEnemies();

	while (isRunning())
	{
		input();
		render();
		update();
		checkCollisions();
		if (newScore != score || newLevel != level || newLives != player.getLives()) {
			newScore = score;
			newLevel = level;
			newLives = player.getLives();
			renderMenu();
		}
		Sleep(10);
	}

	system("cls");
	if (player.getLives() <= 0) {
		// Game over
		cout << "Game Over! Final Score: " << player.getScore() << endl;
		cout << "Press R to restart or Q to quit." << endl;
		while (true) {
			if (_kbhit()) {
				int key = _getch();
				if (key == 'r' || key == 'R') {
					resetGame();
					run(); // Restart the game
					break;
				}
				else if (key == 'q' || key == 'Q') {
					break; // Exit the game
				}
			}
		}
	}
	else {
		resetGame();
		run();
	}
}