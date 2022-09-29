#include "NPC.h"

void NPC::update(sf::Time& t_deltaTime)
{
	randomWanderRadius();
	wander(t_deltaTime);
	checkBoundaries();

	m_wanderText.setPosition(m_npcSprite.getPosition().x - 30, m_npcSprite.getPosition().y);

	WanderLine.clear();
	sf::Vertex begin{ m_npcSprite.getPosition(),sf::Color::Cyan };
	WanderLine.append(begin);
	sf::Vertex end{ linePoint, sf::Color::Yellow };
	WanderLine.append(end);
}

void NPC::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_npcSprite);
	m_window.draw(m_wanderText);
	m_window.draw(WanderLine);
}

void NPC::setupSprite()
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
	m_npcSprite.setOrigin(16,16);
	m_npcSprite.setPosition(m_pos);

	m_wanderText.setFont(m_font);
	m_wanderText.setString("Wander");
	m_wanderText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_wanderText.setPosition(m_npcSprite.getPosition());
	m_wanderText.setCharacterSize(20U);
	m_wanderText.setOutlineColor(sf::Color::Black);
	m_wanderText.setFillColor(sf::Color::White);
	m_wanderText.setOutlineThickness(3.0f);
}


void NPC::checkBoundaries()
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

void NPC::wander(sf::Time& t_deltaTime)
{
	angle = m_npcSprite.getRotation();
	angle = angle + randomInt;

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

	std::cout << "Wandering angle: " << angle << std::endl;

	m_velocity.x = m_speed * sin(angle * t_deltaTime.asMilliseconds() / 1000);
	m_velocity.y = m_speed * -cos(angle * t_deltaTime.asMilliseconds() / 1000);

	//grabbing the normalised velocity
	float squareAns = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	sf::Vector2f normalisedVelocity = m_velocity / squareAns;

	m_npcSprite.setRotation(angle);
	m_npcSprite.move(m_velocity);

}

void NPC::randomWanderRadius()
{
	randomInt = rand() % (3 + 3 + 1) + -3; //random number between -1 to 1 ;
	std::cout << "Alien rotate offset: " << randomInt << std::endl;
}

