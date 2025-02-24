#pragma once
#include "Player.h"

class Pieces : public IGameObject
{
public:
    Pieces(Player& player, int& score);

    void Init() override;
    void Update(float deltatime) override;
    void Draw(sf::RenderWindow& window) override;

private:
    std::vector<sf::CircleShape> m_pieces;
    Player& m_player;
    int& m_score;

};