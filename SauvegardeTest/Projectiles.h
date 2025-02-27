#pragma once
#include "IGameObjects.h"
#include "Player.h"
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

	void SetPlayer(Player* player) 
	{
		m_player = player;
	}

public:
	void Shoot();

private:
	std::vector<sf::CircleShape> m_projectiles;
	float m_speed;
	Player* m_player;
};

