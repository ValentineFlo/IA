#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObjects.h"
#include "Pieces.h"

/**
 * @class Boss
 * @brief Represente un boss avec IA et state machine
 *
 * Cette classe g�re les comportements du Boss, ses attaques,
 * son �tat "voleur" et ses interactions avec le joueur.
 */

class Boss : public IGameObject
{

protected:
    /**
     * @brief Etat du boss
     */
    enum State
    {
          IDLE
        , CHASE
        , THIEVE
    };
    /**
     * @brief Interface des stats
     */
    struct IState
    {
        virtual ~IState() = default;
        virtual IState* handle(const State& state) = 0;
        virtual void update(Boss* boss, float deltaTime) = 0;
    };
    /**
     * @brief mode Idle
     */
    struct IdleState : IState
    {
        ~IdleState() override = default;
        IState* handle(const State& state) override;
        void update(Boss* boss, float deltaTime) override;
    };
    /**
     * @brief Mode Chase
     */
    struct ChaseState : IState
    {
        ~ChaseState() override = default;
        IState* handle(const State& state) override;
        void update(Boss* boss, float deltaTime) override;
    };
    /**
     * @brief mode voleur
     */
    struct ThieveState : IState
    {
        ~ThieveState() override = default;
        IState* handle(const State& state) override;
        void update(Boss* boss, float deltaTime) override;

    };

public:
    /**
     * @brief Constructeur du Boss.
     */
    Boss();
    /**
     * @brief destructeur du MegaBoss.
     */
    ~Boss();
    /**
     * @brief prend la position
     * @param la position du boss
     */
    void setTargetPosition(const sf::Vector2f& position);
    /**
     * @brief faire bonger le boss
     * @param vecteur de sfml
     */
    void move(const sf::Vector2f& offset);
    /**
     * @brief Change le boss d'etat
     * @param prend en param�tre une r�f�rence � state
     */
    void changeState(const State& newState);
    /**
     * @brief change le nombre de pi�ces
     * @param vprend un point
     */
    void setPieces(Pieces* pieces);

    IState* m_currentState; 

public:
    /**
     * @brief initialise l'�tat du boss.
     */
    void Init() override;
    /**
     * @brief Met � jour l'�tat du boss.
     * @param deltatime Temps �coul� depuis la derni�re mise � jour.
     */
    void Update(float deltaTime) override;
    /**
     * @brief Dessine le boss � l'�cran.
     * @param window Fen�tre SFML dans laquelle dessiner.
     */
    void Draw(sf::RenderWindow& window) override;

public:
    /**
     * @brief Bounds pour les collisions
     */
    sf::FloatRect GetBounds() const;
    /**
     * @brief vitesse du boss
     */
    float getSpeed() const;
    /**
     * @brief r�cup�re la position
     */
    const sf::Vector2f& getPosition() const;
    /**
     * @brief D�tecte si le joueur est � port�e du MegaBoss.
     * @return true si le joueur est d�tect�, sinon false.
     */
    float getDetectionRadius() const;

public:
    /**
     * @brief r�cup�re les PV
     */
    int getPV() const;
    /**
     * @brief change PV
     * @param prend les PV en argument
     */
    void setPV(int PV);
    /**
     * @brief condition si le boss meurt
     * @return true si le joueur � ses PV � Z�ro
     */
    void takeDamage(int damagenmbr);
    /**
     * @brief condition si il meurt
     * @return true si le Boss � ses PV � Z�ro
     */
    bool isDead() const;

private:
    sf::RectangleShape m_boss;
    sf::Vector2f m_targetPosition;
    float m_speed;
    float m_detectionRadius;
    Pieces* m_pieces = nullptr;
    int m_PV;
}; 