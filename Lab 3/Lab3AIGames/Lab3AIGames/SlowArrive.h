#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"


class SlowArrive
{
public:

	SlowArrive();

	void update(sf::Time& t_deltaTime, Player& t_player);
	void draw(sf::RenderWindow& t_window);

	bool canUpdate = false;
	bool drawTracer = false;

	sf::Texture m_arrvieTexture; // texture used for alien
	sf::Sprite m_arrvieSprite; // sprite used for alien
	sf::VertexArray LineToPlayer{ sf::Lines };
	
	sf::RectangleShape m_leftLine;
	sf::RectangleShape m_rightLine;
	float angleOfSight = 35;
	float m_calculateRadianAngle = 3.1415926536 / 180;
	void setVisionCone(sf::Vector2f t_targetPos);
	sf::Vector2f normalize(sf::Vector2f normVector);

private:
	void setupSprites();
	void seek(sf::Time& t_deltaTime, Player& t_player);

	float angle = 0.0f;
	float pi = 3.141592653589793238f;
	float speed = 1.0f;
	float maxSpeed = 2.0f;
	float distance;
	float timeToTarget = 0.25f;
	float GetProperRot;
	float rotation;

	sf::Vector2f distanceVec;
	sf::Vector2f vel;

	sf::Font m_font;
	sf::Text arriveSlowText;



};

