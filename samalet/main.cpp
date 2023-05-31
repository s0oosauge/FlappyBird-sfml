#include <SFML/Graphics.hpp>
#include <iostream>

const int width = 864;
const int height = 1080;
const float birdScale = 5.4f;
const float backgroundScale = 1.f;
const float foregroundScale = 1.f;
const float gravity = 0.004f;

float birdAngle = 0.f;
float birdVelocity = 0.f;
float jumpVelocity = -1.1f;

class Pipe {
public:
    Pipe(float x, float y, float scale, sf::Texture& topTexture, sf::Texture& bottomTexture, int gapPosition)
    {
        topSprite.setTexture(topTexture);
        topSprite.setScale(scale, scale);
        topSprite.setPosition(x, (y + gapPosition));

        bottomSprite.setTexture(bottomTexture);
        bottomSprite.setScale(scale, scale);
        bottomSprite.setPosition(x,  ((-y) + gapPosition));
    }

    sf::Sprite topSprite;
    sf::Sprite bottomSprite;
};



void fall(sf::Sprite& bird, float& birdVelocity)
{
    birdVelocity += gravity;
    sf::Vector2f birdPosition = bird.getPosition();
    birdPosition.y += birdVelocity;
    bird.setPosition(birdPosition);
    birdAngle = birdVelocity * 15;
    bird.setRotation(birdAngle);
}

void jump(float& velocity, float jumpVelocity) {
    velocity = jumpVelocity;
}

bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

void updatePipes(Pipe pipes[], int numPipes, sf::Texture& topPipeTexture, sf::Texture& bottomPipeTexture, bool scoreAdded[], int& score)
{
    for (int i = 0; i < numPipes; i++) {
        pipes[i].topSprite.setPosition(pipes[i].topSprite.getPosition().x - 0.35, pipes[i].topSprite.getPosition().y);
        pipes[i].bottomSprite.setPosition(pipes[i].bottomSprite.getPosition().x - 0.35, pipes[i].bottomSprite.getPosition().y);

        if (pipes[i].topSprite.getPosition().x < 200 && pipes[i].topSprite.getPosition().x + 200 > 200 && !scoreAdded[i]) {
            score += 1;
            std::cout << score << std::endl;
            scoreAdded[i] = true;
        }

        if (pipes[i].topSprite.getPosition().x < -650) {
            pipes[i] = Pipe(900.f, -700.f, 1.f, topPipeTexture, bottomPipeTexture, (std::rand() % 201 - 150));
            pipes[i].topSprite.setPosition(pipes[i].topSprite.getPosition().x, pipes[i].topSprite.getPosition().y);
            pipes[i].bottomSprite.setPosition(pipes[i].bottomSprite.getPosition().x, pipes[i].bottomSprite.getPosition().y);
            scoreAdded[i] = false;
        }
    }
}

void updateForeground(sf::Sprite& foreground, sf::Sprite& foreground1)
{
    foreground.setPosition(foreground.getPosition().x - 0.35, foreground.getPosition().y);
    foreground1.setPosition(foreground1.getPosition().x - 0.35, foreground1.getPosition().y);

    if (foreground.getPosition().x < -1000) {
        foreground.setPosition(foreground1.getPosition().x + 960, foreground.getPosition().y);
    }
    if (foreground1.getPosition().x < -1000) {
        foreground1.setPosition(foreground.getPosition().x + 960, foreground1.getPosition().y);
    }
}

void restartGame(sf::Sprite& bird, sf::Texture& topPipeTexture, sf::Texture& bottomPipeTexture, Pipe pipes[], bool scoreAdded[], int& score, const int& numPipes)
{
    bird.setPosition(200.f, 350.f);
    bird.setRotation(0.f);
    birdVelocity = 0.f;

    for (int i = 0; i < numPipes; i++) {
        pipes[i] = Pipe(900.f + i * 500.f, -700.f, 1.f, topPipeTexture, bottomPipeTexture, (std::rand() % 201 - 150));
        scoreAdded[i] = false;
    }

    score = 0;
}

