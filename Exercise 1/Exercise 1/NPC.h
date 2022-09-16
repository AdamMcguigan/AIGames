#include <iostream>
#include <SFML/Graphics.hpp>

class NPC
{
public:
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& m_window);
	void setupSprite();
	void moveNpc();

private:
	sf::Texture m_npcTexture; // texture used for sfml logo
	sf::Sprite m_npcSprite; // sprite used for sfml logo
};
