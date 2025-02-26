#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObjects.h"
#include "Pieces.h"

// faire en sorte que le boss vole des pieces quand il touche le player

class Boss : public IGameObject
{

protected:

    enum State
    {
          IDLE
        , CHASE
        , THIEVE
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

    struct ThieveState : IState
    {
        ~ThieveState() override = default;
        IState* handle(const State& state) override;
        void update(Boss* boss, float deltaTime) override;

    };

public:
    Boss();
    ~Boss();

    void setTargetPosition(const sf::Vector2f& position) { m_targetPosition = position; }

    void move(const sf::Vector2f& offset)
    {
        m_boss.move(offset);
    }

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
    
    void setPieces(Pieces* pieces);

    IState* m_currentState; 

private:
    void Init() override;
    void Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window) override;
    sf::FloatRect GetBounds() const;
    float getSpeed() const { return m_speed; }
    const sf::Vector2f& getPosition() const { return m_boss.getPosition(); }
    float getDetectionRadius() const { return m_detectionRadius; }


private:
    sf::RectangleShape m_boss;
    sf::Vector2f m_targetPosition;
    float m_speed;
    float m_detectionRadius;
    Pieces* m_pieces = nullptr;
}; 