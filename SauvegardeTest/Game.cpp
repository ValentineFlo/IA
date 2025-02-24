#include "Game.h"
Game::Game() : window(sf::VideoMode(800, 600), "Mario Collecteur de Pieces"), saveFile(SaveFile("MySaveAndLoad.txt"))
{
    font.loadFromFile("ariali.ttf");
    textScore.setFont(font);
    textScore.setCharacterSize(30);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(10, 10);

    Player* player = new Player;
    Pieces* pieces = new Pieces(*player, score);

    gameObjects.push_back(player);
    gameObjects.push_back(pieces);

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
        Events();
        Update();
        Draw();
    }
}

void Game::Events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            saveFile.save(score);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            saveFile.load(score);
    }
}

void Game::Update()
{
    for (auto objects : gameObjects)
    {
        objects->Update();
    }

    textScore.setString("Score: " + std::to_string(score));
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