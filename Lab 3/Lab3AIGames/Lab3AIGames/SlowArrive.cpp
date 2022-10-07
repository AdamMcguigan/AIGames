#include "SlowArrive.h"

SlowArrive::SlowArrive()
{
	setupSprites();
}

void SlowArrive::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (canUpdate == true)
	{
		seek(t_deltaTime, t_player);
		arriveSlowText.setPosition(m_arrvieSprite.getPosition());
		setVisionCone(t_player.m_playerSprite.getPosition());
	}
}

void SlowArrive::draw(sf::RenderWindow& t_window)
{
	if (canUpdate == true)
	{
		if (drawTracer == true)
		{
			t_window.draw(LineToPlayer);
		}
		t_window.draw(m_arrvieSprite);
		t_window.draw(arriveSlowText);
		t_window.draw(m_leftLine);
		t_window.draw(m_rightLine);
	}
}


void SlowArrive::setVisionCone(sf::Vector2f t_targetPos)
{
	m_leftLine.setRotation(m_arrvieSprite.getRotation() - 90 - angleOfSight);
	m_leftLine.setPosition(m_arrvieSprite.getPosition());

	m_rightLine.setRotation(m_arrvieSprite.getRotation() - 90 + angleOfSight);
	m_rightLine.setPosition(m_arrvieSprite.getPosition());

	sf::Vector2f orientation = { std::cos(m_calculateRadianAngle * m_arrvieSprite.getRotation() - 90),std::sin(m_calculateRadianAngle * m_arrvieSprite.getRotation() - 90) };
	sf::Vector2f distance = t_targetPos - m_arrvieSprite.getPosition();
	distance = normalize(distance);

	float dotProduct = (orientation.x * distance.x) + (orientation.y * distance.y);


	if (dotProduct > std::cos(angleOfSight * 2))
	{
		if (sqrt((t_targetPos.x - m_arrvieSprite.getPosition().x) * (t_targetPos.x - m_arrvieSprite.getPosition().x) + (t_targetPos.y - m_arrvieSprite.getPosition().y) * (t_targetPos.y - m_arrvieSprite.getPosition().y)) <= 200.0f)
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

sf::Vector2f SlowArrive::normalize(sf::Vector2f normVector)
{
	float length = sqrt((normVector.x * normVector.x) + (normVector.y * normVector.y));
	return { normVector.x / length, normVector.y / length };
}

void SlowArrive::setupSprites()
{
	if (!m_arrvieTexture.loadFromFile("ASSETS\\IMAGES\\ArriveFast.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Fast Arrive" << std::endl;
	}
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	m_arrvieSprite.setTexture(m_arrvieTexture);
	m_arrvieSprite.setPosition(sf::VideoMode::getDesktopMode().width - 50, sf::VideoMode::getDesktopMode().height - 250);
	m_arrvieSprite.scale(3.0f, 3.0f);
	m_arrvieSprite.rotate(angle);
	m_arrvieSprite.setOrigin(16, 16);

	arriveSlowText.setFont(m_font);
	arriveSlowText.setString("Slow Arrive");
	arriveSlowText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	arriveSlowText.setPosition(m_arrvieSprite.getPosition().x - 30, m_arrvieSprite.getPosition().y);
	arriveSlowText.setCharacterSize(20U);
	arriveSlowText.setOutlineColor(sf::Color::Black);
	arriveSlowText.setFillColor(sf::Color::White);
	arriveSlowText.setOutlineThickness(3.0f);

	m_leftLine.setSize({ 200,1 });
	m_leftLine.setFillColor(sf::Color::Green);
	m_leftLine.setRotation(m_arrvieSprite.getRotation());

	m_rightLine.setSize({ 200,1 });
	m_rightLine.setFillColor(sf::Color::Green);
	m_rightLine.setRotation(m_arrvieSprite.getRotation());
}

//Slow Arrive
void SlowArrive::seek(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f playerPos = t_player.m_playerSprite.getPosition();
	sf::Vector2f currentPosition = m_arrvieSprite.getPosition();

	velDistance = playerPos - currentPosition;
	distance = sqrtf(velDistance.x * velDistance.x + velDistance.y * velDistance.y);
	distanceVec = sf::Vector2f{ velDistance.x / distance , velDistance.y / distance };
	velDistance = distanceVec * maxSpeed;

	//if the distance is greater than the outer player radius
	if (distance > t_player.radiusF)
	{
		std::cout << "Seeking the player - Slow Arrive " << std::endl;
	}
	else
	{
		velDistance = velDistance / timeToTarget; //works in the inner circle

		//setting the velocity to travel to player
		if (distance > maxSpeed)
		{
			sf::Vector2f normalisedVelocity = { velDistance.x / distance ,velDistance.y / distance };
			velDistance = normalisedVelocity;
			velDistance = velDistance * maxSpeed * 2.0f;
		}

		//Stopping the enemy when on the player sprite
		if (distance < t_player.smallRadius)
		{
			velDistance = { 0.0f,0.0f };
		}
	}

	//distance between current sprite pos and the player pos
	float dx = currentPosition.x - t_player.m_playerSprite.getPosition().x;
	float dy = currentPosition.y - t_player.m_playerSprite.getPosition().y;

	//Angle in degress
	GetProperRot = (atan2(dy, dx)) * 180 / pi;
	rotation = GetProperRot - 90;

	m_arrvieSprite.setRotation(rotation);
	m_arrvieSprite.move(velDistance);

	//Drawing Lines to player
	LineToPlayer.clear();
	sf::Vertex begin{ m_arrvieSprite.getPosition(), sf::Color::Transparent };
	LineToPlayer.append(begin);
	sf::Vertex end{ playerPos, sf::Color::Red };
	LineToPlayer.append(end);
}