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

	sf::Sprite m_npcSprite; 

private:
	sf::Texture m_npcTexture;
	int speedValue = 3;
};
