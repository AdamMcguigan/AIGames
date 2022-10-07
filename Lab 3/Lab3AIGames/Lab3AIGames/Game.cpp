/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, 32U }, "SFML Game" },
	m_exitGame{ false } //when true game will 
{
	srand(time(NULL));
	//Initializing the sprites in the Game Constructor, when game gets created the images will be loaded for the Player and NPC
	setupFontAndText();
	m_window.setFramerateLimit(144);
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
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


/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;

	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	thePlayer.CheckForInput();

	//Below is the key checks for enabling / disabling Npc's or player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		myFlee.drawCharacter ^= true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		myWander.canUpdate ^= true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		mySeek.canUpdate ^= true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		myFastArrive.canUpdate ^= true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		mySlowArrive.canUpdate ^= true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		myPursue.canUpdate ^= true;
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		thePlayer.drawDebugLines ^= true;
		myWander.drawTracer ^= true;
		mySeek.drawTracer ^= true;
		myFlee.tracerAlive ^= true;
		myFastArrive.drawTracer ^= true;
		mySlowArrive.drawTracer ^= true;
		myPursue.drawTracer ^= true;

	}


}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	//Calling the movement functions for the Player and NPC 
	thePlayer.update(t_deltaTime);
	myWander.update(t_deltaTime, thePlayer);
	mySeek.update(t_deltaTime, thePlayer);
	myFlee.update(t_deltaTime, thePlayer);
	myFastArrive.update(t_deltaTime, thePlayer);
	mySlowArrive.update(t_deltaTime, thePlayer);
	myPursue.update(t_deltaTime, thePlayer);

	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(); 

	thePlayer.draw(m_window); 
	myWander.draw(m_window);
	mySeek.draw(m_window);
	myFlee.draw(m_window);
	myFastArrive.draw(m_window);
	mySlowArrive.draw(m_window);
	myPursue.draw(m_window);
	m_window.draw(gameText);

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	gameText.setFont(m_ArialBlackfont);
	gameText.setString("Press 1.Flee  2.Wander  3.Seek  4.Fast Arrive  5.Slow Arrive  6.Purse  7.Draw Debug Lines");
	gameText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	gameText.setPosition(10.0f,10.0f);
	gameText.setCharacterSize(25U);
	gameText.setOutlineColor(sf::Color::Black);
	gameText.setFillColor(sf::Color::White);
	gameText.setOutlineThickness(3.0f);

}


