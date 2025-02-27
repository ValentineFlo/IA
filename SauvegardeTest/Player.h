#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObjects.h"

class Player : public IGameObject
{
public:
    Player();
    void Init() override;
    void Update(float deltatime) override;
    void Draw(sf::RenderWindow& window) override;
    sf::FloatRect GetBounds() const;
public:
    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& pos);

public:
    int getPV() const;
    void setPV(int PV);
    void takeDamage(int damagenmbr);
    bool isDead() const;

private:
    sf::RectangleShape m_player;
    sf::Vector2f m_position; 
    float m_speed;
    int m_PV;
};