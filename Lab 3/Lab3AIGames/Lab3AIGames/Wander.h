#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <cmath>
#include "Player.h"

class Wander
{
public:
	Wander();
	void update(sf::Time& t_deltaTime, Player& t_player);
	void draw(sf::RenderWindow& m_window);
	void setupSprite();
	void checkBoundaries();
	void wander(sf::Time& t_deltaTime);
	void randomWanderRadius();
	void setVisionCone(sf::Vector2f t_targetPos);
	sf::Vector2f normalize(sf::Vector2f normVector);

	sf::VertexArray WanderLine{ sf::Lines };
	sf::Vector2f linePoint;

	bool canUpdate = false;
	bool drawTracer = false;

	float radius = 100.0f;
	float angleOfSight = 35;
	float m_calculateRadianAngle = 3.1415926536 / 180;

	sf::RectangleShape m_leftLine;
	sf::RectangleShape m_rightLine;

private:
	sf::Sprite m_npcSprite;
	sf::Texture m_npcTexture;

	float angle = 0.0f;
	float m_rotation = 0.0f;
	float m_speed = 3.0f;
	float angleInRads = 0;
	float pi = 3.141592653589793238f;
	int wanderOffset = 0;

	sf::Text m_wanderText;
	sf::Font m_font;

	sf::Vector2f m_target = { 0,0 };
	sf::Vector2f m_velocity = { 0,0 };
	sf::Vector2f m_pos = { sf::VideoMode::getDesktopMode().width / 2,sf::VideoMode::getDesktopMode().height / 2 };

};

