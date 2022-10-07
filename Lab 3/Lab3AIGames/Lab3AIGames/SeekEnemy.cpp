#include "SeekEnemy.h"

SeekEnemy::SeekEnemy()
{
	if (!m_seekTexture.loadFromFile("ASSETS\\IMAGES\\SeekShip.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading seek ship" << std::endl;
	}

	if (!font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_seekSprite.setTexture(m_seekTexture);
	m_seekSprite.setScale(3, 3);
	m_seekSprite.rotate(angle);
	m_seekSprite.setOrigin(16, 16);
	m_seekSprite.setPosition(sf::VideoMode::getDesktopMode().width - 100, sf::VideoMode::getDesktopMode().height - 400);
	m_seekSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	seekText.setFont(font);
	seekText.setString("Seek");
	seekText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	seekText.setPosition(m_seekSprite.getPosition().x - 30, m_seekSprite.getPosition().y);
	seekText.setCharacterSize(20U);
	seekText.setOutlineColor(sf::Color::Black);
	seekText.setFillColor(sf::Color::White);
	seekText.setOutlineThickness(3.0f);

	m_leftLine.setSize({ 200,1 });
	m_leftLine.setFillColor(sf::Color::Green);
	m_leftLine.setRotation(m_seekSprite.getRotation() - 90 - angleOfSight);

	m_rightLine.setSize({ 200,1 });
	m_rightLine.setFillColor(sf::Color::Green);
	m_rightLine.setRotation(m_seekSprite.getRotation() - 90 - angleOfSight);
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
	if (canUpdate == true)
	{
		if (drawTracer == true)
		{
			m_window.draw(LineToPlayer);
		}
		m_window.draw(m_seekSprite);
		m_window.draw(seekText);
		m_window.draw(m_leftLine);
		m_window.draw(m_rightLine);
	}
}

void SeekEnemy::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (canUpdate == true)
	{
		seek(t_deltaTime, t_player);
		seekText.setPosition(m_seekSprite.getPosition().x - 30, m_seekSprite.getPosition().y);
		setVisionCone(t_player.m_playerSprite.getPosition());
		//kinematicSeek(t_deltaTime, t_player);

	}
}

void SeekEnemy::seek(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f playerPos = t_player.m_playerSprite.getPosition();
	sf::Vector2f currentPosition = m_seekSprite.getPosition();

	velDistance = playerPos - currentPosition;
	distance = sqrtf(velDistance.x * velDistance.x + velDistance.y * velDistance.y);
	distanceVec = sf::Vector2f{ velDistance.x / distance , velDistance.y / distance };
	velDistance = distanceVec * maxSpeed;

	//Grabbing the distance between the sprites current Pos and the players pos
	float dx = currentPosition.x - t_player.m_playerSprite.getPosition().x;
	float dy = currentPosition.y - t_player.m_playerSprite.getPosition().y;

	//change that to degrees
	GetProperRot = (atan2(dy, dx)) * 180 / pi;
	rotation = GetProperRot - 90;

	m_seekSprite.setRotation(rotation);
	m_seekSprite.move(velDistance);
	
	//Drawing lines to player
	LineToPlayer.clear();
	sf::Vertex begin{ m_seekSprite.getPosition(), sf::Color::Transparent};
	LineToPlayer.append(begin);
	sf::Vertex end{ playerPos, sf::Color::Red };
	LineToPlayer.append(end);

}

void SeekEnemy::setVisionCone(sf::Vector2f t_targetPos)
{
	m_leftLine.setRotation(m_seekSprite.getRotation() - 90 - angleOfSight);
	m_leftLine.setPosition(m_seekSprite.getPosition());

	m_rightLine.setRotation(m_seekSprite.getRotation() - 90 + angleOfSight);
	m_rightLine.setPosition(m_seekSprite.getPosition());

	sf::Vector2f orientation = { std::cos(m_calculateRadianAngle * m_seekSprite.getRotation() - 90),std::sin(m_calculateRadianAngle * m_seekSprite.getRotation() - 90) };
	sf::Vector2f distance = t_targetPos - m_seekSprite.getPosition();
	distance = normalize(distance);

	float dotProduct = (orientation.x * distance.x) + (orientation.y * distance.y);


	if (dotProduct > std::cos(angleOfSight * 2))
	{
		if (sqrt((t_targetPos.x - m_seekSprite.getPosition().x) * (t_targetPos.x - m_seekSprite.getPosition().x) + (t_targetPos.y - m_seekSprite.getPosition().y) * (t_targetPos.y - m_seekSprite.getPosition().y)) <= 200.0f)
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

sf::Vector2f SeekEnemy::normalize(sf::Vector2f normVector)
{
	float length = sqrt((normVector.x * normVector.x) + (normVector.y * normVector.y));
	return { normVector.x / length, normVector.y / length };
}




//float SeekEnemy::getNewOrientation(float m_orientation, sf::Vector2f m_velocity)
//{
//	float velocityLength = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
//
//	if (velocityLength > 0)
//	{
//		return atan2(m_seekSprite.getPosition().x, m_seekSprite.getPosition().y);
//	}
//
//	return orientation;
//}

//void SeekEnemy::kinematicSeek(sf::Time& t_deltaTime, Player t_player)
//{
//	sf::Vector2f playerPosition = t_player.m_playerSprite.getPosition();
//	sf::Vector2f position = m_seekSprite.getPosition();
//
//	velocity = playerPosition - position;
//
//	float squareAns = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
//	sf::Vector2f normalisedVelocity = velocity / squareAns;
//	normalisedVelocity *= maxSpeed;
//	orientation = getNewOrientation(orientation, normalisedVelocity);
//
//	m_seekSprite.move(normalisedVelocity);
//	m_seekSprite.setRotation(orientation);
//}



