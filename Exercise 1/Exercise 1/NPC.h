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
	//void wander();
	float m_velocity = 0.0f;

private:
	sf::Sprite m_npcSprite; 
	sf::Texture m_npcTexture;

	int speedValue = 3;
};
