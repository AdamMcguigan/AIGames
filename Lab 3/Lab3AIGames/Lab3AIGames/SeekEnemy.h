#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

class SeekEnemy
{
public:
	SeekEnemy();

	void checkBoundaries();
	void draw(sf::RenderWindow& m_window);
	void update(sf::Time& t_deltaTime, Player& t_player);
	void seek(sf::Time& t_deltaTime, Player& t_player);
	void setVisionCone(sf::Vector2f t_targetPos);
	sf::Vector2f normalize(sf::Vector2f normVector);
	
	sf::VertexArray LineToPlayer{ sf::Lines };

	bool canUpdate = false;
	bool drawTracer = false;

	float angleOfSight = 35;
	float m_calculateRadianAngle = 3.1415926536 / 180;

	sf::RectangleShape m_leftLine;
	sf::RectangleShape m_rightLine;

	//float orientation = 0.0f;
	//float getNewOrientation(float m_orientation, sf::Vector2f m_velocity);
	//void kinematicSeek(sf::Time& t_deltaTime, Player t_player);

private:
	sf::Sprite m_seekSprite;
	sf::Texture m_seekTexture;

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Text seekText;
	sf::Font font;

	float angle = 0.0f;
	float pi = 3.141592653589793238f;
	float speed = 1.0f;
	float maxSpeed = 3.0f;
	float distance = 0.0f;
	float timeToTarget = 0.5f;
	float GetProperRot = 0.0f;
	float rotation = 0.0f;
	sf::Vector2f distanceVec;
	sf::Vector2f velDistance;

};