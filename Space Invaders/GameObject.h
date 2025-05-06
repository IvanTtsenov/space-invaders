#pragma once
#include <string>
#include "visualisation.h"
using namespace std;
class GameObject
{
public:
    GameObject();
    GameObject(GameObject& obj);
    GameObject& operator=(const GameObject& other);

    virtual void update();
    virtual void render();
    int getX() const;
    int getY() const;
    char getSymbol() const;
	COLORS getColor() const;

    void setX(int x);
    void setY(int y);
    void setSymbol(char symbol);
	void setColor(COLORS color);
private:
    int x;
    int y;
    char symbol;
    COLORS color;
};

