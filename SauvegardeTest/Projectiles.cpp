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
    }
    ShootMegaBoss();
    ShootBoss();
}


void Projectiles::ShootBoss()
{
    for (size_t i = 0; i < m_projectiles.size(); ++i)
    {
       
        if (m_boss && m_projectiles[i].getGlobalBounds().intersects(m_boss->GetBounds()))
        {
            m_boss->takeDamage(10);

            m_projectiles.erase(m_projectiles.begin() + i);
            m_directions.erase(m_directions.begin() + i);
            --i;
        }
    }
}

void Projectiles::ShootMegaBoss()
{
    for (size_t i = 0; i < m_projectiles.size(); ++i)
    {

        if (m_megaboss && m_projectiles[i].getGlobalBounds().intersects(m_megaboss->GetBounds()))
        {
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

void Projectiles::setPlayer(Player* player)
{
    m_player = player;
}

void Projectiles::setTargetMegaBoss(MegaBoss* megaboss) { m_megaboss = megaboss;}

void Projectiles::setTargetBoss(Boss* boss ) { m_boss = boss; }

void Projectiles::Shoot()
{
    if (!m_player || !m_megaboss || !m_boss) 
    {
        if (!m_player)
			std::cout << "Player null" << std::endl;
		if (!m_megaboss)
			std::cout << "MegaBoss null" << std::endl;
		if (!m_boss)
			std::cout << "Boss null" << std::endl;
        return;
    }

    sf::CircleShape projectile(5);
    projectile.setFillColor(sf::Color::Green);

    sf::Vector2f playerCenter = m_player->getPosition();
    projectile.setPosition(playerCenter);

    int randomShoot = std::rand() % 2;
    sf::Vector2f direction;

    if (randomShoot == 0 && m_boss)
    {
		direction = m_boss->getPosition() - playerCenter;
    }
    else if (randomShoot == 1 && m_megaboss)
    {
        direction = m_megaboss->getPosition() - playerCenter;
    }
    else
        return;

    float directionNormalize= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= directionNormalize;

    float projectileSpeed = 500.f;
    sf::Vector2f velocity = direction * projectileSpeed;

    m_projectiles.push_back(projectile);
    m_directions.push_back(direction);

}

/////// Projectil MegaBoss

ProjectilesMegaBoss::ProjectilesMegaBoss()
{
    Init();
}

void ProjectilesMegaBoss::Init()
{
    m_speed = 700.0f;
    m_player = nullptr;
}

void ProjectilesMegaBoss::Update(float deltaTime)
{

    for (size_t i = 0; i < m_projectilesBoss.size(); ++i)
    {
        m_projectilesBoss[i].move(m_directions[i] * m_speed * deltaTime);
    }
    ShootToPlayer();
}

void ProjectilesMegaBoss::ShootToPlayer()
{
    for (size_t i = 0; i < m_projectilesBoss.size(); ++i)
    {

        if (m_player && m_projectilesBoss[i].getGlobalBounds().intersects(m_player->GetBounds()))
        {
            m_player->takeDamage(10);

            m_projectilesBoss.erase(m_projectilesBoss.begin() + i);
            m_directions.erase(m_directions.begin() + i);
            --i;
        }
    }
}
void ProjectilesMegaBoss::ShootToPlayerAngry()
{
    for (size_t i = 0; i < m_projectilesBoss.size(); ++i)
    {

        if (m_player && m_projectilesBoss[i].getGlobalBounds().intersects(m_player->GetBounds()))
        {
            m_player->takeDamage(20);

            m_projectilesBoss.erase(m_projectilesBoss.begin() + i);
            m_directions.erase(m_directions.begin() + i);
            --i;
        }
    }
}


void ProjectilesMegaBoss::Draw(sf::RenderWindow& window)
{
    for (const auto& projectile : m_projectilesBoss)
    {
        window.draw(projectile);
    }
}

sf::FloatRect ProjectilesMegaBoss::GetBounds() const
{
    if (!m_projectilesBoss.empty())
    {
        return m_projectilesBoss.front().getGlobalBounds();
    }
    return sf::FloatRect();
}

void ProjectilesMegaBoss::setPlayer(Player* player)
{
    m_player = player;
}

void ProjectilesMegaBoss::setMegaBoss(MegaBoss* megaboss)
{
    m_megaboss = megaboss;
}

void ProjectilesMegaBoss::setTargetMegaBoss(MegaBoss* megaboss) { m_megaboss = megaboss; }

void ProjectilesMegaBoss::setTargetBoss(Boss* boss) { m_boss = boss; }

void ProjectilesMegaBoss::Shoot()
{
    if (!m_megaboss || !m_player)
    {
        if (!m_player)
            std::cout << "Player null" << std::endl;
        if (!m_megaboss)
            std::cout << "MegaBoss null" << std::endl;
        return;
    }

    sf::CircleShape projectile(4);
    projectile.setFillColor(sf::Color::Cyan);

    sf::Vector2f megabossCenter = m_megaboss->getPosition();
    projectile.setPosition(megabossCenter);

    sf::Vector2f bossPosition = m_megaboss->getPosition();
    sf::Vector2f playerPosition = m_player->getPosition();
    sf::Vector2f direction = playerPosition - bossPosition;

    float directionNormalize = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= directionNormalize;

    float projectileSpeed = 500.f;
    sf::Vector2f velocity = direction * projectileSpeed * 4.0f;

    m_projectilesBoss.push_back(projectile);
    m_directions.push_back(direction);
    std::cout << "Tir special cree ! Nombre total de projectiles : " << m_projectilesBoss.size() << "\n";
}

void ProjectilesMegaBoss::ShootAngry()
{
    sf::CircleShape projectile(6);
    projectile.setFillColor(sf::Color::Red);
    projectile.setPosition(m_megaboss->getPosition());

    sf::Vector2f bossPosition = m_megaboss->getPosition();
    sf::Vector2f playerPosition = m_player->getPosition();
    sf::Vector2f direction = playerPosition - bossPosition;

    float directionNormalize = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (directionNormalize != 0)
        direction /= directionNormalize;

    m_projectilesBoss.push_back(projectile);
    m_directions.push_back(direction);
}