#include "Creature.h"
#include <time.h>
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"


Creature::Creature(sf::Image& map, sf::Font& statsFont, sf::Texture& bodyTexture, sf::Texture& targetTexture) {
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> xCoordDistribution(5, 1495);
	std::uniform_int_distribution<int> yCoordDistribution(5, 1075);
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
	
	body.setTexture(bodyTexture);
	body.setOrigin(sf::Vector2f(5.0f, 5.0f));
	body.setPosition(sf::Vector2f(xCoordDistribution(mt), yCoordDistribution(mt)));
	body.setColor(sf::Color(rgbDistribution(mt), rgbDistribution(mt), rgbDistribution(mt)));

	target.setTexture(targetTexture);
	target.setOrigin(sf::Vector2f(25.0f, 25.0f));
	
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

	createStatsText(statsFont);
}


Creature::~Creature() {
}

void Creature::Draw(sf::RenderWindow& window) {
	window.draw(body);

	if (selected) {
		window.draw(offenseText);
		window.draw(defenseText);
		window.draw(speedText);
		window.draw(camouflageText);
		window.draw(reproductionRateText);
		window.draw(lifeSpanText);
		window.draw(metabolismText);
		window.draw(intelligenceText);
		window.draw(teamworkText);
		window.draw(eyesightText);
		window.draw(swimmerText);
		window.draw(walkerText);

		window.draw(target);
	}
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
		xOffset = static_cast<float>(movementDistribution(mt)) / (500 * (log((100 - static_cast<float>(features[2])) + 1)));
		yOffset = static_cast<float>(movementDistribution(mt)) / (500 * (log((100 - static_cast<float>(features[2])) + 1)));
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
	if (body.getPosition().x + xOffset > 5 && body.getPosition().x + xOffset < 1495 && 
		body.getPosition().y + yOffset > 5 && body.getPosition().y + yOffset < 1075) {
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

	target.setPosition(body.getPosition());

	target.setRotation(target.getRotation() + 0.25f);
	
	// DIAGONAL MOTION, CURRENTLY DISABLED
	// up = false;
	// right = false;
}

void Creature::createStatsText(sf::Font& myStatsFont) {
	offenseText.setFont(myStatsFont);
	offenseText.setString("Offense: " + std::to_string(features[0]));
	offenseText.setCharacterSize(18);
	offenseText.setFillColor(sf::Color::Red);
	offenseText.setPosition(sf::Vector2f(1520.0f, 60.0f));
	
	defenseText.setFont(myStatsFont);
	defenseText.setString("Defense: " + std::to_string(features[1]));
	defenseText.setCharacterSize(18);
	defenseText.setFillColor(sf::Color::Black);
	defenseText.setPosition(sf::Vector2f(1520.0f, 85.0f));

	speedText.setFont(myStatsFont);
	speedText.setString("Speed: " + std::to_string(features[2]));
	speedText.setCharacterSize(18);
	speedText.setFillColor(sf::Color::Cyan);
	speedText.setPosition(sf::Vector2f(1520.0f, 110.0f));

	camouflageText.setFont(myStatsFont);
	camouflageText.setString("Camouflage: " + std::to_string(features[3]));
	camouflageText.setCharacterSize(18);
	camouflageText.setFillColor(sf::Color::Green);
	camouflageText.setPosition(sf::Vector2f(1520.0f, 135.0f));

	reproductionRateText.setFont(myStatsFont);
	reproductionRateText.setString("Reproduction: " + std::to_string(features[4]));
	reproductionRateText.setCharacterSize(18);
	reproductionRateText.setFillColor(sf::Color::Magenta);
	reproductionRateText.setPosition(sf::Vector2f(1520.0f, 160.0f));

	lifeSpanText.setFont(myStatsFont);
	lifeSpanText.setString("Life Span: " + std::to_string(features[5]));
	lifeSpanText.setCharacterSize(18);
	lifeSpanText.setFillColor(sf::Color::Yellow);
	lifeSpanText.setPosition(sf::Vector2f(1740.0f, 60.0f));

	metabolismText.setFont(myStatsFont);
	metabolismText.setString("Metabolism: " + std::to_string(features[6]));
	metabolismText.setCharacterSize(18);
	metabolismText.setFillColor(sf::Color(102, 51, 0));
	metabolismText.setPosition(sf::Vector2f(1740.0f, 85.0f));

	intelligenceText.setFont(myStatsFont);
	intelligenceText.setString("Intelligence: " + std::to_string(features[7]));
	intelligenceText.setCharacterSize(18);
	intelligenceText.setFillColor(sf::Color(102, 178, 255));
	intelligenceText.setPosition(sf::Vector2f(1740.0f, 110.0f));

	teamworkText.setFont(myStatsFont);
	teamworkText.setString("Teamwork: " + std::to_string(features[8]));
	teamworkText.setCharacterSize(18);
	teamworkText.setFillColor(sf::Color(0, 102, 51));
	teamworkText.setPosition(sf::Vector2f(1740.0f, 135.0f));

	eyesightText.setFont(myStatsFont);
	eyesightText.setString("Eyesight: " + std::to_string(features[9]));
	eyesightText.setCharacterSize(18);
	eyesightText.setFillColor(sf::Color(255, 255, 153));
	eyesightText.setPosition(sf::Vector2f(1740.0f, 160.0f));

	swimmerText.setFont(myStatsFont);
	if (canSwim) {
		swimmerText.setString("Swimmer: yes");
	}
	else {
		swimmerText.setString("Swimmer: no");
	}
	swimmerText.setCharacterSize(18);
	swimmerText.setFillColor(sf::Color::Blue);
	swimmerText.setPosition(sf::Vector2f(1520.0f, 200.0f));

	walkerText.setFont(myStatsFont);
	if (canWalk) {
		walkerText.setString("Walker: yes");
	}
	else {
		walkerText.setString("Walker: no");
	}
	walkerText.setCharacterSize(18);
	walkerText.setFillColor(sf::Color::Green);
	walkerText.setPosition(sf::Vector2f(1740.0f, 200.0f));
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