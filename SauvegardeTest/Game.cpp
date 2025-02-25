#include "Game.h"
Game::Game() : window(sf::VideoMode(800, 600), "Mario Collecteur de Pieces"), saveFile(SaveFile("MySaveAndLoad.txt")), deltaTime(0)
{
    font.loadFromFile("ariali.ttf");
    textScore.setFont(font);
    textScore.setCharacterSize(30);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(10, 10);


    player = new Player;
    Pieces* pieces = new Pieces(*player, score);
    boss = new Boss;

    gameObjects.push_back(player);
    gameObjects.push_back(pieces);
    gameObjects.push_back(boss);

    saveFile = SaveFile("save.txt");

    //FPS 60
    window.setFramerateLimit(60);
}

Game::~Game()
{
    for (auto objects : gameObjects)
        delete objects;
}

void Game::Execute()
{
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds(); 
        Events();
        Update(deltaTime);
        Draw();
    }
}

void Game::Events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            saveFile.save(score);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            saveFile.load(score);
    }
}

void Game::Update(const float& deltaTime)
{
    boss->setTargetPosition(player->getPosition());

    for (auto objects : gameObjects)
    {
        objects->Update(deltaTime);
    }

    textScore.setString("Pieces: " + std::to_string(score));
}

void Game::Draw()
{
    window.clear();
    for (auto objects : gameObjects)
    {
        objects->Draw(window);
    }
    window.draw(textScore);
    window.display();
}