#include "Player.h"


void Player::setupSprite()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\ship_0014.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_playerSprite.setScale(3, 3);
	m_playerSprite.setRotation(90);
	m_playerSprite.setOrigin(16, 16);
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

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_playerSprite.move(-speedValue, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_playerSprite.move(speedValue, 0);
	}*/

	checkMaxSpeed();
	checkRotation();

	m_playerSprite.move(speedValue, 0);
}

void Player::checkRotation()
{
	if (speedValue < 0)
	{
		m_playerSprite.setRotation(-90);
	}
	if (speedValue > 0)
	{
		m_playerSprite.setRotation(90);
	}
}

void Player::checkMaxSpeed()
{
	//checking if speed is greater than maxSpeed
	if (speedValue > m_maxSpeed)
	{
		speedValue = m_maxSpeed;
	}

	if (speedValue < -m_maxSpeed)
	{
		speedValue = -m_maxSpeed;
	}
}

void Player::checkBoundaries()
{
	if (m_playerSprite.getPosition().x > 1920)
	{
		m_playerSprite.setPosition(20.0f, 300.0f);
	}

	if (m_playerSprite.getPosition().x < 0)
	{
		m_playerSprite.setPosition(1920.0f, 300.0f);
	}
}

void Player::update()
{
	movePlayer();
	checkBoundaries();
}

void Player::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_playerSprite);
}
