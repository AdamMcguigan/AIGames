#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT,  sf::VideoMode::getDesktopMode().bitsPerPixel }, "AILab7" },
	m_exitGame{ false } //when true game will exit
{
	setupShapes();
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
	
}

void Game::setupShapes()
{
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setRadius(30.0f);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setPosition(400.0f, 300.0f);
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_window.draw(m_circle);

	m_window.display();
}
