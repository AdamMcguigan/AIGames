#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& m_window);
	void setupSprite();
	void movePlayer();

	float m_maxSpeed = 5.0f;
	float speedValue = 2;

	sf::Texture m_playerTexture; // Should be private, just want to setup boundary checks without creating 'Getter' methods
	sf::Sprite m_playerSprite; // Should be private, just want to setup boundary checks without creating 'Getter' methods

private:
	float speedIncrease = 0.5;
	float speedDecrease = 0.3;

	
	

};



