#include "Player.h"


Player::Player()
{
	setupSprite();
}

void Player::setupSprite()
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\ship_00141.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_playerSprite.setScale(3, 3);
	m_playerSprite.setOrigin(16, 16);
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_playerSprite.setPosition(500.0f, 300.0f);

	radius.setFillColor(sf::Color{ 107, 217, 231, 70 });
	radius.setRadius(radiusF);
	radius.setPosition(m_playerSprite.getPosition().x - radiusF, m_playerSprite.getPosition().y - radiusF);

	smallCircle.setFillColor(sf::Color{ 121, 1, 231, 70 });
	smallCircle.setRadius(smallRadius);
	smallCircle.setPosition(m_playerSprite.getPosition().x - smallRadius, m_playerSprite.getPosition().y - smallRadius);

	pursueCircle.setFillColor(sf::Color{ 197, 85, 226, 80 });
	pursueCircle.setRadius(pursueCircleRadius);
}

////// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 

void Player::movePlayer(sf::Time& t_deltaTime)
{
	m_playerSprite.setRotation(m_rotation);
	m_velocity.x = cos(m_calculateRadianAngle * (m_playerSprite.getRotation())) * m_speed;
	m_velocity.y = sin(m_calculateRadianAngle * (m_playerSprite.getRotation())) * m_speed;

	pursuePoint.x = m_playerSprite.getPosition().x + radiusF * m_velocity.x;
	pursuePoint.y = m_playerSprite.getPosition().y + radiusF * m_velocity.y;

	m_playerSprite.setPosition(m_playerSprite.getPosition() + m_velocity);
	radius.setPosition(m_playerSprite.getPosition().x - radiusF, m_playerSprite.getPosition().y - radiusF);
	smallCircle.setPosition(m_playerSprite.getPosition().x - smallRadius, m_playerSprite.getPosition().y - smallRadius);

	pursueCircle.setOrigin(0, 0);
	pursueCircle.setPosition(pursuePoint.x - pursueCircleRadius, pursuePoint.y - pursueCircleRadius);
}

////// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 

void Player::checkBoundaries()
{
	if (m_playerSprite.getPosition().x > sf::VideoMode::getDesktopMode().width + m_playerSprite.getGlobalBounds().width)
	{
		m_playerSprite.setPosition(-m_playerSprite.getGlobalBounds().width, m_playerSprite.getPosition().y);
	}
	else if (m_playerSprite.getPosition().x < -m_playerSprite.getGlobalBounds().width)
	{
		m_playerSprite.setPosition(sf::VideoMode::getDesktopMode().width + m_playerSprite.getGlobalBounds().width, m_playerSprite.getPosition().y);
	}


	if (m_playerSprite.getPosition().y > sf::VideoMode::getDesktopMode().height + m_playerSprite.getGlobalBounds().height)
	{
		m_playerSprite.setPosition(m_playerSprite.getPosition().x, -m_playerSprite.getGlobalBounds().height);
	}
	else if (m_playerSprite.getPosition().y < -m_playerSprite.getGlobalBounds().height)
	{
		m_playerSprite.setPosition(m_playerSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_playerSprite.getGlobalBounds().height);
	}

}

////// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 

void Player::CheckForInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_speed < MAX_SPEED)
		{
			m_speed += SPEED_INCREASE;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_speed >= SPEED_INCREASE)
		{
			m_speed -= SPEED_INCREASE;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= ROTATION_SPEED;
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += ROTATION_SPEED;
	}

}

////// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 

void Player::update(sf::Time& t_deltaTime)
{
	checkBoundaries();
	movePlayer(t_deltaTime);

	playerLine.clear();
	sf::Vertex begin{ m_playerSprite.getPosition(),sf::Color::Green };
	playerLine.append(begin);
	sf::Vertex end{ pursuePoint, sf::Color::Green };
	playerLine.append(end);

}

////// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 

void Player::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_playerSprite);

	if (drawDebugLines == true)
	{
		m_window.draw(radius);
		m_window.draw(smallCircle);
		m_window.draw(pursueCircle);
		m_window.draw(playerLine);
		
	}
}

sf::Vector2f Player::PlayerPos()
{
	return m_playerSprite.getPosition();
}

