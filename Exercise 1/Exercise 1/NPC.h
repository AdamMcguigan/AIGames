#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <cmath>

class NPC
{
public:
	void update(sf::Time& t_deltaTime);
	void draw(sf::RenderWindow& m_window);
	void setupSprite();
	void checkBoundaries();
	void wander(sf::Time& t_deltaTime);
	void randomWanderRadius();

	float radius = 100.0f;

	sf::VertexArray WanderLine{ sf::Lines };
	sf::Vector2f linePoint;

private:
	sf::Sprite m_npcSprite; 
	sf::Texture m_npcTexture;
	float angle = 0.0f;
	float m_rotation = 0.0f;
	float m_speed = 3.0f;
	float angleInRads = 0;
	float pi = 3.141592653589793238f;
	int randomInt = 0;

	sf::Text m_wanderText;
	sf::Font m_font;

	sf::Vector2f m_target = { 0,0 };
	sf::Vector2f m_velocity = { 0,0 };
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 2 };

};
