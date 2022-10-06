#include "FleeEnemy.h"

FleeEnemy::FleeEnemy()
{
	if (!m_fleeTexture.loadFromFile("ASSETS\\IMAGES\\shipFlee.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading seek ship" << std::endl;
	}

	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_fleeSprite.setTexture(m_fleeTexture);
	m_fleeSprite.setOrigin(16, 16);
	m_fleeSprite.setScale(3, 3);
	m_fleeSprite.setPosition(sf::VideoMode::getDesktopMode().width - 1000, sf::VideoMode::getDesktopMode().height - 600);
	m_fleeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	m_fleeText.setFont(m_font);
	m_fleeText.setString("Flee");
	m_fleeText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_fleeText.setPosition(m_fleeSprite.getPosition().x - 30, m_fleeText.getPosition().y);
	m_fleeText.setCharacterSize(20U);
	m_fleeText.setOutlineColor(sf::Color::Black);
	m_fleeText.setFillColor(sf::Color::White);
	m_fleeText.setOutlineThickness(3.0f);

	radius.setFillColor(sf::Color::Transparent);
	radius.setOutlineThickness(3);
	radius.setOutlineColor(sf::Color::Red);
	radius.setRadius(radiusF);
	radius.setPosition(m_fleeSprite.getPosition().x - radiusF, m_fleeSprite.getPosition().y - radiusF);

	LineToPlayer.clear();

	m_leftLine.setSize({ 200,1 });
	m_leftLine.setFillColor(sf::Color::Green);
	m_leftLine.setRotation(m_fleeSprite.getRotation() - 90 - angleOfSight);

	m_rightLine.setSize({ 200,1 });
	m_rightLine.setFillColor(sf::Color::Green);
	m_rightLine.setRotation(m_fleeSprite.getRotation() - 90 - angleOfSight);
}

void FleeEnemy::checkBoundaries()
{
	if (m_fleeSprite.getPosition().x > sf::VideoMode::getDesktopMode().width + m_fleeSprite.getGlobalBounds().width)
	{
		m_fleeSprite.setPosition(-m_fleeSprite.getGlobalBounds().width, m_fleeSprite.getPosition().y);
	}
	else if (m_fleeSprite.getPosition().x < -m_fleeSprite.getGlobalBounds().width)
	{
		m_fleeSprite.setPosition(sf::VideoMode::getDesktopMode().width + m_fleeSprite.getGlobalBounds().width, m_fleeSprite.getPosition().y);
	}


	if (m_fleeSprite.getPosition().y > sf::VideoMode::getDesktopMode().height + m_fleeSprite.getGlobalBounds().height)
	{
		m_fleeSprite.setPosition(m_fleeSprite.getPosition().x, -m_fleeSprite.getGlobalBounds().height);
	}
	else if (m_fleeSprite.getPosition().y < -m_fleeSprite.getGlobalBounds().height)
	{
		m_fleeSprite.setPosition(m_fleeSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_fleeSprite.getGlobalBounds().height);
	}
}

void FleeEnemy::draw(sf::RenderWindow& m_window)
{
	if (drawCharacter == true)
	{
		if (tracerAlive == true)
		{
			m_window.draw(radius);
			m_window.draw(LineToPlayer);
		}

		m_window.draw(m_fleeSprite);
		m_window.draw(m_fleeText);
		m_window.draw(m_leftLine);
		m_window.draw(m_rightLine);
	}
}

void FleeEnemy::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (drawCharacter == true)
	{
		kinematicFlee(t_deltaTime, t_player);
		checkBoundaries();
		radius.setPosition(m_fleeSprite.getPosition().x - radiusF, m_fleeSprite.getPosition().y - radiusF);
		m_fleeText.setPosition(m_fleeSprite.getPosition().x - 30, m_fleeSprite.getPosition().y);
		setVisionCone(t_player.m_playerSprite.getPosition());
	}
}

void FleeEnemy::kinematicFlee(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f playerPos = t_player.m_playerSprite.getPosition();
	sf::Vector2f currentPosition = m_fleeSprite.getPosition();

	vel = currentPosition - playerPos;
	distance = sqrtf(vel.x * vel.x + vel.y * vel.y);
	distanceVec = sf::Vector2f{ vel.x / distance , vel.y / distance };
	vel = distanceVec * maxSpeed;

	if (distance < radiusF)
	{
		std::cout << "Standing Still " << std::endl;
	}
	else
	{
		vel = vel / timeToTarget;

		if (distance > radiusF)
		{
			std::cout << "In large radius 22 " << std::endl;
			sf::Vector2f normalisedVelocity = { vel.x / distance ,vel.y / distance };
			vel = normalisedVelocity;
			vel = vel * maxSpeed;
		}
	}

	float dx = currentPosition.x - t_player.m_playerSprite.getPosition().x;
	float dy = currentPosition.y - t_player.m_playerSprite.getPosition().y;

	GetProperRot = (atan2(dy, dx)) * 180 / pi;
	rotation = GetProperRot + 90; // -270

	m_fleeSprite.setRotation(rotation);
	std::cout << "flee angle: " << rotation << std::endl;

	m_fleeSprite.move(vel);

	LineToPlayer.clear();
	sf::Vertex begin{ m_fleeSprite.getPosition(), sf::Color::Yellow };
	LineToPlayer.append(begin);
	sf::Vertex end{ playerPos, sf::Color::Yellow };
	LineToPlayer.append(end);
}

void FleeEnemy::setVisionCone(sf::Vector2f t_targetPos)
{
	m_leftLine.setRotation(m_fleeSprite.getRotation() - 90 - angleOfSight);
	m_leftLine.setPosition(m_fleeSprite.getPosition());

	m_rightLine.setRotation(m_fleeSprite.getRotation() - 90 + angleOfSight);
	m_rightLine.setPosition(m_fleeSprite.getPosition());

	sf::Vector2f orientation = { std::cos(m_calculateRadianAngle * m_fleeSprite.getRotation() - 90),std::sin(m_calculateRadianAngle * m_fleeSprite.getRotation() - 90) };
	sf::Vector2f distance = t_targetPos - m_fleeSprite.getPosition();
	distance = normalize(distance);

	float dotProduct = (orientation.x * distance.x) + (orientation.y * distance.y);


	if (dotProduct > std::cos(angleOfSight * 2))
	{
		if (sqrt((t_targetPos.x - m_fleeSprite.getPosition().x) * (t_targetPos.x - m_fleeSprite.getPosition().x) + (t_targetPos.y - m_fleeSprite.getPosition().y) * (t_targetPos.y - m_fleeSprite.getPosition().y)) <= 200.0f)
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

sf::Vector2f FleeEnemy::normalize(sf::Vector2f normVector)
{
	float length = sqrt((normVector.x * normVector.x) + (normVector.y * normVector.y));
	return { normVector.x / length, normVector.y / length };
}
