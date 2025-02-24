#include "Boss.h"

/// State du Boss
///// Idle State
Boss::IState* Boss::IdleState::handle(const State& state)
{
    if (state == State::CHASE)
    {
        return new ChaseState();
    }
    return nullptr;
}

void Boss::IdleState::update(Boss* boss, float deltaTime)
{
    sf::Vector2f direction = boss->m_targetPosition - boss->getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 200.0f)
    {
        boss->changeState(State::CHASE);
        return;
    }
}
///// Chase State
Boss::IState* Boss::ChaseState::handle(const State& state)
{
    if (state == State::IDLE)
    {
        return new IdleState();
    }
    return nullptr;
}

void Boss::ChaseState::update(Boss* boss, float deltaTime)
{
    sf::Vector2f direction = boss->m_targetPosition - boss->getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 40)
    {
        boss->changeState(State::IDLE);
        return;
    }

    if (distance > 0)
    {
        direction /= distance;
        boss->move(direction * boss->getSpeed() * deltaTime);
    }
}

// Boss

Boss::Boss() : m_currentState(new IdleState())
{
    m_boss.setSize(sf::Vector2f(50, 50));
    m_boss.setFillColor(sf::Color::Red);
    m_boss.setPosition(400, 50);
}

Boss::~Boss()
{
    delete m_currentState;
}

void Boss::Init() {}

void Boss::Update(float deltatime)
{
    if (m_currentState)
    {
        m_currentState->update(this, deltatime);
    }
}

void Boss::Draw(sf::RenderWindow& window)
{
    window.draw(m_boss);
}

sf::FloatRect Boss::GetBounds() const { return m_boss.getGlobalBounds(); }
sf::Vector2f Boss::GetPosition() const { return m_boss.getPosition(); }