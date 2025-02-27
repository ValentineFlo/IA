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

    void setTargetPosition(const sf::Vector2f& position);
    void move(const sf::Vector2f& offset);
    void changeState(const State& newState);
    void setPieces(Pieces* pieces);

    IState* m_currentState; 

public:
    void Init() override;
    void Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window) override;

public:
    sf::FloatRect GetBounds() const;
    float getSpeed() const;
    const sf::Vector2f& getPosition() const;
    float getDetectionRadius() const;

public:
    int getPV() const;
    void setPV(int PV);
    void takeDamage(int damagenmbr);
    bool isDead() const;

private:
    sf::RectangleShape m_boss;
    sf::Vector2f m_targetPosition;
    float m_speed;
    float m_detectionRadius;
    Pieces* m_pieces = nullptr;
    int m_PV;
}; 