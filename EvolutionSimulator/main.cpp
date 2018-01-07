/* Evolution Simulator

	This simulator will create a pool of random creatures. 
	Creatures will have multiple variables controlling various features

	TODOS:
	make creatures interact with each other
	make creatures who can both walk and swim swim slower than they walk OR walk slower than they swim (randomly)


	CURRENT TODO:

	spawn a certain number of creatures in random places
	*VERY IMPORTANT* make prettier creatures
	

	CURRENT CAPABILITIES: 

	draws a single creature with random color, random features, and random position
	draws map
	creature can move in diagonals with randomly chosen direction
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Creature.h"

const int NUM_CREATURES = 100;

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

	// creates the map texture that will be drawn onto the window (identical graphic to mapImage)
	sf::Texture mapTexture;
	mapTexture.loadFromFile("Map (simple).png");

	// creates the map rectangle with the proper dimensions and gives it the mapTexture
	sf::RectangleShape map;
	map.setTexture(&mapTexture);
	map.setSize(sf::Vector2f(1500.0f, 1080.0f));
	map.setOrigin(sf::Vector2f(750.0f, 540.0f));
	map.setPosition(sf::Vector2f(750.0f, 540.0f));

	// creates the sidePanel texture that will display the clock and selected creature information on the right
	sf::Texture sidePanelTexture;
	sidePanelTexture.loadFromFile("sidePanel.png");

	// creates the sidePanel rectangle with proper dimensions and gives it the sidePanelTexture
	sf::RectangleShape sidePanel;
	sidePanel.setTexture(&sidePanelTexture);
	sidePanel.setSize(sf::Vector2f(420.0f, 1080.0f));
	sidePanel.setOrigin(sf::Vector2f(210.0f, 540.0f));
	sidePanel.setPosition(sf::Vector2f(1710.0f, 540.0f));

	int numMonths = 0;
	int numYears = 0;

	sf::Font clockFont;
	clockFont.loadFromFile("PIXEARG_.TTF");

	sf::Text clockMonths;
	clockMonths.setFont(clockFont);
	clockMonths.setString(std::to_string(numMonths));
	clockMonths.setCharacterSize(15);
	clockMonths.setFillColor(sf::Color::Black);
	clockMonths.setPosition(sf::Vector2f(1530.0f, 18.0f));

	sf::Text clockYears;
	clockYears.setFont(clockFont);
	clockYears.setString(std::to_string(numYears));
	clockYears.setCharacterSize(15);
	clockYears.setFillColor(sf::Color::Black);
	clockYears.setPosition(sf::Vector2f(1560.0f, 18.0f));

	// creates a Creature vector and fills it with 10 Creature objects
	std::vector<Creature> creatureList;
	for (int i = 0; i < NUM_CREATURES; i++) {
		creatureList.emplace_back(mapImage);
	}

	sf::Vector2i mousePosition;

	// keeps track of the time since the last update
	float creatureUpdateTimer = 0.0f;
	float clockTimer = 0.0f;
	sf::Clock clock;

	float deltaTime = 0.0f;

	while (window.isOpen()) {
		// this restarts the clock and adds the elapsed time since the last restart to deltaTime
		deltaTime += clock.restart().asSeconds();
		creatureUpdateTimer += deltaTime;
		clockTimer += deltaTime;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				mousePosition = sf::Mouse::getPosition(window);
				for (int i = 0; i < NUM_CREATURES; i++) {
					if (creatureList.at(i).isTouchingMouse(mousePosition)) {
						std::cout << "CREATURE PRESSED" << std::endl;
					}
				}
					
			}
		}

		// Updates 60 times a second
		if (creatureUpdateTimer > 0.00167f) {
			for (int i = 0; i < NUM_CREATURES; i++) {
				creatureList.at(i).Update(creatureUpdateTimer, mapImage);
			}
			creatureUpdateTimer = 0.0f;
		}

		// Clock update, updates every second (every second is 1 month)
		// Also updates the years
		if (clockTimer > 0.5f) {
			if (numMonths < 12) {
				clockMonths.setString(std::to_string(++numMonths));
			}
			else {
				clockYears.setString(std::to_string(++numYears));
				clockMonths.setString(std::to_string(1));
				numMonths = 1;
			}
			
			clockTimer = 0;
		}

		deltaTime = 0.0f;

		window.clear(sf::Color::Black);

		window.draw(map);
		window.draw(sidePanel);
		window.draw(clockMonths);
		window.draw(clockYears);

		for (int i = 0; i < NUM_CREATURES; i++)
			creatureList.at(i).Draw(window);

		window.display();
	}
	return 0;
}
