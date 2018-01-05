/* Evolution Simulator

	This simulator will create a pool of random creatures. 
	Creatures will have multiple variables controlling various features

	TODOS:
	make creatures interact with each other


	CURRENT TODO:

	spawn a certain number of creatures in random places
	*VERY IMPORTANT* make prettier creatures
	
	
	CURRENT TASK: 

	move the creature in random patterns
	

	CURRENT CAPABILITIES: 

	draws a single creature with random color, random features, and random position
	draws map
	creature can move in diagonals with randomly chosen direction

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Creature.h"

int main() {
	// selects a seed (different each time it runs)
	srand(time(NULL));
	
	// creates the window for the game 
	//disables key repeat (holding down a key and having it register multiple times)
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "EvolutionSimulator", sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);

	// creates the map image, which will be used to find the color 
	// of a pixel for pathfinding purposes
	sf::Image mapImage;
	mapImage.loadFromFile("Map (simple).png");

	// creates the map texture that will be drawn onto the window (identical to mapImage)
	sf::Texture mapTexture;
	mapTexture.loadFromFile("Map (simple).png");

	// creates the map rectangle with the proper dimensions and gives it the mapTexture
	sf::RectangleShape map;
	map.setTexture(&mapTexture);
	map.setSize(sf::Vector2f(1500.0f, 1080.0f));
	map.setOrigin(sf::Vector2f(750.0f, 540.0f));
	map.setPosition(sf::Vector2f(750.0f, 540.0f));

	// creates a Creature vector and fills it with 10 Creature objects
	std::vector<Creature> creatureList;
	for (int i = 0; i < 1000; i++) {
		creatureList.emplace_back();
	}

	// keeps track of the time since the last update
	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) {
		// this restarts the clock and adds the elapsed time since the last restart to deltaTime
		deltaTime += clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
		}
		if (deltaTime > .00167) {
			for (int i = 0; i < 1000; i++)
				creatureList.at(i).Update(deltaTime, mapImage);
			deltaTime = 0;
		}


		window.clear(sf::Color::Black);

		window.draw(map);

		for (int i = 0; i < 1000; i++)
			creatureList.at(i).Draw(window);

		window.display();
	}
	return 0;
}