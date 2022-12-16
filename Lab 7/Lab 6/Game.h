//Author - Adam Mcguigan
//Date - Dec 2022

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "ScreenSize.h"
#include "Fuzzy.h"


class Game
{
public:
	Game();
	~Game();
	void run();
	
	

private:
	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);

	void setupFontAndText();
	void setupSprite();


	void update(sf::Time t_deltaTime);
	void render();

	sf::RectangleShape m_divider;
	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	sf::CircleShape m_playerShape;
	sf::CircleShape m_enemyShape;

	sf::Font m_font;
	sf::Text m_text;

	// Player Troops
	int m_playerUnits;

	// Enemy Troop Number
	int m_enemyUnits;

	// Enemy Distance
	int m_range;

	// Enemy Size
	double m_tiny;
	double m_small;
	double m_moderate;
	double m_large;

	// Enemy Range
	double m_close;
	double m_medium;
	double m_far;

	// Threat Levels
	double m_low;
	double m_normal;
	double m_high;

	//Defuzzy
	double m_defuzzyResult = 0;

	sf::Text m_enemyText; // text used for enemy info
	sf::Text m_playerText; // text used for player info

	sf::Text m_lowThreat;
	sf::Text m_midThreat;
	sf::Text m_highThreat;
	sf::Text tutorialText;
	sf::Text m_defuzzyText;



};

#endif 


