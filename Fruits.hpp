#ifndef FRUITS_HPP
#define FRUITS_HPP
#include "Score.hpp"

using namespace sf;

class Fruits
{
public:

    Sprite fruit, choppedFruit;
    int fruitNumber, fruitLifeTime, fly;
    float fallSpeed, rotate;
    FloatRect rect;
    bool putFruitOnGround, changeTextureBool;

    // ����� set, ������� ������������� ��������� ��������� ������.
    void set(Texture& image, int x, int y);

    // ����� update, ������� ��������� ��������� ������ �� ������.
    void update();
};

#endif // !FRUITS_HPP

