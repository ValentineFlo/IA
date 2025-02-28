#include "MegaBoss.h"
#include "BTMegaBoss.h"

MegaBoss::MegaBoss() : m_rootNode(this), m_player(nullptr)
{
    m_megaboss.setSize(sf::Vector2f(50, 50));
    m_megaboss.setFillColor(sf::Color::Red);
    m_megaboss.setPosition(300, 50);
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

MegaBoss::~MegaBoss(){}

void MegaBoss::Init(){}

void MegaBoss::Update(float deltatime)
{
	m_position = m_megaboss.getPosition();

    sf::FloatRect bossBounds = m_megaboss.getGlobalBounds();
    sf::FloatRect playerBounds = m_player->GetBounds();
    Patrol(); 

}

void MegaBoss::Draw(sf::RenderWindow& window)
{
	window.draw(m_megaboss);
}
sf::FloatRect MegaBoss::GetBounds() const { return m_megaboss.getGlobalBounds(); }

const sf::Vector2f& MegaBoss::getPosition() const { return m_position; }
void MegaBoss::setPosition(const sf::Vector2f& pos) { m_megaboss.setPosition(pos); }

void MegaBoss::SetPlayer(Player* player) { m_player = player; }


bool MegaBoss::isPlayerDetect()
{
    return false;
}

void MegaBoss::Idle()
{

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
        if (m_megaboss.getPosition().y <= 100)
        {
            movingRight = true;
        }
    }
}

void MegaBoss::Shoot()
{

}

void MegaBoss::SpecialAttack()
{

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
}

bool MegaBoss::isDead() const
{
    if (m_PV <= 0)
    {
        return true;
    }
    return false;
}
