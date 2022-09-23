#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	void update();
	void draw(sf::RenderWindow& m_window);
	void setupSprite();
	void movePlayer();
	void checkRotation();
	void checkMaxSpeed();
	void checkBoundaries();

	float m_maxSpeed = 5.0f;
	float speedValue = 2;


private:
	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite; 

	float speedIncrease = 0.5;
	float speedDecrease = 0.3;

	
	

};



