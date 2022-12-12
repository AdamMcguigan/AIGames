#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"


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

	void setupShapes();

	void update(sf::Time t_deltaTime);
	void render();

	sf::CircleShape m_circle;
	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

};

#endif 


