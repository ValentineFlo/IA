#include "Player.h"

Player::Player()
{
    Init();
}

void Player::Init() 
{
    m_player.setSize(sf::Vector2f(50, 50));
    m_player.setFillColor(sf::Color::Green);
    m_player.setPosition(400, 500);
    m_speed = 300.0f;
    m_PV = 100;
}

void Player::Update(float deltaTime)
{
    
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        m_player.move(0, -m_speed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        m_player.move(-m_speed * deltaTime, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_player.move(0, m_speed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_player.move(m_speed * deltaTime, 0);

    // Player limit window
    sf::Vector2f pos = m_player.getPosition();
    pos.x = std::max(0.f, std::min(pos.x, 750.f));
    pos.y = std::max(0.f, std::min(pos.y, 550.f));
    m_player.setPosition(pos);
    m_position = m_player.getPosition();

}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(m_player);
}


sf::FloatRect Player::GetBounds() const { return m_player.getGlobalBounds(); }

const sf::Vector2f& Player::getPosition() const { return m_position; }
void Player::setPosition(const sf::Vector2f& pos) { m_player.setPosition(pos); }

int Player::getPV() const { return m_PV; }
void Player::setPV(int PV) { m_PV = PV; }

void Player::takeDamage(int damagenmbr)
{
    m_PV -= damagenmbr;
}

bool Player::isDead() const
{
    if (m_PV <= 0)
	{
		return true;
	}
	return false;
}

