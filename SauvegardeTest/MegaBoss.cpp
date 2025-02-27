#include "MegaBoss.h"

MegaBoss::MegaBoss()
{
    m_megaboss.setSize(sf::Vector2f(50, 50));
    m_megaboss.setFillColor(sf::Color::Red);
    m_megaboss.setPosition(300, 50);
    m_speed = 100.0f;
	m_PV = 300;
}

MegaBoss::~MegaBoss(){}

void MegaBoss::Init(){}

void MegaBoss::Update(float deltatime)
{
	m_position = m_megaboss.getPosition();

    sf::FloatRect bossBounds = m_megaboss.getGlobalBounds();
    sf::FloatRect playerBounds = m_player->GetBounds();

    if (m_PV <= 0)
	{
		m_PV = 0;
	}


}

void MegaBoss::Draw(sf::RenderWindow& window)
{
	window.draw(m_megaboss);
}
sf::FloatRect MegaBoss::GetBounds() const { return m_megaboss.getGlobalBounds(); }


const sf::Vector2f& MegaBoss::getPosition() const { return m_position; }
void MegaBoss::setPosition(const sf::Vector2f& pos) { m_megaboss.setPosition(pos); }

void MegaBoss::SetPlayer(Player* player) { m_player = player; }

int MegaBoss::getPV() const { return m_PV; }
void MegaBoss::setPV(int PV) { m_PV = PV; }
void MegaBoss::takeDamage(int damagenmbr)
{
    m_PV -= damagenmbr;
}

bool MegaBoss::isDead() const
{
    if (m_PV <= 0)
    {
        return true;
    }
    return false;
}
