#include "FastArrive.h"

FastArrive::FastArrive()
{
	setupSprites();
}

void FastArrive::update(sf::Time& t_deltaTime, Player& t_player)
{
	if (canUpdate == true)
	{
		seek(t_deltaTime, t_player);
		fastArriveText.setPosition(m_arrvieSprite.getPosition());
	}
}

void FastArrive::draw(sf::RenderWindow& t_window)
{
	if (canUpdate == true)
	{
		if (drawTracer == true)
		{
			t_window.draw(LineToPlayer);
		}
		t_window.draw(m_arrvieSprite);
		t_window.draw(fastArriveText);
	}
}



void FastArrive::setupSprites()
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
	m_arrvieSprite.setPosition(sf::VideoMode::getDesktopMode().width - 150, sf::VideoMode::getDesktopMode().height - 500);
	m_arrvieSprite.scale(3.0f, 3.0f);
	m_arrvieSprite.rotate(angle);
	m_arrvieSprite.setOrigin(16, 16);

	fastArriveText.setFont(m_font);
	fastArriveText.setString("Fast Arrive");
	fastArriveText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	fastArriveText.setPosition(m_arrvieSprite.getPosition().x - 30, m_arrvieSprite.getPosition().y);
	fastArriveText.setCharacterSize(20U);
	fastArriveText.setOutlineColor(sf::Color::Black);
	fastArriveText.setFillColor(sf::Color::White);
	fastArriveText.setOutlineThickness(3.0f);
}

void FastArrive::seek(sf::Time& t_deltaTime, Player& t_player)
{
	sf::Vector2f playerPos = t_player.m_playerSprite.getPosition();
	sf::Vector2f currentPosition = m_arrvieSprite.getPosition();

	vel = playerPos - currentPosition;
	distance = sqrtf(vel.x * vel.x + vel.y * vel.y);
	distanceVec = sf::Vector2f{ vel.x / distance , vel.y / distance };
	vel = distanceVec * maxSpeed;

	if (distance > t_player.radiusF)
	{
		std::cout << "SEEKING PLAYER " << std::endl;
	}
	else
	{
		vel = vel / timeToTarget;

		if (distance > maxSpeed)
		{

			std::cout << "In large radius " << std::endl;
			sf::Vector2f normalisedVelocity = { vel.x / distance ,vel.y / distance };
			vel = normalisedVelocity;
			vel = vel * maxSpeed * 2.0f;
		}

		if (distance < t_player.smallRadius)
		{
			std::cout << "Touching small radius	" << std::endl;
			vel = { 0.0f,0.0f };
		}
	}

	float dx = currentPosition.x - t_player.m_playerSprite.getPosition().x;
	float dy = currentPosition.y - t_player.m_playerSprite.getPosition().y;

	GetProperRot = (atan2(dy, dx)) * 180 / pi;
	rotation = GetProperRot - 90;

	m_arrvieSprite.setRotation(rotation);
	std::cout << "Seeking angle: " << rotation << std::endl;

	m_arrvieSprite.move(vel);

	LineToPlayer.clear();
	sf::Vertex begin{ m_arrvieSprite.getPosition(), sf::Color::Transparent };
	LineToPlayer.append(begin);
	sf::Vertex end{ playerPos, sf::Color::Red };
	LineToPlayer.append(end);
}