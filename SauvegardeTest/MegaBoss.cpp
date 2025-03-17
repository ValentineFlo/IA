#include "MegaBoss.h"
#include "BTMegaBoss.h"
#include "Projectiles.h"

MegaBoss::MegaBoss() : m_rootNode(this), m_player(nullptr), m_projectiles(nullptr), m_projectilesMegaBoss(nullptr)
{
    m_megaboss.setSize(sf::Vector2f(50, 50));
    m_megaboss.setFillColor(sf::Color::Red);
    m_megaboss.setPosition(100, 40);
	m_PV = 300;

    auto* behavior = new BT::Sequence(&m_rootNode);

    auto* lowHealthCheck = new BT::LowHealth(behavior);

    auto* detectAndAttack = new BT::Sequence(behavior);

    auto* Patrol = new BT::Patrol(detectAndAttack);
    new BT::PlayerDetect(detectAndAttack);
    new BT::AttackPlayer(detectAndAttack);
    new BT::Idle(detectAndAttack);

    new BT::SpecialAttack(lowHealthCheck);
}

MegaBoss::~MegaBoss() 
{

}

void MegaBoss::Update(float deltatime)
{

    m_position = m_megaboss.getPosition();

    if (m_counterShootBoss > 0)
    {
        m_counterShootBoss -= deltatime;
    }

    if (m_counterShootBossAngry > 0)
    {
        m_counterShootBossAngry -= deltatime;
    }


    isPlayerDetect();

    if (m_specialAttackTimer > 0)
    {
        m_specialAttackTimer -= deltatime;
    }

    m_rootNode.tick();
}



void MegaBoss::Draw(sf::RenderWindow& window)
{
	window.draw(m_megaboss);
}
sf::FloatRect MegaBoss::GetBounds() const { return m_megaboss.getGlobalBounds(); }

const sf::Vector2f& MegaBoss::getPosition() const { return m_position; }
void MegaBoss::setPosition(const sf::Vector2f& pos) { m_megaboss.setPosition(pos); }

void MegaBoss::setPlayer(Player* player) { m_player = player; }

void MegaBoss::setProjectiles(ProjectilesMegaBoss* projectiles)
{
    m_projectilesMegaBoss = projectiles;
}


bool MegaBoss::isPlayerDetect()
{
    if (!m_player) return false;

    sf::Vector2f bossPosition = m_megaboss.getPosition();
    sf::Vector2f playerPosition = m_player->getPosition();

    sf::Vector2f direction = bossPosition - playerPosition;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    float detectionCircle= 200.0f;

    if (distance <= detectionCircle)
    {
        return true;
    }

    return false;
}

void MegaBoss::Idle()
{
    if (!m_isIdle)
    {
        m_isIdle = true;
        m_counterIdle = m_maxCounterIdle;
    }


}

void MegaBoss::Patrol()
{
    static bool movingRight = true;
    if (!m_isAngry)
    {
        float m_speed = 100;

        if (movingRight)
        {
            m_megaboss.move(0, m_speed * 0.03f);
            if (m_megaboss.getPosition().y >= 5000)
            {
                movingRight = false;
            }
        }
        else
        {
            m_megaboss.move(0, -m_speed * 0.03f);
            if (m_megaboss.getPosition().y <= 50)
            {
                movingRight = true;
            }
        }
    }
    else if (m_isAngry)
    {
        float m_speed = 200;

        if (movingRight)
        {
            m_megaboss.move(0, m_speed * 0.03f);
            if (m_megaboss.getPosition().y >= 500)
            {
                movingRight = false;
            }
        }
        else
        {
            m_megaboss.move(0, -m_speed * 0.03f);
            if (m_megaboss.getPosition().y <= 50)
            {
                movingRight = true;
            }
        }
    }

}


void MegaBoss::Shoot()
{
    if (!m_projectilesMegaBoss)
    {
        return;
    }

    if (!m_isAngry) 
    {
        m_projectilesMegaBoss->Shoot();
        Idle();
    }
   
}

void MegaBoss::SpecialAttack()
{

    if (!m_projectilesMegaBoss) 
    {
        return;
    }

    if (m_specialAttackTimer > 0)
    {
        return;
    }

    m_projectilesMegaBoss->ShootAngry();
    m_specialAttackTimer = m_specialAttackCooldown;
    
}


int MegaBoss::getPV() const { return m_PV; }
void MegaBoss::setPV(int PV) { m_PV = PV; }
void MegaBoss::takeDamage(int damagenmbr)
{
    m_PV -= damagenmbr;

    if (m_PV <= 0)
    {
        m_PV = 0;
    }

    if (m_PV <= 150)
    {
        m_rootNode.tick();
    }
}

bool MegaBoss::isDead() const
{
    if (m_PV <= 0)
    {
        return true;
    }
    return false;
}

float MegaBoss::reseatShootTimer()
{
    return m_counterShootBoss = m_counterTimerShoot;
}

bool MegaBoss::essaiShoot()
{
    return m_counterShootBoss <= 0;
}

bool MegaBoss::isIdle()
{
    if (m_isIdle)
    {
        return true;
    }
    return false;
}

bool MegaBoss::startIdle()
{
    if (!m_isIdle) 
    {
        m_counterIdle = m_maxCounterIdle;
        m_isIdle = true;
    }
    return true;
}

bool MegaBoss::endIdle()
{
    if (!m_isIdle) 
    {
        return false;
    }

    if (m_counterIdle > 0)
    {
        m_counterIdle -= 1;
        return false;
    }
    
    m_isIdle = false;
    return true;
}