#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

class FleeEnemy
{
public:

	FleeEnemy();

	void checkBoundaries();
	void draw(sf::RenderWindow& m_window);
	void update(sf::Time& t_deltaTime, Player& t_player);
	void kinematicFlee(sf::Time& t_deltaTime, Player& t_player);
	void setVisionCone(sf::Vector2f t_targetPos);
	sf::Vector2f normalize(sf::Vector2f normVector);

	sf::CircleShape radius;

	float angleOfSight = 35;
	float m_calculateRadianAngle = 3.1415926536 / 180;
	float radiusF = 300.0f;
	float smallRadius = 60;

	sf::VertexArray LineToPlayer{ sf::Lines };

	bool drawCharacter = false;
	bool tracerAlive = false;

	sf::RectangleShape m_leftLine;
	sf::RectangleShape m_rightLine;
private:
	sf::Texture m_fleeTexture;
	sf::Sprite m_fleeSprite;

	sf::Font m_font;
	sf::Text m_fleeText;

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f distanceVec;
	sf::Vector2f vel;

	float angle = 0.0f;
	float pi = 3.141592653589793238f;
	float speed = 1.0f;
	float maxSpeed = 3.0f;
	float distance = 0.0f;
	float timeToTarget = 0.5f;
	float GetProperRot = 0.0f;
	float rotation = 0.0f;


};

