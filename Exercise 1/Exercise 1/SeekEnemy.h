#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <cmath>

class SeekEnemy
{
public:
	SeekEnemy();

	void checkBoundaries();
	void draw(sf::RenderWindow& m_window);

	
private:
	sf::Sprite m_seekSprite;
	sf::Texture m_seekTexture;

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Text seekText;
	sf::Font font;

	float angle = 0.0f;
	float pi = 3.141592653589793238f;
	float speed = 2.0f;
	float maxSpeed = 4.0f;
	float distance;
	float timeToTarget = 0.25f;
	float GetProperRot;
	float rotation;
	sf::Vector2f distanceVec;
	sf::Vector2f vel;

};