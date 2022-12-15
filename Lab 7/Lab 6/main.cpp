#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <iostream>
#include "Game.h"
#include "Fuzzy.h"


int main()
{
	Game game;
	game.run();

	//float enemies = 8;
	//float range = 25.0f;

	//// Fuzzy force size subsets:
	//float sizeTiny = fuzzy::triangle(enemies, -10.0f, 0.0f, 10.0f);
	//float sizeSmall = fuzzy::trapezoid(enemies, 2.5f, 10.0f, 15.0f, 20.0f);
	//float sizeModerate = fuzzy::trapezoid(enemies, 15.0f, 20.0f, 25.0f, 30.0f);
	//float sizeLarge = fuzzy::grade(enemies, 25.0f, 30.0f);

	//// Fuzzy force distance subsets:
	//float distanceClose = fuzzy::triangle(range, -30.0f, 0.0f, 30.0f);
	//float distanceMedium = fuzzy::trapezoid(range, 10.0f, 30.0f, 50.0f, 70.0f);
	//float distanceFar = fuzzy::grade(range, 50.0f, 70.0f);

	//// Apply the fuzzy rules.
	//float threatLow =
	//	fuzzy::OR(fuzzy::OR(fuzzy::AND(distanceMedium, sizeTiny),
	//		fuzzy::AND(distanceMedium, sizeSmall)),
	//		fuzzy::AND(distanceFar, fuzzy::NOT(sizeLarge)));

	//float threatMedium =
	//	fuzzy::OR(fuzzy::OR(fuzzy::AND(distanceClose, sizeTiny),
	//		fuzzy::AND(distanceMedium, sizeModerate)),
	//		fuzzy::AND(distanceFar, sizeLarge));

	//float threatHigh =
	//	fuzzy::OR(fuzzy::AND(distanceClose, fuzzy::NOT(sizeTiny)),
	//		fuzzy::AND(distanceMedium, sizeLarge));

	//float deploy =
	//	round((threatLow * 10.0f + threatMedium * 30 + threatHigh * 50) /
	//		(threatLow + threatMedium + threatHigh));

	//std::cout << enemies << " enemy troops spotted at distance of " << range << std::endl;
	//std::cout << "Deploying " << deploy << " troops." << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}