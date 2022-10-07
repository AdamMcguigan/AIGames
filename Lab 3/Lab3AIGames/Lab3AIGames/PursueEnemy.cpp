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

	m_leftLine.setSize({ 200,1 });
	m_leftLine.setFillColor(sf::Color::Green);
	m_leftLine.setRotation(m_pursueSprite.getRotation() - 90 - angleOfSight);

	m_rightLine.setSize({ 200,1 });
	m_rightLine.setFillColor(sf::Color::Green);
	m_rightLine.setRotation(m_pursueSprite.getRotation() - 90 - angleOfSight);
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
		m_window.draw(m_leftLine);
		m_window.draw(m_rightLine);
	}

}

void PursueEnemy::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (canUpdate == true)
	{
		pursue(t_deltaTime, t_player);
		m_pursueText.setPosition(m_pursueSprite.getPosition().x - 30, m_pursueSprite.getPosition().y);
		setVisionCone(t_player.m_playerSprite.getPosition());
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

	float dX = pursueSpritePos.x - pursuePointPos.x; //distance between the endPoint at the circle and the pursue sprite
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

void PursueEnemy::setVisionCone(sf::Vector2f t_targetPos)
{
	m_leftLine.setRotation(m_pursueSprite.getRotation() - 90 - angleOfSight);
	m_leftLine.setPosition(m_pursueSprite.getPosition());

	m_rightLine.setRotation(m_pursueSprite.getRotation() - 90 + angleOfSight);
	m_rightLine.setPosition(m_pursueSprite.getPosition());

	sf::Vector2f orientation = { std::cos(m_calculateRadianAngle * m_pursueSprite.getRotation() - 90),std::sin(m_calculateRadianAngle * m_pursueSprite.getRotation() - 90) };
	sf::Vector2f distance = t_targetPos - m_pursueSprite.getPosition();
	distance = normalize(distance);

	float dotProduct = (orientation.x * distance.x) + (orientation.y * distance.y);


	if (dotProduct > std::cos(angleOfSight * 2))
	{
		if (sqrt((t_targetPos.x - m_pursueSprite.getPosition().x) * (t_targetPos.x - m_pursueSprite.getPosition().x) + (t_targetPos.y - m_pursueSprite.getPosition().y) * (t_targetPos.y - m_pursueSprite.getPosition().y)) <= 200.0f)
		{
			m_leftLine.setFillColor(sf::Color::Red);
			m_rightLine.setFillColor(sf::Color::Red);
		}

		else
		{
			m_leftLine.setFillColor(sf::Color::Green);
			m_rightLine.setFillColor(sf::Color::Green);
		}
	}
	else
	{
		m_leftLine.setFillColor(sf::Color::Green);
		m_rightLine.setFillColor(sf::Color::Green);
	}
}

sf::Vector2f PursueEnemy::normalize(sf::Vector2f normVector)
{
	float length = sqrt((normVector.x * normVector.x) + (normVector.y * normVector.y));
	return { normVector.x / length, normVector.y / length };
}
