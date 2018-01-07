#include "Creature.h"
#include <time.h>
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"


Creature::Creature(sf::Image& map) {
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> xCoordDistribution(0, 1500);
	std::uniform_int_distribution<int> yCoordDistribution(0, 1079);
	std::uniform_int_distribution<int> rgbDistribution(0, 255);
	std::uniform_int_distribution<int> movementDistribution(-100, 100);
	std::uniform_int_distribution<int> probabilityDistribution(0, 99);

	allocateStats();

	/* DIAGONAL MOTION, CURRENTLY DISABLED 


	if (rand() % 2 == 0)
		up = true;
	if (rand() % 2 == 0)
		right = true;

	yOffset = float(features[2]) / 1000;
	xOffset = float(features[2]) / 1000;

	if (up)
		yOffset = -yOffset;
	if (!right)
		xOffset = -xOffset;
	*/

	xOffset = static_cast<float>(movementDistribution(mt)) / (500 * (log(static_cast<float>(features[2]))));
	yOffset = static_cast<float>(movementDistribution(mt)) / (500 * (log(static_cast<float>(features[2]))));


	bodyTexture.loadFromFile("square.png");
	
	body.setOrigin(sf::Vector2f(5.0f, 5.0f));
	body.setPosition(sf::Vector2f(xCoordDistribution(mt), yCoordDistribution(mt)));
	body.setColor(sf::Color(rgbDistribution(mt), rgbDistribution(mt), rgbDistribution(mt)));
	body.setTexture(bodyTexture);

	// if the creature is spawned on water, it can swim 
	if (map.getPixel(body.getPosition().x, body.getPosition().y) == sf::Color(0, 100, 158)) {
		canSwim = true;
		// rolls a 30% probability to determine whether the creature can walk
		if (probabilityDistribution(mt) < 30) {
			canWalk = false;
		}
	}
	// If the creature is spawned on land and rolls a 30% probability, it can swim
	else if (probabilityDistribution(mt) < 30) {
		canSwim = true;
	}
}


Creature::~Creature() {
}

void Creature::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void Creature::Update(float deltaTime, sf::Image& map) {
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> movementDistribution(-100, 100);
	std::uniform_int_distribution<int> myDeltaTimeDistribution(25, 75);

	myDeltaTime += deltaTime;
	// Random motion 
	if (myDeltaTime > static_cast<float>(myDeltaTimeDistribution(mt)) / 100) {
		myDeltaTime = 0.0f;
		xOffset = static_cast<float>(movementDistribution(mt)) / (500 * (log(static_cast<float>(features[2]))));
		yOffset = static_cast<float>(movementDistribution(mt)) / (500 * (log(static_cast<float>(features[2]))));
	}

	/* DIAGONAL MOTION, CURRENTLY DISABLED


	std::uniform_int_distribution<int> oneZeroDistribution(0, 1);

	myDeltaTime += deltaTime;
	if (myDeltaTime > 0.5f) {
		myDeltaTime = 0.0f;

		if (oneZeroDistribution(mt) == 0)
			up = true;
		if (oneZeroDistribution(mt) == 0)
			right = true;

		xOffset = static_cast<float>(features[2]) / 1000;
		yOffset = static_cast<float>(features[2]) / 1000;

		if (up)
			yOffset = -yOffset;
		if (!right)
			xOffset = -xOffset;
	}
	*/

	// checks to make sure the creature wants to move on the map and not off it
	if (body.getPosition().x + xOffset > 0 && body.getPosition().x + xOffset < 1500 && 
		body.getPosition().y + yOffset > 0 && body.getPosition().y + yOffset < 1080) {
		// if the creature can walk and swim, no checks are needed for terrain type
		if (canWalk && canSwim) {
			body.move(xOffset, yOffset);
		}
		// creature can't swim, so we check to make sure the creature wants to move on land and not water
		else if (canWalk) {
			if (map.getPixel(body.getPosition().x + xOffset, body.getPosition().y + yOffset) != sf::Color(0, 100, 158))
				body.move(xOffset, yOffset);
		}
		// creature can't walk, so we check to make sure the creature wants to move on water and not land
		else {
			if (map.getPixel(body.getPosition().x + xOffset, body.getPosition().y + yOffset) != sf::Color(23, 94, 37))
				body.move(xOffset, yOffset);
		}
		
	}
	
	// DIAGONAL MOTION, CURRENTLY DISABLED
	// up = false;
	// right = false;
}

void Creature::displayStats() {
	sf::Text offenseText;
	sf::Text defenseText;
	sf::Text speedText;
	sf::Text camouflageText;
	sf::Text reproductionRateText;
	sf::Text lifeSpanText;
	sf::Text metabolismText;
	sf::Text intelligenceText;
	sf::Text teamworkText;
	sf::Text eyesightText;
}

bool Creature::isTouchingMouse(sf::Vector2i mousePosition) {
	int xPos = mousePosition.x;
	int yPos = mousePosition.y;

	if (xPos >= body.getPosition().x - 5 && xPos <= body.getPosition().x + 5 &&
		yPos >= body.getPosition().y - 5 && yPos <= body.getPosition().y + 5) {
		return true;
	}
	return false;
}

sf::Vector2f Creature::getPosition() {

	return sf::Vector2f();
}

void Creature::allocateStats(int skillPoints) {
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> featureDistribution(1, 99);
	
	for (int i = 0; i < 10; ++i) {
		features[i] = featureDistribution(mt);
	}

	std::cout << "Offense: " << features[0] << std::endl;
	std::cout << "Defense: " << features[1] << std::endl;
	std::cout << "Speed: " << features[2] << std::endl;
	std::cout << "Camouflage: " << features[3] << std::endl;
	std::cout << "Reproduction Rate: " << features[4] << std::endl;
	std::cout << "Life Span: " << features[5] << std::endl;
	std::cout << "Metabolism: " << features[6] << std::endl;
	std::cout << "Intelligence: " << features[7] << std::endl;
	std::cout << "Teamwork: " << features[8] << std::endl;
	std::cout << "Eyesight: " << features[9] << std::endl << std::endl;
}