#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 900, 900,  sf::VideoMode::getDesktopMode().bitsPerPixel }, "AILab6" },
	m_exitGame{ false } //when true game will exit
{
	std::cout << "Left Click = Start Pos " << std::endl;
	std::cout << "Right Click = End Pos " << std::endl;
	std::cout << "Press C = Add the Cost Field " << std::endl;
	std::cout << "When you do the right click the heatmap will show " << std::endl;
}


Game::~Game()
{
}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type)
		{
			processKeys(newEvent);
		}
		
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::C == t_event.key.code)
	{
		m_grid.buttonPressed ^= true;


	}

}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	mousePosition = sf::Mouse::getPosition(m_window);
	m_grid.update(m_window);

	
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_grid.render(m_window);
	m_window.display();
}
