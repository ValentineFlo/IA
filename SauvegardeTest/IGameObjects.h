#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class IGameObject
{
public:
    virtual ~IGameObject() = default;
    virtual void Init() = 0;
    virtual void Update(float deltatime) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
};
