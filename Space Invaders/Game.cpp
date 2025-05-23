#include "Game.h"

Game::Game() 
	: player(POLE_COLS / 2, POLE_ROWS, 'A', GREEN, 3, 0), score(0), level(1), running(true), rows(0), addedLive(true), enemyMoveTimer(0),
	  currentEnemySpeed(100), currentEnemyBulletSpeed(30), enemyBulletTimer(0){
}

Game::~Game() {
	for (auto b : bullets) delete b;
	bullets.clear();
	for (auto e : enemies) delete e;
	enemies.clear();
	for (auto eBul : enemyBul) delete eBul;
	enemyBul.clear();
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
				newEnemy = new EnemyType1(rand() % POLE_COLS + 1, 2, '#', YELLOW, 1);
			}
			else if (i % 3 == 0) {
				newEnemy = new EnemyType2(rand() % POLE_COLS + 1, 2, '&', BLUE, 1);
			}
			else if (i % 5 == 0) {
				newEnemy = new EnemyType3(rand() % POLE_COLS + 1, 2, '$', PINK, 1);
			}
			else {
				newEnemy = new EnemyType4(rand() % POLE_COLS + 1, 2, '@', RED, 1);
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
			//draw_char(player.getSymbol(), player.getY(), player.getX(), player.getColor(), BACKGROUND_COLOR);
		}
	}
}

void Game::updateEnemySpeed() {
	if (score >= 500) {
		level = 3;
		currentEnemySpeed = 50;
		currentEnemyBulletSpeed = 10;
	}
	else if (score >= 200) {
		level = 2;
		currentEnemySpeed = 75;
		currentEnemyBulletSpeed = 20;
	}
	else {
		level = 1;
		currentEnemySpeed = 100;
		currentEnemyBulletSpeed = 30;
	}
}

void Game::update() {
	updateEnemySpeed();
	enemyMoveTimer++;
	enemyBulletTimer++;

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
			if(enemyMoveTimer >= currentEnemySpeed){
				e->update();
			}

			if (e->getY() != oldY) {
				newRow = true;
			}
			if (e->getX() == player.getX() && e->getY() == player.getY()) {
					player.setLives(player.getLives() - 1);
					setRunning(false);
					break;
			}

			if (e->getY() > POLE_ROWS) {
				delete e;
				it = enemies.erase(it);
			}
			else {
				++it;
			}
		}

		if (enemyMoveTimer >= currentEnemySpeed) {
			enemyMoveTimer = 0;
		}

		static int shootTimer = 0;
		shootTimer++;

		if (shootTimer > 30) {
			shootTimer = 0;

			for (auto e : enemies) {
				if (enemyBul.size() < 8) {
					bool canShoot = true;
					for (auto other : enemies) {
						if (other == e) continue;

						// Same X (column) and is below the current enemy
						if (other->getX() == e->getX() && other->getY() > e->getY()) {
							canShoot = false;
							break;
						}
					}

				// 10% chance this enemy shoots a bullet
					if (canShoot && rand() % 100 < 10) {
						Bullet* b = new Bullet(e->getX(), e->getY() + 1, '|', BLUE, 1);
						enemyBul.push_back(b);
					}
				}
			}
		}

		for (auto it = enemyBul.begin(); it != enemyBul.end();) {
			Bullet* b = dynamic_cast<Bullet*>(*it);

			if (enemyBulletTimer >= currentEnemyBulletSpeed) {
				b->Enemyshoot();
			}

			if (b->getX() == player.getX() && b->getY() == player.getY()) {
					player.setLives(player.getLives() - 1);
				if (player.getLives() != 0) {
					draw_char(' ', b->getY(), b->getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
					delete b;
					it = enemyBul.erase(it);
					player.setX(POLE_COLS / 2);
					player.setY(POLE_ROWS);
					break;
				}
				else {
					setRunning(false);
					break;
				}
			}

			if (b->getY() > POLE_ROWS) {
				draw_char(' ', b->getY(), b->getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
				delete b;
				it = enemyBul.erase(it);
			}
			else {
				++it;
			}
		}

		if (enemyBulletTimer >= currentEnemyBulletSpeed) {
			enemyBulletTimer = 0;
		}

		if (newRow && rows < 5 || enemies.empty()) {
			if (enemies.empty()) {
				rows = 0;
			}
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
				draw_char(' ', e->getY(), e->getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
				delete e;
				enemyIt = enemies.erase(enemyIt);
				draw_char(' ', b->getY(), b->getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
				delete b;
				bulletIt = bullets.erase(bulletIt);
				bulletDeleted = true;
				break;
			}
			else {
				++enemyIt;
			}
		}

		if (!bulletDeleted) {
			for (auto enemyBulletIt = enemyBul.begin(); enemyBulletIt != enemyBul.end(); ) {
				auto eb = *enemyBulletIt;

				if (b->getX() == eb->getX() && b->getY() == eb->getY()) {
					draw_char(' ', b->getY(), b->getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
					delete b;
					bulletIt = bullets.erase(bulletIt);
					bulletDeleted = true;

					draw_char(' ', eb->getY(), eb->getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
					delete eb;
					enemyBulletIt = enemyBul.erase(enemyBulletIt);
					break;
				}
				else {
					++enemyBulletIt;
				}
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
	for (auto eBul : enemyBul) delete eBul;
	enemyBul.clear();

	player = Player(POLE_COLS / 2, POLE_ROWS, 'A', GREEN, player.getLives(), getScore());
	if (player.getLives() != 0) {
		score = getScore();
		level = getLevel();
	}
	else {
		score = 0;
		level = 1;
		player.setLives(3);
		addedLive = true;
	}
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

	while (isRunning())
	{
		input();
		checkCollisions();
		update();
		render();
		if (newScore != score || newLevel != level || newLives != player.getLives()) {
			if (score >= 300 && addedLive) {
				player.setLives(player.getLives() + 1);
				addedLive = false;
			}
			newScore = score;
			newLevel = level;
			newLives = player.getLives();
			renderMenu();
		}
		Sleep(10);
	}

	system("cls");
	if (player.getLives() == 0) {
		cout << "Game Over! Final Score: " << getScore() << endl;
		cout << "Press R to restart or Q to quit." << endl;
		while (true) {
			if (_kbhit()) {
				int key = _getch();
				if (key == 'r' || key == 'R') {
					resetGame();
					run();
					break;
				}
				else if (key == 'q' || key == 'Q') {
					break;
				}
			}
		}
	}
	else {
		resetGame();
		run();
	}
}