int main()
{

    // Создаем окно размером 864 на 1080 пикселей
    sf::RenderWindow window(sf::VideoMode(width, height), "Flappy Bird");

    // Загружаем текстуры для птицы, верхней и нижней колонны
    sf::Texture birdTexture, topPipeTexture, bottomPipeTexture, backgroundTexture, foregroundTexture;
    if (!birdTexture.loadFromFile      ("C:/Users/ogluz/source/repos/samalet/Images/bird1.png") or
        !topPipeTexture.loadFromFile   ("C:/Users/ogluz/source/repos/samalet/Images/top_pipe.png") or
        !bottomPipeTexture.loadFromFile("C:/Users/ogluz/source/repos/samalet/Images/bottom_pipe.png") or
        !backgroundTexture.loadFromFile("C:/Users/ogluz/source/repos/samalet/Images/background.jpg") or
        !foregroundTexture.loadFromFile ("C:/Users/ogluz/source/repos/samalet/Images/foreground1.png"))
    {
        std::cerr << "Failed to load textures\n";
        return 1;
    }

    // Загружаем текстуры для анимации птицы
    sf::Texture birdTexture1, birdTexture2, birdTexture3;
    if (!birdTexture1.loadFromFile("C:/Users/ogluz/source/repos/samalet/Images/bird1.png") or
        !birdTexture2.loadFromFile("C:/Users/ogluz/source/repos/samalet/Images/bird2.png") or
        !birdTexture3.loadFromFile("C:/Users/ogluz/source/repos/samalet/Images/bird3.png"))
    {
        std::cerr << "Failed to load textures\n";
        return 1;
    }

    float birdAngle = 0.f;

    std::srand(std::time(nullptr));

    // Создаем массив текстур для анимации птицы
    sf::Texture birdTextures[] = { birdTexture1, birdTexture2, birdTexture3 };

    // Создаем часы для анимации птицы
    sf::Clock birdAnimationClock;
    int birdFrameIndex = 0;

    // Создаем спрайт для птицы и заднего фона, устанавливаем начальную позицию птицы
    sf::Sprite bird(birdTexture), background(backgroundTexture), foreground(foregroundTexture), foreground1(foregroundTexture);
    bird.setPosition(200.f, 350.f);
    bird.setScale(birdScale, birdScale);
    background.setPosition(0.f, 0.f);
    background.setScale(backgroundScale, backgroundScale);
    foreground.setPosition(0.f, 870.f);
    foreground.setScale(foregroundScale, foregroundScale);
    foreground1.setPosition(960, 870.f);
    foreground1.setScale(foregroundScale, foregroundScale);

    const int numPipes = 3;
    Pipe pipes[numPipes] = {
        Pipe(900.f, -700.f, 1.f, topPipeTexture, bottomPipeTexture, (std::rand() % 201 - 150)),
        Pipe(1400.f, -700.f, 1.f, topPipeTexture, bottomPipeTexture, (std::rand() % 201 - 150)),
        Pipe(1900.f, -700.f, 1.f, topPipeTexture, bottomPipeTexture, (std::rand() % 201 - 150)),
    };

    bool isGameStarted = false;
    bool isGameOver = false;

    int score = 0;
    int maxscore = 0;

    bool scoreAdded[numPipes] = { false };

    // Основной цикл игры
    while (window.isOpen())
    {
        // Обрабатываем все события в очереди
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (!isGameStarted && !isGameOver && event.mouseButton.button == sf::Mouse::Left)
                {
                    isGameStarted = true;
                }
                if (isGameStarted && event.mouseButton.button == sf::Mouse::Left) {
                    jump(birdVelocity, jumpVelocity);
                    birdAngle = birdVelocity * (-5);
                    bird.setRotation(birdAngle);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (isGameOver && event.key.code == sf::Keyboard::R) {
                    isGameOver = false;
                    restartGame(bird, topPipeTexture, bottomPipeTexture, pipes, scoreAdded, score, numPipes);
                    system("cls");
                    std::cout << "High score: " << maxscore << std::endl;
                }
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        // Рисуем все спрайты на экране
        window.clear(sf::Color::White);
        window.draw(background);
        for (int i = 0; i < numPipes; i++) {
            window.draw(pipes[i].topSprite);
            window.draw(pipes[i].bottomSprite);
            // Проверка коллизии
            if ((checkCollision(bird, pipes[i].topSprite) || checkCollision(bird, pipes[i].bottomSprite) || checkCollision(bird, foreground) || checkCollision(bird, foreground1)) && !isGameOver) {
                isGameOver = true;
                isGameStarted = false;
                if (score > maxscore)
                    maxscore = score;
                std::cout << "Game over!" << std::endl;
                std::cout << "Final score: " << score << std::endl;
            }
        }
        window.draw(bird);
        window.draw(foreground);
        window.draw(foreground1);
        window.display();

        if (!isGameOver)
        {
            // Обновляем анимацию птицы каждые 100 миллисекунд
            if (birdAnimationClock.getElapsedTime().asMilliseconds() > 100) {
                birdFrameIndex++;
                if (birdFrameIndex >= 3) {
                    birdFrameIndex = 0;
                }
                birdAnimationClock.restart();
            }
            bird.setTexture(birdTextures[birdFrameIndex]);

            updateForeground(foreground, foreground1);
        }
        
        if (isGameStarted)
        {
            updatePipes(pipes, numPipes, topPipeTexture, bottomPipeTexture, scoreAdded, score);
            fall(bird, birdVelocity);
        }
    }

    return 0;
}