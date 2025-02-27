#include "IGameObjects.h"
	
	
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
	int getPV() const;
	void setPV(int PV);
	void takeDamage(int damagenmbr);
	bool isDead() const;

private:
	sf::RectangleShape m_megaboss;
	sf::Vector2f m_position;
	float m_speed;
	int m_PV;
};