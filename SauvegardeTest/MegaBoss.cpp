#include "MegaBoss.h"
#include "BTMegaBoss.h"
#include "Projectiles.h"

MegaBoss::MegaBoss() : m_rootNode(this), m_player(nullptr), m_projectiles(nullptr), m_projectilesMegaBoss(nullptr)
{
    m_megaboss.setSize(sf::Vector2f(50, 50));
    m_megaboss.setFillColor(sf::Color::Red);
    m_megaboss.setPosition(100, 40);
    m_speed = 100.0f;
	m_PV = 260;

    auto* behavior = new BT::Sequence(&m_rootNode);
    std::cout << "BT: Behavior Tree sequence created" << std::endl;

    auto* lowHealthCheck = new BT::LowHealth(behavior);

    auto* detectAndAttack = new BT::Sequence(behavior);
    std::cout << "BT: Adding PlayerDetect Sequence" << std::endl;

    auto* Patrol = new BT::Patrol(detectAndAttack);
    new BT::PlayerDetect(detectAndAttack);
    new BT::AttackPlayer(detectAndAttack);
    new BT::Idle(detectAndAttack);

    std::cout << "BT: Adding Special Attack on Low Health" << std::endl;
    new BT::SpecialAttack(lowHealthCheck);
    new BT::Patrol(detectAndAttack);

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

    if (m_isIdle)
    {
        bool finished = endIdle();
        if (finished)
        {
            std::cout << "BT: MegaBoss Idle Finished in Update!" << std::endl;
        }
    }

    isPlayerDetect();

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
        Idle();
    }
   
}

void MegaBoss::SpecialAttack()
{
    if (!m_projectilesMegaBoss) return;

    std::cout << "MegaBoss utilise son attaque speciale en rafale !" << std::endl;

    if (m_isAngry)
    {
        m_projectilesMegaBoss->ShootAngry();
        std::cout << "Tir angry" << std::endl;
    }

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
    m_rootNode.tick(); 
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

bool MegaBoss::canShoot()
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
        std::cout << "MegaBoss entering Idle mode." << std::endl;

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
        std::cout << "Idle countdown: " << m_counterIdle << std::endl;
        return false;
    }
    

    std::cout << "MegaBoss exiting Idle mode." << std::endl;
    m_isIdle = false;
    return true;
}