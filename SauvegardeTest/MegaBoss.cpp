#include "MegaBoss.h"
#include "BTMegaBoss.h"
#include "Projectiles.h"

MegaBoss::MegaBoss() : m_rootNode(this), m_player(nullptr), m_projectiles(nullptr), m_projectilesMegaBoss(nullptr)
{
    m_megaboss.setSize(sf::Vector2f(50, 50));
    m_megaboss.setFillColor(sf::Color::Red);
    m_megaboss.setPosition(100, 40);
    m_speed = 100.0f;
	m_PV = 300;

    auto* behavior = new BT::Sequence(&m_rootNode);

    auto* idleOrPatrol = new BT::Retry(behavior);
    new BT::Idle(idleOrPatrol);
    new BT::Patrol(idleOrPatrol);

    auto* detectAndAttack = new BT::Sequence(behavior);
    new BT::PlayerDetect(detectAndAttack);
    new BT::AttackPlayer(detectAndAttack);

    auto* lowHealthCheck = new BT::LowHealth(behavior);
    new BT::SpecialAttack(lowHealthCheck);
}

MegaBoss::~MegaBoss() 
{

}

void MegaBoss::Update(float deltatime)
{
    m_position = m_megaboss.getPosition();

    if (m_PV <= m_angryPVLimit && !m_isAngry)
    {
        m_isAngry = true;
        m_speed *= m_angrySpeed;
        m_counterShootBoss *= m_angrySpeedShoot;
        m_maxCounterShootBossAngry  *= m_angrySpeedShoot;
    }

    if (m_counterShootBossAngry > 0)
    {
        m_counterShootBossAngry -= deltatime;
    }

    if (m_isIdle)
    {
        m_counterIdle -= deltatime;
        if (m_counterIdle <= 0)
        {
            m_isIdle = false;
        }
        return; 
    }

    Patrol();

    if (m_counterShootBossAngry > 0)
    {
        m_counterShootBossAngry -= deltatime;
    }

    if (isPlayerDetect() && m_counterShootBoss <= 0 && !m_isAngry)
    {
        Shoot();
        Idle();
        m_counterShootBoss = m_maxCounterShootBoss;
    }

    if (m_isAngry && m_counterShootBossAngry <= 0)
    {
        Shoot();
		m_counterShootBossAngry = m_maxCounterShootBossAngry;
    }

    if (m_isAngry && m_counterShootBossAngry <= 0)
    {
        SpecialAttack();
        m_counterShootBossAngry = m_maxCounterShootBossAngry;
    }
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
        m_megaboss.move(0,-m_speed * 0.03f);
        if (m_megaboss.getPosition().y <= 50)
        {
            movingRight = true;
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
        std::cout << "Tir normal" << std::endl;
        m_projectilesMegaBoss->Shoot();
    }
    else if (m_isAngry)
    {
        m_projectilesMegaBoss->ShootAngry();
        std::cout << "Tir special" << std::endl;
    }
}

void MegaBoss::SpecialAttack()
{
    
}


int MegaBoss::getPV() const { return m_PV; }
void MegaBoss::setPV(int PV) { m_PV = PV; }
void MegaBoss::takeDamage(int damagenmbr)
{
    std::cout << "AVANT MegaBoss took " << damagenmbr << " damage" << std::endl;
    std::cout << "AVANT MegaBoss PV : " << m_PV << std::endl;
    m_PV -= damagenmbr;

    if (m_PV <= 0)
    {
        m_PV = 0;
    }

    std::cout << "APRES MegaBoss took " << damagenmbr << " damage" << std::endl;
    std::cout << "APRES MegaBoss PV : " << m_PV << std::endl;
}

bool MegaBoss::isDead() const
{
    if (m_PV <= 0)
    {
        return true;
    }
    return false;
}
