#pragma once
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <set>
#include "Player.h"
#include "GameObject.h"
#include "visualisation.h"
#include "Bullet.h"
#include "EnemyType1.h"
#include "EnemyType2.h"
#include "EnemyType3.h"
#include "EnemyType4.h"

using namespace std;
class Game
{
public:
	Game();
	~Game();

	void initializeEnemies();
	void input();
	void update();
	void checkCollisions();
	void render();
	void run();

	void setRunning(bool running);
	bool isRunning() const;
	void setScore(int score);
	int getScore() const;
	void setLevel(int level);
	int getLevel() const;

	void resetGame();
	void renderMenu();
	void updateEnemySpeed();

private:
	Player player;
	vector<GameObject*> enemies;
	vector<GameObject*> bullets;
	vector<GameObject*> enemyBul;
	int score;
	int level;
	int rows = 0;
	bool running;
	bool addedLive;
	bool winCondition;
	bool enemiesReachedEnd;
	int enemyMoveTimer = 0;
	int enemyBulletTimer = 0;
	int shootTimer = 0;
	int currentEnemySpeed = 100;
	int currentEnemyBulletSpeed = 30;
	int shootChance = 10;
};

