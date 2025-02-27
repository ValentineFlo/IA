#include "Projectiles.h"

Projectiles::Projectiles()
{
    Init();
}

void Projectiles::Init() 
{
    m_speed = 700.0f;
    m_player = nullptr;
}

void Projectiles::Update(float deltaTime) 
{
    for (size_t i = 0; i < m_projectiles.size(); ++i)
    {
        m_projectiles[i].move(m_directions[i] * m_speed * deltaTime);

        if (m_megaboss && m_projectiles[i].getGlobalBounds().intersects(m_megaboss->GetBounds()))
        {
            std::cout << "[INFO] Collision detectee entre un projectile et MegaBoss !" << std::endl;

            m_megaboss->takeDamage(10);

            m_projectiles.erase(m_projectiles.begin() + i);
            m_directions.erase(m_directions.begin() + i);
            --i;
        }
    }

}

void Projectiles::Draw(sf::RenderWindow& window) 
{
    for (const auto& projectile : m_projectiles) 
    {
        window.draw(projectile);
    }
}

sf::FloatRect Projectiles::GetBounds() const 
{
    if (!m_projectiles.empty()) 
    {
        return m_projectiles.front().getGlobalBounds();
    }
    return sf::FloatRect();
}

void Projectiles::SetPlayer(Player* player)
{
    m_player = player;
}

void Projectiles::Shoot()
{
    if (!m_player || !m_megaboss) 
    {
        return;
    }

    sf::Vector2f megabossPosition = m_megaboss->getPosition();

    sf::CircleShape projectile(3);
    projectile.setFillColor(sf::Color::Cyan);

    sf::Vector2f playerCenter = m_player->getPosition();
    projectile.setPosition(playerCenter);

    sf::Vector2f direction = megabossPosition - playerCenter;
    float directionNormalize = std::sqrt(direction.x * direction.x + direction.y * direction.y);

     direction /= directionNormalize;

    float projectileSpeed = 500.f;
    sf::Vector2f velocity = direction * projectileSpeed;

    m_projectiles.push_back(projectile);
    m_directions.push_back(direction);

}


