#pragma once
#include "IGameObjects.h"
#include "Pieces.h"


class Game
{
public:
    Game();
    ~Game();
    void Execute();

private:
    void Events();
    void Update();
    void Draw();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text textScore;
    std::vector<IGameObject*> gameObjects;
    int score = 0;
    SaveFile saveFile;

};