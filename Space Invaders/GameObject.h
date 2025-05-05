#pragma once
#include <string>
#include "visualisation.cpp"
using namespace std;
class GameObject
{
public:
    GameObject();
    GameObject(GameObject& obj);
    GameObject& operator=(const GameObject& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            symbol = other.symbol;
            color = other.color;
        }
        return *this;
    }

    virtual void update();
    virtual void render();
    int getX() const;
    int getY() const;
    char getSymbol() const;

    void setX(int x);
    void setY(int y);
    void setSymbol(char symbol);

private:
    int x;
    int y;
    char symbol;
    COLORS color;
};

