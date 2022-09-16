#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& m_window);
	void setupSprite();
	void movePlayer();

private:
	sf::Texture m_playerTexture; // texture used for sfml logo
	sf::Sprite m_playerSprite; // sprite used for sfml logo

	sf::Vector2f m_velocity = {2.0f,0.0f};
	float maxVelocity = 3;
	

};



