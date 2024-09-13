#include "Fruits.hpp"

using namespace sf;
const int W = 296;
const int H = 167;

//class SetSound
//{
//public:
//    // Объявление буферов и звуков
//    SoundBuffer b, e, g, n, r, u;
//    Sound boom, error, gameover, nature, choppedFruit, up;
//    bool ops, bomba;
//
//    SetSound()
//    {
//        // Инициализация буферов
//        b.loadFromFile();
//        e.loadFromFile();
//        g.loadFromFile();
//        n.loadFromFile();
//        r.loadFromFile();
//        u.loadFromFile();
//
//        // Установка буферов для звуков
//        boom.setBuffer(b);
//        error.setBuffer(e);
//        gameover.setBuffer(g);
//        nature.setBuffer(n);
//        choppedFruit.setBuffer(r);
//        up.setBuffer(u);
//
//        nature.setLoop(true); // Установка цикла для звука nature
//
//        ops = bomba = false; // Инициализация флагов
//    }
//};
//SetSound sound;




// Запускает программу и создаёт окно игры.
int main()
{

    int ground = 600;
    bool startGame = true;
    int prop = 0;

    srand(time(0)); // Инициализация генератора случайных чисел текущим временем.
    RenderWindow window(VideoMode(888, 501), "Fruit Ninja"); // Создание окна игры.

    Texture f;
    f.loadFromFile("images\\fon3.png");
    Sprite fon(f); // Создание спрайта из загруженной текстуры.

    // Создание круга с радиусом 3 пикселя и белым цветом заливки.
    CircleShape strel;
    strel.setRadius(3.f);
    strel.setFillColor(Color::White);

    // Объявление двумерных массивов для хранения информации о видимости кругов и времени их видимости.
    bool vid[W][H];
    int time[W][H];
    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
        {
            vid[i][j] = false;
            time[i][j] = 0;
        }

    Texture f2;  // Загрузка текстуры фруктов из файла.
    f2.loadFromFile("fruits.png");

    // Создание массива из 21 объекта класса Fruits, каждый из которых инициализируется текстурой фруктов и начальным положением на экране.
    Fruits fruit[21];
    for (int i = 0; i < 21; i++)
        fruit[i].set(f2, 110 * i, ground);

    int pusk = 100; // Объявление переменной для количества пуль.

    // Создание спрайта для отображения счёта с использованием текстуры фруктов.
    Sprite ArbScore(f2);
    ArbScore.setTextureRect(IntRect(200, 160, 100, 60));
    ArbScore.setScale(0.8, 0.8);
    ArbScore.setPosition(0, 60);
    ArbScore.setRotation(315);

    // Загрузка текстуры для отображения счёта.
    Texture scoreTexture;
    scoreTexture.loadFromFile("watermelon.png");
    Score score(&scoreTexture); // Создание объекта класса Score для отображения счёта.

    Texture crossTexture;
    crossTexture.loadFromFile("cross.png"); // Загрузка текстуры для крестиков и создание массива из трёх спрайтов.
    Sprite cross[3];
    for (int i = 0; i < 3; i++)
    {
        cross[i].setTexture(crossTexture);
        cross[i].setTextureRect(IntRect(0, 0, 50, 50));
        cross[i].setPosition(650 + 75 * i, 25);
    }

    Texture youLoseTexture; // Загрузка текстуры для отображения проигрыша.
    youLoseTexture.loadFromFile("fon2");
    Sprite youLose;
    youLose.setPosition(300, 200);
    bool lose = false;  // Объявление переменной для отслеживания проигрыша.

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window); // Получаем текущую позицию мыши

    // Обрабатываем события окна
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close(); // Закрываем окно, если пользователь нажал на кнопку закрытия
        }
    }

    // Проходим по сетке и обновляем состояние каждой ячейки
    for (int i = 0; i < W; i++)
        for (int j = 0; j < W; j++)
        {
            // Проверяем, находится ли мышь над текущей ячейкой
            if (pos.x >= i * 6 && pos.x <= (i + 1) * 6 &&
                pos.y >= j * 6 && pos.y <= (j + 1) * 6)
            {
                // Делаем ячейку видимой и запускаем таймер
                vid[i][j] = true;
                time[i][j] = 100;
            }

            // Уменьшаем таймер для текущей ячейки
            if (time[i][j] > 0)
            {
                time[i][j]--;
                if (time[i][j] == 0)
                    vid[i][j] = false;
            }
        }
    }
    // Если флаг 'startGame' установлен, обновляем позицию фруктов
    if (startGame)
    {
        for (int i = 0; i < 21; i++)
        {
            fruit[i].fly = rand() % 2 + 1;
            fruit[i].rect.left = 5 + 110 * i + 50;
        }
        //sound.up.play();
        startGame = false;
    }

    if (pusk > 0)
        pusk--;

    // Проверяем, нажал ли игрок на фрукт
    for (int i = 0; i < 21; i++)
    {
        if (fruit[i].fruit.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && fruit[i].changeTextureBool && pusk == 0 && !lose)
        {
            if (fruit[i].fruitNumber < 20)
            {
                // Увеличиваем счет и обновляем позицию фрукта
                fruit[i].changeTextureBool = false;
                score.c++;
                fruit[i].rect.left -= 50;
                //sound.choppedFruit.play();
            }
            else
            {
                // Игрок нажал на бомбу, устанавливаем флаг 'lose'
                lose = true;
                /*if (!sound.bomba)
                {
                    sound.boom.play();
                    sound.bomba = true;
                }*/
            }
        }
    }

    // Обновляем счетчик 'prop' и устанавливаем флаг 'lose', если необходимо
    if (prop > 3)
        prop = 3;

    if (prop == 3)
        lose = true;

    // Проигрываем звук 'game over', если игрок проиграл
    //if (lose /*&& !sound.ops*/)
    //{
    //    sound.gameover.play();
    //    sound.ops = true;
    //}

    // Обновляем позицию спрайтов крестов
    for (int i = 0; i < prop; i++)
        cross[i].setTextureRect(IntRect(50, 0, 50, 50));

    // Обновляем позицию фруктов
    for (int i = 0; i < 20; i++)
        if (!lose)
            fruit[i].update();

    // Обновляем счет
    score.update();
    window.clear(Color::White); // Очищаем окно и рисуем игровые элементы
    window.draw(fon);

    // Рисуем видимые ячейки
    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
        {
            strel.setPosition(i * 6, j * 6);
            if (vid[i][j])
                window.draw(strel);
        }

    // Рисуем фрукты и счет
    for (int i = 0; i < 21; i++)
    {
        window.draw(fruit[i].fruit);
        if (!fruit[i].changeTextureBool)
            window.draw(fruit[i].choppedFruit);
        for (int i = 0; i < 3; i++)
            if (score.vid[i])
                window.draw(score.sec[i]);
        window.display();
    }

    window.draw(ArbScore);
    for (int i = 0; i < 3; i++)
        if (score.vid[i])
            window.draw(score.sec[i]);
    for (int i = 0; i < 3; i++)
        window.draw(cross[i]);
    if (lose)
    {
        window.draw(youLose);
    }

    window.display();

    return 0;
}