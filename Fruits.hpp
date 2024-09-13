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

    // Метод set, который устанавливает начальные параметры фрукта.
    void set(Texture& image, int x, int y);

    // Метод update, который обновляет состояние фрукта на экране.
    void update();
};

#endif // !FRUITS_HPP

