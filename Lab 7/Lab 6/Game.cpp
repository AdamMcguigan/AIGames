//Author - Adam Mcguigan
//Date - Dec 2022

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ScreenSize::M_WIDTH, ScreenSize::M_HEIGHT,  sf::VideoMode::getDesktopMode().bitsPerPixel }, "AILab7 - Fuzzy Logic" },
	m_exitGame{ false }, m_playerUnits{ 0 }, m_enemyUnits{ 0 }, m_range{0} //when true game will exit
{
	setupFontAndText();
	setupSprite();
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
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	if (sf::Keyboard::R == t_event.key.code)
	{
		m_enemyUnits = static_cast<double>(rand() % 30 + 1);
		m_range = static_cast<double>(rand() % 25 + 5);

		m_tiny = Fuzzy::FuzzyTriangle(m_enemyUnits, -10, 0, 10);
		m_small = Fuzzy::FuzzyTrapezoid(m_enemyUnits, 2.5, 10, 15, 20);
		m_moderate = Fuzzy::FuzzyTrapezoid(m_enemyUnits, 15, 20, 25, 30);
		m_large = Fuzzy::FuzzyGrade(m_enemyUnits, 25, 30);

		m_close = Fuzzy::FuzzyTriangle(m_range, -30, 0, 30);
		m_medium = Fuzzy::FuzzyTrapezoid(m_range, 10, 30, 50, 70);
		m_far = Fuzzy::FuzzyGrade(25, 50, 70);

		m_low = Fuzzy::FuzzyOR(Fuzzy::FuzzyOR(Fuzzy::FuzzyAND(m_medium, m_tiny), Fuzzy::FuzzyAND(m_medium, m_small)), Fuzzy::FuzzyAND(m_far, Fuzzy::FuzzyNOT(m_large)));
		m_lowThreat.setString("low danger: " + std::to_string(m_low));

		m_normal = Fuzzy::FuzzyOR(Fuzzy::FuzzyOR(Fuzzy::FuzzyAND(m_close, m_tiny), Fuzzy::FuzzyAND(m_medium, m_moderate)), Fuzzy::FuzzyAND(m_far, m_large));
		m_midThreat.setString("Medium danger: " + std::to_string(m_normal));

		m_high = Fuzzy::FuzzyOR(Fuzzy::FuzzyAND(m_close, Fuzzy::FuzzyNOT(m_tiny)), Fuzzy::FuzzyAND(m_medium, m_large));
		m_highThreat.setString("High Danger: " + std::to_string(m_high));

		m_enemyText.setString("There are " + std::to_string(m_enemyUnits) + " Enemy Units at a Range of " + std::to_string(m_range) + " Units");

		m_playerUnits = std::ceil((m_low * 10 + m_normal * 30 + m_high * 50) / (m_low + m_normal + m_high));
		m_playerText.setString("The number of Units that should be deployed in response is " + std::to_string(m_playerUnits) + " Units");

	}
	
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

	m_window.draw(m_divider);
	m_window.draw(m_enemyText);

	m_window.draw(m_playerText);
	m_window.draw(tutorialText);

	m_window.draw(m_lowThreat);
	m_window.draw(m_midThreat);
	m_window.draw(m_highThreat);

	//Drawing the Player and Enemy
	for (int i = 0; i < m_playerUnits; i++)
	{
		m_playerShape.setPosition(100 + (i * 25), 900);
		m_window.draw(m_playerShape);
	}

	for (int i = 0; i < m_enemyUnits; i++)
	{
		m_enemyShape.setPosition(100 + (i * 25), 300);
		m_window.draw(m_enemyShape);
	}

	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "There was an error loading up the font " << std::endl;
	}

	m_enemyText.setFont(m_font);
	m_enemyText.setPosition(80.0f, 550.0f);
	m_enemyText.setCharacterSize(30);
	m_enemyText.setOutlineColor(sf::Color::Red);
	m_enemyText.setFillColor(sf::Color::Black);
	m_enemyText.setOutlineThickness(3.0f);

	m_playerText.setFont(m_font);
	m_playerText.setPosition(80.0f, 650.0f);
	m_playerText.setCharacterSize(30);
	m_playerText.setOutlineColor(sf::Color::Green);
	m_playerText.setFillColor(sf::Color::Black);
	m_playerText.setOutlineThickness(3.0f);

	tutorialText.setFont(m_font);
	tutorialText.setString("Press R to spawn the player and enemies");
	tutorialText.setPosition(300.0f, 0.0f);
	tutorialText.setCharacterSize(30);
	tutorialText.setOutlineColor(sf::Color::Green);
	tutorialText.setFillColor(sf::Color::Black);
	tutorialText.setOutlineThickness(3.0f);

	m_lowThreat.setFont(m_font);
	m_lowThreat.setString("Low Danger: " + std::to_string(m_low));
	m_lowThreat.setPosition(80.0f, 90.0f);
	m_lowThreat.setCharacterSize(30);
	m_lowThreat.setOutlineColor(sf::Color::Blue);
	m_lowThreat.setFillColor(sf::Color::Black);
	m_lowThreat.setOutlineThickness(3.0f);

	m_midThreat.setFont(m_font);
	m_midThreat.setString("Medium Danger: " + std::to_string(m_normal));
	m_midThreat.setPosition(80.0f, 120.0f);
	m_midThreat.setCharacterSize(30);
	m_midThreat.setOutlineColor(sf::Color::Yellow);
	m_midThreat.setFillColor(sf::Color::Black);
	m_midThreat.setOutlineThickness(3.0f);

	m_highThreat.setFont(m_font);
	m_highThreat.setString("High Danger: " + std::to_string(m_high));
	m_highThreat.setPosition(80.0f, 150.0f);
	m_highThreat.setCharacterSize(30);
	m_highThreat.setOutlineColor(sf::Color::Red);
	m_highThreat.setFillColor(sf::Color::Black);
	m_highThreat.setOutlineThickness(3.0f);
}

void Game::setupSprite()
{
	m_divider.setFillColor(sf::Color::White);
	m_divider.setSize(sf::Vector2f(1600, 40));
	m_divider.setPosition(0, 600);

	m_playerShape.setFillColor(sf::Color::Green);
	m_playerShape.setRadius(10);

	m_enemyShape.setFillColor(sf::Color::Red);
	m_enemyShape.setRadius(10);
}








