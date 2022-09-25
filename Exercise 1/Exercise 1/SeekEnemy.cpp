#include "SeekEnemy.h"

SeekEnemy::SeekEnemy()
{
	if (!m_seekTexture.loadFromFile("ASSETS\\IMAGES\\SeekShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading seek ship" << std::endl;
	}
	m_seekSprite.setTexture(m_seekTexture);
	m_seekSprite.setScale(3, 3);
	m_seekSprite.setOrigin(m_seekSprite.getGlobalBounds().width / 2, m_seekSprite.getGlobalBounds().height / 2);
	m_seekSprite.setPosition(sf::VideoMode::getDesktopMode().width - 100, sf::VideoMode::getDesktopMode().height - 400);
}

void SeekEnemy::checkBoundaries()
{
	if (m_seekSprite.getPosition().x > sf::VideoMode::getDesktopMode().width + m_seekSprite.getGlobalBounds().width)
	{
		m_seekSprite.setPosition(-m_seekSprite.getGlobalBounds().width, m_seekSprite.getPosition().y);
	}
	else if (m_seekSprite.getPosition().x < -m_seekSprite.getGlobalBounds().width)
	{
		m_seekSprite.setPosition(sf::VideoMode::getDesktopMode().width + m_seekSprite.getGlobalBounds().width, m_seekSprite.getPosition().y);
	}


	if (m_seekSprite.getPosition().y > sf::VideoMode::getDesktopMode().height + m_seekSprite.getGlobalBounds().height)
	{
		m_seekSprite.setPosition(m_seekSprite.getPosition().x, -m_seekSprite.getGlobalBounds().height);
	}
	else if (m_seekSprite.getPosition().y < -m_seekSprite.getGlobalBounds().height)
	{
		m_seekSprite.setPosition(m_seekSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_seekSprite.getGlobalBounds().height);
	}
}


void SeekEnemy::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_seekSprite);
}



