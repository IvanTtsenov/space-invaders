#pragma once
#include "Player.h"
#include "GameObject.h"
#include <vector>
#include "Enemy.h"
using namespace std;
class Game
{
public:
	Game();
	Game(Game& obj);

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
	Enemy enemy;
	Player player;
	vector<GameObject*> enemies;
	vector<GameObject*> bullets;
	int score;
	int level;
	bool running;
};

