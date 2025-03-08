#pragma once
#include "IGameObjects.h"
#include "Player.h"
#include "Tree.h"

/**
 * @class MegaBoss
 * @brief Represente un boss avec IA et behavior tree.
 *
 * Cette classe gère les comportements du MegaBoss, ses attaques,
 * son état "angry" et ses interactions avec le joueur.
 */

class Projectiles;
class ProjectilesMegaBoss;

class MegaBoss : public IGameObject
{
public:
	/**
	 * @brief Constructeur du MegaBoss.
	 */
	MegaBoss();
	/**
	 * @brief Destructeur du MegaBoss.
	 */
	~MegaBoss();
	/**
	 * @brief initialise l'état du mégaboss.
	 */
	void Init() override {};
	/**
	 * @brief Met à jour l'état du mégaboss.
	 * @param deltatime Temps écoulé depuis la dernière mise à jour.
	 */
	void Update(float deltatime) override;
	/**
	 * @brief Dessine le mégaboss à l'écran.
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
	 * @brief change position player
	 * @param pointeur de player
	 */
	void setPlayer(Player* player);
	/**
	 * @brief change position projectile
	 * @param pointeur vers les projectiles de mégaboss
	 */
	void setProjectiles(ProjectilesMegaBoss* projectiles);

public:
	//Behavior tree

	/**
	 * @brief Détecte si le joueur est à portée du MegaBoss.
	 * @return true si le joueur est détecté, sinon false.
	 */
	bool isPlayerDetect();
	/**
	 * @brief Mode Idle
	 */
	void Idle();
	/**
	 * @brief Mode Patrol
	 */
	void Patrol();
	/**
	 * @brief Mode Shoot
	 */
	void Shoot();
	/**
	 * @brief Mode Special Shoot
	 */
	void SpecialAttack();

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
	 * @brief condition si le megaboss meurt 
	 * @return true si le MegaBoss à ses PV à Zéro
	 */
	bool isDead() const;

	float reseatShootTimer();

	bool canShoot();

	bool isIdle();
	bool startIdle();
	bool endIdle();


private:
	sf::RectangleShape m_megaboss;
	sf::Vector2f m_position;
	Player* m_player;
	Projectiles* m_projectiles;
	ProjectilesMegaBoss* m_projectilesMegaBoss;
	BT::RootNode m_rootNode; 
	float m_speed;
	int m_PV;

	float m_counterShootBoss = 0.0f;
	float m_counterTimerShoot = 2.0f;
	bool m_isIdle = false;
	float m_counterIdle = 0.0f;
	const float m_maxCounterIdle = 2.0f;

	bool m_isAngry = false;

	float m_counterShootBossAngry = 0.0f;

	//// Special attack
	//const float m_specialAttackPVLimit = 50.0f;
	//float m_attackSpeed = 3.0f;
	//float m_attackSpeedShoot = 1.5f;
	//bool m_isSpecialAttack = false;
};