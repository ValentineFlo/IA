#pragma once
#include "Player.h"
class Game;

class Pieces : public IGameObject
{
public:
    Pieces(Player* player, int score);
    ~Pieces();
    void Init() override;
    void Update(float deltatime) override;
    void Draw(sf::RenderWindow& window) override;

    int& getScore();
    void setScore(int score);

public:
    void winPieces();
    void thievePieces();

public:
    void addScore(int changeScore); // ajoute changeScore au score
    void subScore(int changeScore); // enleve changeScore au score

private:
    std::vector<sf::CircleShape> m_pieces;
    Player* m_player;
    int m_score;

};