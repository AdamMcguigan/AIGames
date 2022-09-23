#include <iostream>
#include <SFML/Graphics.hpp>

class NPC
{
public:
	void update();
	void draw(sf::RenderWindow& m_window);
	void setupSprite();

	void moveNpc();
	void checkBoundaries();

	float getNewOrientation(float currentOrientation, float velocity);
	void wander();
	sf::Sprite m_npcSprite; 
	float m_velocity = 0.0f;

private:
	sf::Texture m_npcTexture;
	int speedValue = 3;
};
