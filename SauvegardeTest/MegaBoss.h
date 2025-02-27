#pragma once
#include "IGameObjects.h"
#include "Player.h"


class Projectiles;

class MegaBoss : public IGameObject
{
public:
	MegaBoss();
	~MegaBoss();
	void Init() override;
	void Update(float deltatime) override;
	void Draw(sf::RenderWindow& window) override;
	sf::FloatRect GetBounds() const;

public:
	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& pos);

public:
	void SetPlayer(Player* player);

public:
	int getPV() const;
	void setPV(int PV);
	void takeDamage(int damagenmbr);
	bool isDead() const;

private:
	sf::RectangleShape m_megaboss;
	sf::Vector2f m_position;
	Player* m_player;
	float m_speed;
	int m_PV;
};