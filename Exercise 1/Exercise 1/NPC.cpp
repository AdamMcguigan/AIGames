#include "NPC.h"

void NPC::update()
{
	checkBoundaries();
	moveNpc();
}

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

void NPC::checkBoundaries()
{
	if (m_npcSprite.getPosition().x > 1920)
	{
		m_npcSprite.setPosition(20.0f, 600.0f);
	}

	if (m_npcSprite.getPosition().x < 0)
	{
		m_npcSprite.setPosition(1920.0f, 600.0f);
	}
}

float NPC::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity > 0)
	{
		return atan2(m_npcSprite.getPosition().y, m_npcSprite.getPosition().x);
	}
	else
	{
		return currentOrientation;

	}

}

void NPC::wander()
{

}
