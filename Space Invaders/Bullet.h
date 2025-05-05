#pragma once
class Bullet
{
public:
	Bullet();
	Bullet(Bullet& obj);
	Bullet& operator=(const Bullet& other)
	{
		if (this != &other)
		{
			direction = other.direction;
		}
		return *this;
	}

	void update();
	void render();

private:
	int direction;
};

