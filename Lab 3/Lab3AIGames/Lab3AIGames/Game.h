/// <summary>
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "SeekEnemy.h"
#include "FleeEnemy.h"
#include "Wander.h"
#include "FastArrive.h"
#include "SlowArrive.h"
#include "PursueEnemy.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

	//Creating instances of the Player and NPC
	Player thePlayer;
	SeekEnemy mySeek;
	FleeEnemy myFlee;
	Wander myWander;
	FastArrive myFastArrive;
	SlowArrive mySlowArrive;
	PursueEnemy myPursue;

	sf::Text gameText;

private:
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void setupFontAndText();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

