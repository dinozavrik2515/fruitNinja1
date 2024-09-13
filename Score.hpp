#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;

class Score
{
public:

    Sprite sec[3];
    int s[3], c;
    bool vid[3];

    // Конструктор, который принимает текстуру для отображения цифр счёта.
    Score(Texture* image)
    {
        // Инициализация полей объекта.
        for (int i = 0; i < 3; i++)
        {
            sec[i].setTexture(*image); // Установка текстуры для каждого спрайта.
            sec[i].setPosition(100 + 22 * i, 25); // Установка начального положения спрайтов.
            sec[i].setTextureRect(IntRect(0, 0, 22, 45)); // Установка начальных значений для текстуры спрайтов.

            // Инициализация счётчиков для каждой цифры.
            s[i] = 0;
            c = 0;
        }
    }

    // Метод update, который обновляет отображение цифр счёта в зависимости от текущего значения счёта.
    void update()
    {
        if (c < 10) // Если значение счёта меньше 10, отображаем только первую цифру.
        {
            s[0] = c;

            vid[0] = true;
            vid[1] = false;
            vid[2] = false;
        }
        else if (c >= 10 && c < 100) // Если значение счёта от 10 до 99, отображаем две цифры.
        {
            s[0] = c / 10;
            s[1] = c % 10;

            vid[0] = true;
            vid[1] = true;
            vid[2] = false;
        }
        else if (c >= 100 && c < 1000) // Если значение счёта от 100 до 999, отображаем три цифры.
        {
            s[0] = c / 100;
            s[1] = (c / 10) % 10;
            s[2] = (c % 100) % 10;

            vid[0] = true;
            vid[1] = true;
            vid[2] = false;
        }

        // Обновляем отображение цифр на экране.
        for (int i = 0; i < 3; i++)
            sec[i].setTextureRect(IntRect(22 * s[i], 0, 22, 45));
    }
};

#endif // !SCORE_HPP


