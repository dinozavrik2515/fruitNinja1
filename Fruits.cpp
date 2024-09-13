#include "Fruits.hpp"

void Fruits::set(Texture& image, int x, int y)
{
    // Инициализация полей объекта.
    fruit.setTexture(image);

    rect.left = x + 50; // Начальное положение фрукта по оси X.
    rect.top = y; // Начальное положение фрукта по оси Y.

    fruitNumber = rand() % 20; // Случайное число от 0 до 19, которое будет использоваться для выбора текстуры фрукта.
    rotate = fruitLifeTime = 0; // Инициализация переменных для управления вращением и временем жизни фрукта.
    fallSpeed = 7; // Начальная скорость падения фрукта. 
    changeTextureBool = true; // Инициализация флага, который определяет, должен ли фрукт менять текстуру при падении.
}

void Fruits::update()
{
    if (fly == 1)
    {
        if (!putFruitOnGround)
            fallSpeed = fallSpeed + 0.005;

        rect.top += fallSpeed;

    }

    putFruitOnGround = false; // Устанавливаем флаг, что фрукт находится на земле.

    // Если фрукт находится выше земли, то устанавливаем его на землю и останавливаем падение.
    if (rect.top > ground)
    {
        rect.top = ground;
        fallSpeed = 0;
        putFruitOnGround = true;

        if (fruitLifeTime == 0)
            fruitLifeTime = 1000;
    }

    // Уменьшаем время жизни фрукта на 1.
    if (fruitLifeTime > 0)
    {
        fruitLifeTime--;
        if (fruitLifeTime == 0)
        {
            // Обновляем параметры фрукта для следующего падения.
            fallSpeed = -0, 7;
            fruitNumber = rand() % 7;
            changeTextureBool = true;
            startGame = true;
        }
    }

    // Проверяем, должен ли фрукт изменить текстуру при падении.
    if (changeTextureBool && fruitNumber<6 && rect.top>ground - 1 && fallSpeed > 0)
    {
        prop++;

        // sound.error.play();
    }

    // Устанавливаем начало координат спрайта и текстуры в центр фрукта.
    fruit.setOrigin(50, 50);
    choppedFruit.setOrigin(50, 50);

    // Устанавливаем угол поворота фрукта.
    fruit.setRotation(rotate);
    choppedFruit.setRotation(rotate);

    rotate += 0.25; // Увеличиваем угол поворота фрукта на 0.25 радиана.

    // Выбираем текстуру фрукта в зависимости от его состояния.
    if (changeTextureBool)
        fruit.setTextureRect(IntRect(100 * fruitNumber, 0, 100, 100)); // Если фрукт меняет текстуру при падении, выбираем случайный размер текстуры от 0 до 100 пикселей.
    else
        fruit.setTextureRect(IntRect(100 * fruitNumber, 0, 100, 60)); // Если фрукт не меняет текстуру при падении, выбираем фиксированный размер текстуры 60x60 пикселей.

    // Устанавливаем положение спрайта и текстуры на экране.
    fruit.setPosition(rect.left, rect.top);
    choppedFruit.setTextureRect(IntRect(100 * fruitNumber, 0, 100, 60));
    choppedFruit.setPosition(rect.left + 50, rect.top);
}
