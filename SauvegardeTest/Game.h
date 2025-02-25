#pragma once
#include "IGameObjects.h"
#include "Pieces.h"
#include "Scenes.h"
#include "Boss.h"


class Game
{
public:
    Game();
    ~Game();
    void Execute();

private:
    void Events();
    void Update(const float& deltaTime);
    void Draw();

private:
    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime;
    sf::Font font;
    sf::Text textScore;
    std::vector<IGameObject*> gameObjects;
    int score = 0;
    SaveFile saveFile;
    Player* player;
    Boss* boss;

};