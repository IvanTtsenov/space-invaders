#include "Game.h"

Game::Game() 
	: player(POLE_COLS / 2, POLE_ROWS, 'A', GREEN, 3, 0), score(0), level(1), running(true), rows(0), addedLive(true), enemyMoveTimer(0),
	  currentEnemySpeed(100), currentEnemyBulletSpeed(30), enemyBulletTimer(0), winCondition(false), enemiesReachedEnd(false), shootTimer(0),
	  shootChance(10){
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

	set<int> uniqueX;

	for (int i = 0; i < POLE_COLS - (rand() % 15 + 1) ; i++) {
		Enemy* newEnemy = nullptr;

		int x;

		do {
			x = rand() % POLE_COLS + 1;
			//find връща uniqueX.end() ако не го намери
		} while (uniqueX.find(x) != uniqueX.end());

		uniqueX.insert(x);

			if (i % 2 == 0) {
				newEnemy = new EnemyType1(x, 2, '#', YELLOW, 1);
			}
			else if (i % 3 == 0) {
				newEnemy = new EnemyType2(x, 2, '&', BLUE, 1);
			}
			else if (i % 5 == 0) {
				newEnemy = new EnemyType3(x, 2, '$', PINK, 1);
			}
			else {
				newEnemy = new EnemyType4(x, 2, '@', RED, 1);
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
		}
	}
}

void Game::updateEnemySpeed() {
	if (score >= 500) {
		level = 3;
		currentEnemySpeed = 75;
		currentEnemyBulletSpeed = 50;
		shootChance = 50;
	}
	else if (score >= 200) {
		level = 2;
		currentEnemySpeed = 90;
		currentEnemyBulletSpeed = 60;
		shootChance = 30;
	}
	else {
		level = 1;
		currentEnemySpeed = 100;
		currentEnemyBulletSpeed = 70;
		shootChance = 10;
	}
}

void Game::update() {
	updateEnemySpeed();
	enemyMoveTimer++;
	enemyBulletTimer++;
	enemiesReachedEnd = false;
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
					return;
			}

			if (e->getY() > POLE_ROWS) {
				enemiesReachedEnd = true;
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

		shootTimer++;

		if (shootTimer > 30) {
			shootTimer = 0;

			for (auto e : enemies) {
				if (enemyBul.size() < 8) {
					bool canShoot = true;
					for (auto frontEnemies : enemies) {
						if (frontEnemies == e) continue;

						if (frontEnemies->getX() == e->getX() && frontEnemies->getY() > e->getY()) {
							canShoot = false;
							break;
						}
					}

					bool bulletExistsInColumn = false;
					for (auto existingBullet : enemyBul) {
						if (existingBullet->getX() == e->getX()) {
							bulletExistsInColumn = true;
							break;
						}
					}

					if (canShoot && rand() % 100 < shootChance && !bulletExistsInColumn) {
						Bullet* b = new Bullet(e->getX(), e->getY() + 2, '|', BLUE, 1);
						enemyBul.push_back(b);
					}
				}
			}
		}

		for (auto it = enemyBul.begin(); it != enemyBul.end();) {
			auto b = *it;

			if (enemyBulletTimer >= currentEnemyBulletSpeed) {
				b->Enemyshoot();
			}

			if (b->getX() == player.getX() && b->getY() == player.getY()) {
					player.setLives(player.getLives() - 1);

					draw_char(' ', b->getY(), b->getX(), BACKGROUND_COLOR, BACKGROUND_COLOR);
					delete b;
					it = enemyBul.erase(it);

				if (player.getLives() != 0) {
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
			if (enemies.empty() && level == 3 && enemiesReachedEnd == false && rows != 0) {
				winCondition = true;
				setRunning(false);
				return;
			}

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
	cout << "\033[" << 1 << ";1H";
	cout << "\033[2K";
	//cout << "Level: " << getLevel() << string(max(0,(POLE_COLS - 36) / 2), ' ') << "Score: " << getScore() << "     " << "Lives: " << player.getLives() << endl;
	cout << left << setw(10) << ("Level: " + to_string(getLevel()))
		<< setw(11) << ("Score: " + to_string(getScore()))
		<< right << setw(10) << ("Lives: " + to_string(player.getLives()))
		<< endl;
	cout << string(POLE_COLS + 1, '-') << endl;
}

void Game::render() {
	player.render();

	for (int x = 0; x <= POLE_COLS; x++) {
		draw_char('-', POLE_ROWS + 1, x, WHITE, BACKGROUND_COLOR);
	}

	for (int y = 2; y <= POLE_ROWS; y++) {
		draw_char('|', y, POLE_COLS + 1, WHITE, BACKGROUND_COLOR);
	}
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
	
	enemyMoveTimer = 0;
	enemyBulletTimer = 0;
	shootTimer = 0;
	rows = 0;
	winCondition = false;
	enemiesReachedEnd = false;
	currentEnemySpeed = 100;
	currentEnemyBulletSpeed = 30;
	shootChance = 10;
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
	if (player.getLives() == 0 || winCondition) {
		if (winCondition) {
			cout << "Congratulations! You have won! Final Score: " << getScore() << endl;
			return;
		}
		else {
			cout << "Game Over! Final Score: " << getScore() << endl;
			cout << "Press R to restart or Q to quit." << endl;
		}

		while (true) {
			if (_kbhit()) {
				int key = _getch();
				if (key == 'r' || key == 'R') {
					resetGame();
					run();
					return;
				}
				else if (key == 'q' || key == 'Q') {
					return;
				}
			}
		}
	}
	else {
		resetGame();
		run();

	}
}
