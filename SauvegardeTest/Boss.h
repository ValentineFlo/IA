#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObjects.h"
#include "Player.h"

class Boss : public IGameObject
{

protected:

    enum State
    {
        IDLE
        , CHASE
    };

    struct IState
    {
        virtual ~IState() = default;
        virtual IState* handle(const State& state) = 0;
        virtual void update(Boss* boss, float deltaTime) = 0;
    };

    struct IdleState : IState
    {
        ~IdleState() override = default;
        IState* handle(const State& state) override;
        void update(Boss* boss, float deltaTime) override;
    };

    struct ChaseState : IState
    {
        ~ChaseState() override = default;
        IState* handle(const State& state) override;
        void update(Boss* boss, float deltaTime) override;
    };

public:
    Boss();
    ~Boss();

    void setTargetPosition(const sf::Vector2f& target) { m_targetPosition = target; }
    const sf::Vector2f& getPosition() const { return m_boss.getPosition(); }
    void move(const sf::Vector2f& offset) { m_boss.move(offset); }

    void changeState(const State& newState)
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
    

    IState* m_currentState; 

private:
    void Init() override;
    void Update(float deltatime) override;
    void Draw(sf::RenderWindow& window) override;
    sf::FloatRect GetBounds() const;
    sf::Vector2f GetPosition() const;

    float getSpeed() const { return m_speed; }

private:
    sf::RectangleShape m_boss;
    sf::Vector2f m_targetPosition;
    float m_speed = 300.0f;
    Player m_player;
};