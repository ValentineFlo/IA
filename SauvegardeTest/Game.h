#pragma once
#include "IGameObjects.h"
#include "Pieces.h"
#include "Scenes.h"
#include "Boss.h"
#include "MegaBoss.h"
#include "Projectiles.h"
#include "Save.h"


class Game
{
public:
    Game();
    ~Game();
    void Run();

private:
    void Events();
    void Update(const float& deltaTime);
    void Draw();


private:
    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime;
    sf::Font font;
    sf::Text m_textScore;
    sf::Text m_textPV_Player;
    sf::Text m_textPV_Boss;
    sf::Text m_textPV_MegaBoss;
    std::vector<IGameObject*> gameObjects;
    int score = 0;
    SaveFile saveFile;
    Pieces* pieces;
    Projectiles* projectiles;
    Player* player;
    Boss* boss;
    MegaBoss* megaboss;

};