#include "Player.h"


void Player::setupSprite()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\chicken.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(500.0f, 300.0f);
}

void Player::movePlayer()
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		speedValue += speedIncrease;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		speedValue -= speedDecrease;
	}

	m_playerSprite.move(speedValue, 0);
}

void Player::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_playerSprite);
}
