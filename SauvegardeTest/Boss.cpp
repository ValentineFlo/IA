#include "Boss.h"

/// State du Boss
///// Idle State
Boss::IState* Boss::IdleState::handle(const State& state)
{
    if (state == State::CHASE)
    {
        return new ChaseState();
    }

    if (state == State::THIEVE)
    {
        return new ThieveState();
    }

    return nullptr;
}

void Boss::IdleState::update(Boss* boss, float deltaTime)
{
    sf::Vector2f direction = boss->m_targetPosition - boss->getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (direction.x == 0 && direction.y == 0) // verification
    {
        return; 
    }

    if (distance < 200.0f)
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

    if (state == State::THIEVE)
    {
        return new ThieveState();
    }


    return nullptr;
}

void Boss::ChaseState::update(Boss* boss, float deltaTime)
{
    sf::Vector2f direction = boss->m_targetPosition - boss->getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 200.0f)
    {
        boss->changeState(State::IDLE);
        return;
    }


    if (distance < 10.0f)
    {
        boss->changeState(State::THIEVE);
        return;
    }

    if (distance > 0)
    {
        direction /= distance;
        boss->move(direction * boss->getSpeed() * deltaTime);
    }
    else
        return;

}

///// Thieve State
Boss::IState* Boss::ThieveState::handle(const State& state)
{
    if (state == State::IDLE)
    {
        return new IdleState();
    }

    if (state == State::CHASE)
    {
        return new ChaseState();
    }

    return nullptr;
}

void Boss::ThieveState::update(Boss* boss, float deltaTime)
{
    sf::Vector2f direction = boss->m_targetPosition - boss->getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    /// Code here
    if (boss->m_pieces)
    {
        boss->m_pieces->thievePieces();
    }


    if (distance > 10.0f)
    {
        boss->changeState(State::CHASE);
        return;
    }

    if (distance > 0)
    {
        direction /= distance;
        boss->move(direction * boss->getSpeed() * deltaTime);
    }
    else
        return;

}



// Boss

Boss::Boss()
    : m_currentState(new IdleState())
    , m_detectionRadius(350.0f)
    , m_speed(150.0f)
{
    m_boss.setSize(sf::Vector2f(50, 50));
    m_boss.setFillColor(sf::Color::Magenta);
    m_boss.setPosition(400, 50);
    m_PV = 200;
}

Boss::~Boss()
{
    delete m_currentState;
}

void Boss::setTargetPosition(const sf::Vector2f& position) { m_targetPosition = position; }
void Boss::move(const sf::Vector2f& offset) {m_boss.move(offset);}
void Boss::changeState(const State& newState)
{
    if (m_currentState)
    {
        IState* state = m_currentState->handle(newState);
        if (state)
        {
            delete m_currentState;
            m_currentState = state;
        }
    }
}

void Boss::setPieces(Pieces* pieces)
{
    m_pieces = pieces;
}

void Boss::Init() {}

void Boss::Update(float deltaTime)
{
    if (m_currentState)
    {
        m_currentState->update(this, deltaTime);
    }

}

void Boss::Draw(sf::RenderWindow& window)
{
    window.draw(m_boss);
}

sf::FloatRect Boss::GetBounds() const { return m_boss.getGlobalBounds(); }

float Boss::getSpeed() const { return m_speed; }
const sf::Vector2f& Boss::getPosition() const { return m_boss.getPosition(); }
float Boss::getDetectionRadius() const { return m_detectionRadius; }

int Boss::getPV() const { return m_PV; }
void Boss::setPV(int PV) { m_PV = PV; }

void Boss::takeDamage(int damagenmbr)
{
    m_PV -= damagenmbr;
}

bool Boss::isDead() const
{
    if (m_PV <= 0)
    {
        return true;
    }
    return false;
}
