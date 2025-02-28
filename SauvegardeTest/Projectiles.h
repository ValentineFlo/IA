#pragma once
#include "IGameObjects.h"
#include "Player.h"
#include "Boss.h"
#include "MegaBoss.h"
#include <vector>


class Projectiles : public IGameObject
{
public:
	Projectiles();
	~Projectiles() = default;
	void Init() override;
	void Update(float deltatime)override;
	void Draw(sf::RenderWindow& window) override;
	sf::FloatRect GetBounds() const;

	void setPlayer(Player* player);
	void setTargetMegaBoss(MegaBoss* megaboss);
	void setTargetBoss(Boss* boss);

public:
	void Shoot();
	void ShootBoss();
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
	ProjectilesMegaBoss();
	~ProjectilesMegaBoss() = default;
	void Init() override;
	void Update(float deltatime)override;
	void Draw(sf::RenderWindow& window) override;
	sf::FloatRect GetBounds() const;

	void setPlayer(Player* player);
	void setMegaBoss(MegaBoss* megaboss);

	void setTargetMegaBoss(MegaBoss* megaboss);
	void setTargetBoss(Boss* boss);

	


public:
	void Shoot();
	void ShootToPlayer();

private:
	MegaBoss* m_megaboss;
	Boss* m_boss;
	Player* m_player;
	std::vector<sf::CircleShape> m_projectilesBoss;
	std::vector<sf::Vector2f> m_directions;
	float m_speed;
};

