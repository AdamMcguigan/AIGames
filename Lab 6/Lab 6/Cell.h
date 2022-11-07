#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"
#include <queue>
class Cell
{
	int m_ID = 0;
	int m_costDistance;

	double m_Hcost;
	double m_Fcost;
	double m_Gcost;

	bool m_traversable = true;
	bool m_marked = false;
	bool m_isEndoint = false;
	bool m_isStartoint = false;

	std::queue<Cell*> m_neighbour;
	sf::RectangleShape m_rect;
	sf::Vector2f m_pos;

public:
	int rectXPos;
	int rectYPos;

	int xPos;
	int yPos;

	bool& getEndPoint();
	bool& getStartPoint();
	bool& getMarked();
	bool& getTraversable();

	void setColor(sf::Color t_color);
	void setEndPoint(bool t_et);
	void setStartPoint(bool t_st);

	void setMarked(bool t_marked);
	void setStartColour();
	void setEndColour();

	void setCostDistance(int t_cost);
	void setTraversable(bool t_traversable);
	void setID(int t_id);

	void setPos(sf::Vector2f t_pos);
	void initRect();
	void setNeighbours(Cell* t_neighbour);

	int& getCostDistance();
	int& getID();

	double& getHcost();
	double& getFcost();
	double& getGcost();

	sf::Vector2f& getPos();
	sf::RectangleShape& getRect();
	std::queue<Cell*>& getNeighbours();

};

