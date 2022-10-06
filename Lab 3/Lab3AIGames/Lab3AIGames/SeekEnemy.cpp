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
	}
}

void SeekEnemy::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (canUpdate == true)
	{
		seek(t_deltaTime, t_player);
		//kinematicSeek(t_deltaTime, t_player);
		seekText.setPosition(m_seekSprite.getPosition().x - 30, m_seekSprite.getPosition().y);
	}
}

void SeekEnemy::seek(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f playerPos = t_player.m_playerSprite.getPosition();
	sf::Vector2f currentPosition = m_seekSprite.getPosition();

	vel = playerPos - currentPosition;
	distance = sqrtf(vel.x * vel.x + vel.y * vel.y);
	distanceVec = sf::Vector2f{ vel.x / distance , vel.y / distance };
	vel = distanceVec * maxSpeed;

	float dx = currentPosition.x - t_player.m_playerSprite.getPosition().x;
	float dy = currentPosition.y - t_player.m_playerSprite.getPosition().y;

	GetProperRot = (atan2(dy, dx)) * 180 / pi;
	rotation = GetProperRot - 90;

	m_seekSprite.setRotation(rotation);
	std::cout << "Seeking angle: " << rotation << std::endl;

	m_seekSprite.move(vel);
	
	LineToPlayer.clear();
	sf::Vertex begin{ m_seekSprite.getPosition(), sf::Color::Transparent};
	LineToPlayer.append(begin);
	sf::Vertex end{ playerPos, sf::Color::Red };
	LineToPlayer.append(end);

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



