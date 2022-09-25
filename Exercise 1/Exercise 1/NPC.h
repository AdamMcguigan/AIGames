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

private:
	sf::Sprite m_npcSprite; 
	sf::Texture m_npcTexture;
	float angle = 0.0f;
	float m_rotation = 0.0f;
	float m_speed = 3.0f;
	int randomInt = 0;

	sf::Text m_wanderText;
	sf::Font m_font;

	sf::Vector2f m_target = { 0,0 };
	sf::Vector2f m_velocity = { 0,0 };
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 2 };

};
