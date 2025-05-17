#pragma once
#include "Player.h"
#include "GameObject.h"
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
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
	Game(const Game& obj);
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

private:
	Player player;
	vector<GameObject*> enemies;
	vector<GameObject*> bullets;
	int score;
	int level;
	int rows = 0;
	bool running;
};

