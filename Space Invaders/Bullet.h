#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(Bullet& obj);
	Bullet& operator=(const Bullet& other);

	void update();
	void render() override;

	int getDirection() const;
	void setDirection(int direction);

private:
	int direction;
};

