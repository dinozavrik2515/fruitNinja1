#include "Fruits.hpp"

using namespace sf;
const int W = 296;
const int H = 167;

//class SetSound
//{
//public:
//    // ���������� ������� � ������
//    SoundBuffer b, e, g, n, r, u;
//    Sound boom, error, gameover, nature, choppedFruit, up;
//    bool ops, bomba;
//
//    SetSound()
//    {
//        // ������������� �������
//        b.loadFromFile();
//        e.loadFromFile();
//        g.loadFromFile();
//        n.loadFromFile();
//        r.loadFromFile();
//        u.loadFromFile();
//
//        // ��������� ������� ��� ������
//        boom.setBuffer(b);
//        error.setBuffer(e);
//        gameover.setBuffer(g);
//        nature.setBuffer(n);
//        choppedFruit.setBuffer(r);
//        up.setBuffer(u);
//
//        nature.setLoop(true); // ��������� ����� ��� ����� nature
//
//        ops = bomba = false; // ������������� ������
//    }
//};
//SetSound sound;




// ��������� ��������� � ������ ���� ����.
int main()
{

    int ground = 600;
    bool startGame = true;
    int prop = 0;

    srand(time(0)); // ������������� ���������� ��������� ����� ������� ��������.
    RenderWindow window(VideoMode(888, 501), "Fruit Ninja"); // �������� ���� ����.

    Texture f;
    f.loadFromFile("images\\fon3.png");
    Sprite fon(f); // �������� ������� �� ����������� ��������.

    // �������� ����� � �������� 3 ������� � ����� ������ �������.
    CircleShape strel;
    strel.setRadius(3.f);
    strel.setFillColor(Color::White);

    // ���������� ��������� �������� ��� �������� ���������� � ��������� ������ � ������� �� ���������.
    bool vid[W][H];
    int time[W][H];
    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
        {
            vid[i][j] = false;
            time[i][j] = 0;
        }

    Texture f2;  // �������� �������� ������� �� �����.
    f2.loadFromFile("fruits.png");

    // �������� ������� �� 21 ������� ������ Fruits, ������ �� ������� ���������������� ��������� ������� � ��������� ���������� �� ������.
    Fruits fruit[21];
    for (int i = 0; i < 21; i++)
        fruit[i].set(f2, 110 * i, ground);

    int pusk = 100; // ���������� ���������� ��� ���������� ����.

    // �������� ������� ��� ����������� ����� � �������������� �������� �������.
    Sprite ArbScore(f2);
    ArbScore.setTextureRect(IntRect(200, 160, 100, 60));
    ArbScore.setScale(0.8, 0.8);
    ArbScore.setPosition(0, 60);
    ArbScore.setRotation(315);

    // �������� �������� ��� ����������� �����.
    Texture scoreTexture;
    scoreTexture.loadFromFile("watermelon.png");
    Score score(&scoreTexture); // �������� ������� ������ Score ��� ����������� �����.

    Texture crossTexture;
    crossTexture.loadFromFile("cross.png"); // �������� �������� ��� ��������� � �������� ������� �� ��� ��������.
    Sprite cross[3];
    for (int i = 0; i < 3; i++)
    {
        cross[i].setTexture(crossTexture);
        cross[i].setTextureRect(IntRect(0, 0, 50, 50));
        cross[i].setPosition(650 + 75 * i, 25);
    }

    Texture youLoseTexture; // �������� �������� ��� ����������� ���������.
    youLoseTexture.loadFromFile("fon2");
    Sprite youLose;
    youLose.setPosition(300, 200);
    bool lose = false;  // ���������� ���������� ��� ������������ ���������.

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window); // �������� ������� ������� ����

    // ������������ ������� ����
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close(); // ��������� ����, ���� ������������ ����� �� ������ ��������
        }
    }

    // �������� �� ����� � ��������� ��������� ������ ������
    for (int i = 0; i < W; i++)
        for (int j = 0; j < W; j++)
        {
            // ���������, ��������� �� ���� ��� ������� �������
            if (pos.x >= i * 6 && pos.x <= (i + 1) * 6 &&
                pos.y >= j * 6 && pos.y <= (j + 1) * 6)
            {
                // ������ ������ ������� � ��������� ������
                vid[i][j] = true;
                time[i][j] = 100;
            }

            // ��������� ������ ��� ������� ������
            if (time[i][j] > 0)
            {
                time[i][j]--;
                if (time[i][j] == 0)
                    vid[i][j] = false;
            }
        }
    }
    // ���� ���� 'startGame' ����������, ��������� ������� �������
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

    // ���������, ����� �� ����� �� �����
    for (int i = 0; i < 21; i++)
    {
        if (fruit[i].fruit.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && fruit[i].changeTextureBool && pusk == 0 && !lose)
        {
            if (fruit[i].fruitNumber < 20)
            {
                // ����������� ���� � ��������� ������� ������
                fruit[i].changeTextureBool = false;
                score.c++;
                fruit[i].rect.left -= 50;
                //sound.choppedFruit.play();
            }
            else
            {
                // ����� ����� �� �����, ������������� ���� 'lose'
                lose = true;
                /*if (!sound.bomba)
                {
                    sound.boom.play();
                    sound.bomba = true;
                }*/
            }
        }
    }

    // ��������� ������� 'prop' � ������������� ���� 'lose', ���� ����������
    if (prop > 3)
        prop = 3;

    if (prop == 3)
        lose = true;

    // ����������� ���� 'game over', ���� ����� ��������
    //if (lose /*&& !sound.ops*/)
    //{
    //    sound.gameover.play();
    //    sound.ops = true;
    //}

    // ��������� ������� �������� �������
    for (int i = 0; i < prop; i++)
        cross[i].setTextureRect(IntRect(50, 0, 50, 50));

    // ��������� ������� �������
    for (int i = 0; i < 20; i++)
        if (!lose)
            fruit[i].update();

    // ��������� ����
    score.update();
    window.clear(Color::White); // ������� ���� � ������ ������� ��������
    window.draw(fon);

    // ������ ������� ������
    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
        {
            strel.setPosition(i * 6, j * 6);
            if (vid[i][j])
                window.draw(strel);
        }

    // ������ ������ � ����
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