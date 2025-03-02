#pragma once
#include "IGameObjects.h"
#include "Player.h"
#include "Boss.h"
#include "MegaBoss.h"
#include <vector>

/**
 * @class Projectiles
 * @brief Represente les projectiles lancé par le player
 *
 * Cette classe gère les comportements des projectiles
 */

class Projectiles : public IGameObject
{
public:
	/**
	 * @brief Constructeur du Projectiles.
	 */
	Projectiles();
	/**
	 * @brief Destructeur du Projectiles.
	 */
	~Projectiles() = default;
	/**
	 * @brief initialise l'état du mégaboss.
	 */
	void Init() override;
	/**
	 * @brief Met à jour l'état du player.
	 * @param deltatime Temps écoulé depuis la dernière mise à jour.
	 */
	void Update(float deltatime)override;
	/**
	 * @brief Dessine le mégaboss à l'écran.
	 * @param window Fenêtre SFML dans laquelle dessiner.
	 */
	void Draw(sf::RenderWindow& window) override;
	/**
	 * @brief Bounds pour les collisions
	 */
	sf::FloatRect GetBounds() const;

	/**
	 * @brief change player
	 * @param pointeur vers un player
	 */
	void setPlayer(Player* player);
	/**
	 * @brief récupère megaboss
	 * @param pointeur vers un mégaboss
	 */
	void setTargetMegaBoss(MegaBoss* megaboss);
	/**
	 * @brief récupère boss
	 * @param pointeur vers un boss
	 */
	void setTargetBoss(Boss* boss);

public:
	/**
	 * @brief fonction de shoot
	 */
	void Shoot();
	/**
	 * @brief Shoot pour le boss
	 */
	void ShootBoss();
	/**
	 * @brief Shoot pour le mégaboss
	 */
	void ShootMegaBoss();
private:
	MegaBoss* m_megaboss;
	Boss* m_boss;
	Player* m_player;
	std::vector<sf::CircleShape> m_projectiles;
	std::vector<sf::Vector2f> m_directions;
	float m_speed;
};

class ProjectilesMegaBoss : public IGameObject
{
public:
	/**
	 * @brief Constructeur du ProjectilesMegaBoss.
	 */
	ProjectilesMegaBoss();
	/**
	 * @brief destructeur du ProjectilesMegaBoss.
	 */
	~ProjectilesMegaBoss();
	/**
	 * @brief initialise le projectile
	 */
	void Init() override;
	/**
	 * @brief Met à jour l'état du ProjectilesMegaBoss.
	 * @param deltatime Temps écoulé depuis la dernière mise à jour.
	 */
	void Update(float deltatime)override;
	/**
	 * @brief Dessine le mégaboss à l'écran.
	 * @param window Fenêtre SFML dans laquelle dessiner.
	 */
	void Draw(sf::RenderWindow& window) override;
	/**
	 * @brief Bounds pour les collisions
	 */
	sf::FloatRect GetBounds() const;
	/**
	 * @brief change position player
	 * @param pointeur de player
	 */
	void setPlayer(Player* player);
	/**
	 * @brief change position MegaBoss
	 * @param pointeur de MegaBoss
	 */
	void setMegaBoss(MegaBoss* megaboss);
	/**
	 * @brief stock le pointeurs vers megaboss
	 * @param pointeur de megaboss
	 */
	void setTargetMegaBoss(MegaBoss* megaboss);
	/**
	 * @brief stock le pointeurs vers boss
	 * @param pointeur de Boss
	 */
	void setTargetBoss(Boss* boss);

	


public:
	/**
	 * @brief Mode Shoot
	 */
	void Shoot();
	/**
	 * @brief Mode Shoot Angry, en dessous de 100 PV, il active le mode angry
	 */
	void ShootAngry();
	/**
	 * @brief Mode Shoot sur le player
	 */
	void ShootToPlayer();
	/**
	 * @brief Mode Shoot sur le player en mode angry
	 */
	void ShootToPlayerAngry();

private:
	MegaBoss* m_megaboss;
	Boss* m_boss;
	Player* m_player;
	std::vector<sf::CircleShape> m_projectilesBoss;
	std::vector<sf::Vector2f> m_directions;
	float m_speed;

};

