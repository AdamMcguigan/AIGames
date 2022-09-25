#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	Player();

	void setupSprite();
	void movePlayer(sf::Time& t_deltaTime);
	void checkBoundaries();
	void CheckForInput();
	void update(sf::Time& t_deltaTime);
	void draw(sf::RenderWindow& m_window);

	sf::CircleShape radius;
	float radiusF = 100.0f;

private:
	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;

	const float MAX_SPEED = 15.0f;
	const float SPEED_INCREASE = 0.5f;
	const float ROTATION_SPEED = 4.0f;

	float m_calculateRadianAngle = 3.1415926536 / 180;
	float m_speed = 3.0f;
	float m_rotation = 0.0f;

	sf::Vector2f m_velocity = { 0,0 };

};



