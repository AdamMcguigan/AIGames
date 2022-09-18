#include "NPC.h"

void NPC::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_npcSprite);
}

void NPC::setupSprite()
{
	if (!m_npcTexture.loadFromFile("ASSETS\\IMAGES\\crocodile.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_npcSprite.setTexture(m_npcTexture);
	m_npcSprite.setPosition(50.0f, 600.0f);
}

void NPC::moveNpc()
{
	m_npcSprite.move(speedValue, 0);
}
