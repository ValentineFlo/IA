#pragma once
#include <SFML/Graphics.hpp>
#include "IGameObjects.h"

/**
 * @class Player
 *
 * Cette classe gère les comportements du joueur
 */

class Player : public IGameObject
{
public:
    /**
     * @brief Constructeur du player.
     */
    Player();
    /**
     * @brief initialise le player
     */
    void Init() override;
    /**
     * @brief Met à jour l'état du player.
     * @param deltatime Temps écoulé depuis la dernière mise à jour.
     */
    void Update(float deltatime) override;
    /**
     * @brief Dessine le player à l'écran.
     * @param window Fenêtre SFML dans laquelle dessiner.
     */
    void Draw(sf::RenderWindow& window) override;
    /**
     * @brief Bounds pour les collisions
     */
    sf::FloatRect GetBounds() const;
public:
    /**
     * @brief récupère la position
     */
    const sf::Vector2f& getPosition() const;
    /**
     * @brief change position
     * @param vecteur de SFML
     */
    void setPosition(const sf::Vector2f& pos);

public:
    /**
     * @brief récupère les PV
     */
    int getPV() const;
    /**
     * @brief change PV
     * @param prend les PV en argument
     */
    void setPV(int PV);
    /**
     * @brief prend des dommanges
     * @param le nombre de dommage qu'il subit
     */
    void takeDamage(int damagenmbr);
    /**
     * @brief condition si le player meurt
     * @return true si le player à ses PV à Zéro
     */
    bool isDead() const;

private:
    sf::RectangleShape m_player;
    sf::Vector2f m_position; 
    float m_speed;
    int m_PV;
};