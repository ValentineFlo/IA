#pragma once
#include "IGameObjects.h"
#include "Player.h"
#include "Tree.h"


class Projectiles;
class ProjectilesMegaBoss;

class MegaBoss : public IGameObject
{
public:
	MegaBoss();
	~MegaBoss();
	void Init() override {};
	void Update(float deltatime) override;
	void Draw(sf::RenderWindow& window) override;
	sf::FloatRect GetBounds() const;

public:
	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& pos);

public:
	void setPlayer(Player* player);
	void setProjectiles(ProjectilesMegaBoss* projectiles);

public:
	//Behavior tree
	bool isPlayerDetect();
	void Idle();
	void Patrol();
	void Shoot();
	void SpecialAttack();

public:
	int getPV() const;
	void setPV(int PV);
	void takeDamage(int damagenmbr);
	bool isDead() const;

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
	const float m_maxCounterShootBoss = 1.0f;
	bool m_isIdle = false;
	float m_counterIdle = 0.0f;
	const float m_maxCounterIdle = 2.0f;

	bool m_isAngry = false;
	const float m_angryPVLimit = 100.0f;
	float m_angrySpeed = 2.0f;
	float m_angrySpeedShoot = 0.5f; 
	float m_angryDamage = 2.0f;

	float m_counterShootBossAngry = 0.0f;
	float m_maxCounterShootBossAngry = 1.8f;
};