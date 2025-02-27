#include "Projectiles.h"

Projectiles::Projectiles()
{
    Init();
}

void Projectiles::Init() 
{
    m_speed = 500.0f;
    m_player = nullptr;
}

void Projectiles::Update(float deltaTime) {}

void Projectiles::Draw(sf::RenderWindow& window) 
{
    for (const auto& projectile : m_projectiles) 
    {
        window.draw(projectile);
    }
}

sf::FloatRect Projectiles::GetBounds() const {
    if (!m_projectiles.empty()) {
        return m_projectiles.front().getGlobalBounds();
    }
    return sf::FloatRect();
}


void Projectiles::Shoot()
{
    sf::CircleShape projectile(5);
    projectile.setFillColor(sf::Color::Cyan);
    projectile.setPosition(m_player->getPosition());
    m_projectiles.push_back(projectile);
    std::cout << "Tir ajouté ! Nombre actuel : " << m_projectiles.size() << std::endl;
}