#include "Fruits.hpp"

void Fruits::set(Texture& image, int x, int y)
{
    // ������������� ����� �������.
    fruit.setTexture(image);

    rect.left = x + 50; // ��������� ��������� ������ �� ��� X.
    rect.top = y; // ��������� ��������� ������ �� ��� Y.

    fruitNumber = rand() % 20; // ��������� ����� �� 0 �� 19, ������� ����� �������������� ��� ������ �������� ������.
    rotate = fruitLifeTime = 0; // ������������� ���������� ��� ���������� ��������� � �������� ����� ������.
    fallSpeed = 7; // ��������� �������� ������� ������. 
    changeTextureBool = true; // ������������� �����, ������� ����������, ������ �� ����� ������ �������� ��� �������.
}

void Fruits::update()
{
    if (fly == 1)
    {
        if (!putFruitOnGround)
            fallSpeed = fallSpeed + 0.005;

        rect.top += fallSpeed;

    }

    putFruitOnGround = false; // ������������� ����, ��� ����� ��������� �� �����.

    // ���� ����� ��������� ���� �����, �� ������������� ��� �� ����� � ������������� �������.
    if (rect.top > ground)
    {
        rect.top = ground;
        fallSpeed = 0;
        putFruitOnGround = true;

        if (fruitLifeTime == 0)
            fruitLifeTime = 1000;
    }

    // ��������� ����� ����� ������ �� 1.
    if (fruitLifeTime > 0)
    {
        fruitLifeTime--;
        if (fruitLifeTime == 0)
        {
            // ��������� ��������� ������ ��� ���������� �������.
            fallSpeed = -0, 7;
            fruitNumber = rand() % 7;
            changeTextureBool = true;
            startGame = true;
        }
    }

    // ���������, ������ �� ����� �������� �������� ��� �������.
    if (changeTextureBool && fruitNumber<6 && rect.top>ground - 1 && fallSpeed > 0)
    {
        prop++;

        // sound.error.play();
    }

    // ������������� ������ ��������� ������� � �������� � ����� ������.
    fruit.setOrigin(50, 50);
    choppedFruit.setOrigin(50, 50);

    // ������������� ���� �������� ������.
    fruit.setRotation(rotate);
    choppedFruit.setRotation(rotate);

    rotate += 0.25; // ����������� ���� �������� ������ �� 0.25 �������.

    // �������� �������� ������ � ����������� �� ��� ���������.
    if (changeTextureBool)
        fruit.setTextureRect(IntRect(100 * fruitNumber, 0, 100, 100)); // ���� ����� ������ �������� ��� �������, �������� ��������� ������ �������� �� 0 �� 100 ��������.
    else
        fruit.setTextureRect(IntRect(100 * fruitNumber, 0, 100, 60)); // ���� ����� �� ������ �������� ��� �������, �������� ������������� ������ �������� 60x60 ��������.

    // ������������� ��������� ������� � �������� �� ������.
    fruit.setPosition(rect.left, rect.top);
    choppedFruit.setTextureRect(IntRect(100 * fruitNumber, 0, 100, 60));
    choppedFruit.setPosition(rect.left + 50, rect.top);
}
