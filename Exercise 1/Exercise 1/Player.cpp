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
	m_playerSprite.move(2.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity.x += 0.5f;
		m_playerSprite.move(m_velocity);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.x -= 0.5f;
		m_playerSprite.move(2, 0);
	}
}

void Player::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_playerSprite);
}
