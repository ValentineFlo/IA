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

    std::cout << "thieve" << std::endl;

    //std::cout << "score: " << boss->piece->getScore() << std::endl;

    int score = boss->piece->getScore();
    score -= 10;
    boss->piece->setScore(score);

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
    , piece(nullptr)
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