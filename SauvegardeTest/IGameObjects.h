#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Save.h"

class IGameObject
{
public:
    virtual ~IGameObject() = default;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
};
