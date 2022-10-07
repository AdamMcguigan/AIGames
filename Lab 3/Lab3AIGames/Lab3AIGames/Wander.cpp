#include "Wander.h"

Wander::Wander()
{
	setupSprite();
}

void Wander::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (canUpdate == true)
	{
		randomWanderRadius();
		wander(t_deltaTime);
		checkBoundaries();
		setVisionCone(t_player.m_playerSprite.getPosition());

		m_wanderText.setPosition(m_npcSprite.getPosition().x - 30, m_npcSprite.getPosition().y);

		WanderLine.clear();
		sf::Vertex begin{ m_npcSprite.getPosition(),sf::Color::Cyan };
		WanderLine.append(begin);
		sf::Vertex end{ linePoint, sf::Color::Yellow };
		WanderLine.append(end);

	}
}

void Wander::draw(sf::RenderWindow& m_window)
{
	if (canUpdate == true)
	{
		if (drawTracer == true)
		{
			m_window.draw(WanderLine);
		}
		m_window.draw(m_npcSprite);
		m_window.draw(m_wanderText);
		m_window.draw(m_leftLine);
		m_window.draw(m_rightLine);
	}
}

void Wander::setupSprite()
{
	if (!m_npcTexture.loadFromFile("ASSETS\\IMAGES\\WanderShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_npcSprite.setTexture(m_npcTexture);
	m_npcSprite.setRotation(m_rotation);
	m_npcSprite.setScale(3, 3);
	m_npcSprite.setOrigin(16, 16);
	m_npcSprite.setPosition(m_pos);

	m_wanderText.setFont(m_font);
	m_wanderText.setString("Wander");
	m_wanderText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_wanderText.setPosition(m_npcSprite.getPosition());
	m_wanderText.setCharacterSize(20U);
	m_wanderText.setOutlineColor(sf::Color::Black);
	m_wanderText.setFillColor(sf::Color::White);
	m_wanderText.setOutlineThickness(3.0f);

	m_leftLine.setSize({ 200,1 });
	m_leftLine.setFillColor(sf::Color::Green);
	m_leftLine.setRotation(m_npcSprite.getRotation());

	m_rightLine.setSize({ 200,1 });
	m_rightLine.setFillColor(sf::Color::Green);
	m_rightLine.setRotation(m_npcSprite.getRotation());
}


void Wander::checkBoundaries()
{
	if (m_npcSprite.getPosition().x > sf::VideoMode::getDesktopMode().width + m_npcSprite.getGlobalBounds().width)
	{
		m_npcSprite.setPosition(-m_npcSprite.getGlobalBounds().width, m_npcSprite.getPosition().y);
	}
	else if (m_npcSprite.getPosition().x < -m_npcSprite.getGlobalBounds().width)
	{
		m_npcSprite.setPosition(sf::VideoMode::getDesktopMode().width + m_npcSprite.getGlobalBounds().width, m_npcSprite.getPosition().y);
	}


	if (m_npcSprite.getPosition().y > sf::VideoMode::getDesktopMode().height + m_npcSprite.getGlobalBounds().height)
	{
		m_npcSprite.setPosition(m_npcSprite.getPosition().x, -m_npcSprite.getGlobalBounds().height);
	}
	else if (m_npcSprite.getPosition().y < -m_npcSprite.getGlobalBounds().height)
	{
		m_npcSprite.setPosition(m_npcSprite.getPosition().x, sf::VideoMode::getDesktopMode().height + m_npcSprite.getGlobalBounds().height);
	}
}

void Wander::wander(sf::Time& t_deltaTime)
{
	angle = m_npcSprite.getRotation();
	angle = angle + wanderOffset;

	//Resetting the angle 
	if (angle == 360.0)
	{
		angle = 0;
	}
	if (angle == 0.0)
	{
		angle = 359.0;
	}


	angleInRads = (angle - 90) * pi / 180;
	linePoint.x = m_npcSprite.getPosition().x + radius * cos(angleInRads);
	linePoint.y = m_npcSprite.getPosition().y + radius * sin(angleInRads);

	//will rotate the wander left and right.
	m_velocity.x = m_speed * sin(angle * t_deltaTime.asMilliseconds() / 1000);
	m_velocity.y = m_speed * -cos(angle * t_deltaTime.asMilliseconds() / 1000);

	//grabbing the normalised velocity
	float squareAns = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	sf::Vector2f normalisedVelocity = m_velocity / squareAns;

	m_npcSprite.setRotation(angle);
	m_npcSprite.move(m_velocity);

}

void Wander::randomWanderRadius()
{
	wanderOffset = rand() % (3 + 3) + -3; //random number between -1 to 1 ;
}

void Wander::setVisionCone(sf::Vector2f t_targetPos)
{
	m_leftLine.setRotation(m_npcSprite.getRotation() - 90 - angleOfSight);
	m_leftLine.setPosition(m_npcSprite.getPosition());

	m_rightLine.setRotation(m_npcSprite.getRotation() - 90 + angleOfSight);
	m_rightLine.setPosition(m_npcSprite.getPosition());

	sf::Vector2f orientation = { std::cos(m_calculateRadianAngle * m_npcSprite.getRotation() - 90),std::sin(m_calculateRadianAngle * m_npcSprite.getRotation() - 90) };
	sf::Vector2f distance = t_targetPos - m_npcSprite.getPosition();
	distance = normalize(distance);

	float dotProduct = (orientation.x * distance.x) + (orientation.y * distance.y);


	if (dotProduct > std::cos(angleOfSight * 2))
	{
		if (sqrt((t_targetPos.x - m_npcSprite.getPosition().x) * (t_targetPos.x - m_npcSprite.getPosition().x) + (t_targetPos.y - m_npcSprite.getPosition().y) * (t_targetPos.y - m_npcSprite.getPosition().y)) <= 200.0f)
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

sf::Vector2f Wander::normalize(sf::Vector2f normVector)
{
	float length = sqrt((normVector.x * normVector.x) + (normVector.y * normVector.y));
	return { normVector.x / length, normVector.y / length };
}

