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
    sf::Vector2f GetPosition() const;

private:
    sf::RectangleShape m_player;
};