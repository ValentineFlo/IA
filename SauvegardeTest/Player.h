#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObjects.h"
#include "Boss.h"

class Player : public IGameObject
{
public:
    Player();
    void Init() override;
    void Update(float deltatime) override;
    void Draw(sf::RenderWindow& window) override;
    sf::FloatRect GetBounds() const;

    const sf::Vector2f& getPosition() const { return m_position; }
    void setPosition(const sf::Vector2f& pos) { m_player.setPosition(pos); }

private:
    sf::RectangleShape m_player;
    sf::Vector2f m_position; 
    float m_speed;
};