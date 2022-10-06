#include "PursueEnemy.h"

PursueEnemy::PursueEnemy()
{
	if (!m_pursueTexture.loadFromFile("ASSETS\\IMAGES\\pursueShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading pursue ship" << std::endl;
	}

	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_pursueSprite.setTexture(m_pursueTexture);
	m_pursueSprite.setScale(3, 3);
	m_pursueSprite.rotate(angle);
	m_pursueSprite.setOrigin(16, 16);
	m_pursueSprite.setPosition(sf::VideoMode::getDesktopMode().width - 20, sf::VideoMode::getDesktopMode().height - 50);
	m_pursueSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	m_pursueText.setFont(m_font);
	m_pursueText.setString("Pursue");
	m_pursueText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_pursueText.setPosition(m_pursueSprite.getPosition().x - 30, m_pursueSprite.getPosition().y);
	m_pursueText.setCharacterSize(20U);
	m_pursueText.setOutlineColor(sf::Color::Black);
	m_pursueText.setFillColor(sf::Color::White);
	m_pursueText.setOutlineThickness(3.0f);
}

void PursueEnemy::checkBoundaries()
{
	if (m_pursueSprite.getPosition().x > sf::VideoMode::getDesktopMode().width + m_pursueSprite.getGlobalBounds().width)
	{
		m_pursueSprite.setPosition(-m_pursueSprite.getGlobalBounds().width, m_pursueSprite.getPosition().y);
	}
	else if (m_pursueSprite.getPosition().x < -m_pursueSprite.getGlobalBounds().width)
	{
		m_pursueSprite.setPosition(sf::VideoMode::getDesktopMode().width + m_pursueSprite.getGlobalBounds().width, m_pursueSprite.getPosition().y);
	}


	if (m_pursueSprite.getPosition().y > sf::VideoMode::getDesktopMode().height + m_pursueSprite.getGlobalBounds().height)
	{
		m_pursueSprite.setPosition(m_pursueSprite.getPosition().x, -m_pursueSprite.getGlobalBounds().height);
	}
	else if (m_pursueSprite.getPosition().y < -m_pursueSprite.getGlobalBounds().height)
	{
		m_pursueSprite.setPosition(m_pursueSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_pursueSprite.getGlobalBounds().height);
	}
}

void PursueEnemy::draw(sf::RenderWindow& m_window)
{
	if (canUpdate == true)
	{
		if (drawTracer == true)
		{
			m_window.draw(LineToPlayer);
		}
		m_window.draw(m_pursueSprite);
		m_window.draw(m_pursueText);
	}

}

void PursueEnemy::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (canUpdate == true)
	{
		pursue(t_deltaTime, t_player);
		m_pursueText.setPosition(m_pursueSprite.getPosition().x - 30, m_pursueSprite.getPosition().y);
		
	}
}

void PursueEnemy::pursue(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f pursuePointPos = {t_player.pursuePoint.x, t_player.pursuePoint.y};
	sf::Vector2f pursueSpritePos = m_pursueSprite.getPosition();

	velocity = pursuePointPos - pursueSpritePos;

	distance = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
	distanceVec = sf::Vector2f{ velocity.x / distance, velocity.y / distance };
	vel = distanceVec * maxSpeed;

	float dX = pursueSpritePos.x - pursuePointPos.x;
	float dY = pursueSpritePos.y - pursuePointPos.y;

	ActualRotation = (atan2(dY, dX)) * 180 / pi;
	rotation = ActualRotation - 90;

	m_pursueSprite.setRotation(rotation);
	m_pursueSprite.move(vel);

	//Drawing line to player
	LineToPlayer.clear();
	sf::Vertex begin{ pursueSpritePos,sf::Color::Transparent };
	LineToPlayer.append(begin);
	sf::Vertex end{ pursuePointPos, sf::Color::Red };
	LineToPlayer.append(end);
}
