#include "Creature.h"
#include <time.h>
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"


Creature::Creature() {
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> xCoordDistribution(0, 1500);
	std::uniform_int_distribution<int> yCoordDistribution(0, 1080);
	std::uniform_int_distribution<int> rgbDistribution(0, 255);


	allocateStats();

	if (rand() % 2 == 0)
		up = true;
	if (rand() % 2 == 0)
		right = true;

	yOffset = float(features[2]) / 50;
	xOffset = float(features[2]) / 50;

	if (up)
		yOffset = -yOffset;
	if (!right)
		xOffset = -xOffset;

	bodyTexture.loadFromFile("square.png");
	
	body.setOrigin(sf::Vector2f(10.0f, 10.0f));
	body.setPosition(sf::Vector2f(xCoordDistribution(mt), yCoordDistribution(mt)));
	body.setColor(sf::Color(rgbDistribution(mt), rgbDistribution(mt), rgbDistribution(mt)));
	body.setTexture(bodyTexture);
}


Creature::~Creature() {
}

void Creature::Draw(sf::RenderWindow& window) {
	window.draw(body);
}

void Creature::Update(float deltaTime, sf::Image& map) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> oneZeroDistribution(0, 1);

	myDeltaTime += deltaTime;
	if (myDeltaTime > 0.25f) {
		myDeltaTime = 0.0f;

		if (oneZeroDistribution(mt) == 0)
			up = true;
		if (oneZeroDistribution(mt) == 0)
			right = true;

		yOffset = static_cast<float>(features[2]) / 50;
		xOffset = static_cast<float>(features[2]) / 50;

		if (up)
			yOffset = -yOffset;
		if (!right)
			xOffset = -xOffset;
	}

	if (body.getPosition().x + xOffset >= 0 && body.getPosition().x + xOffset <= 1500 && body.getPosition().y + yOffset >= 0 && body.getPosition().y + yOffset <= 1080) {
		if (map.getPixel(body.getPosition().x + xOffset, body.getPosition().y + yOffset) != sf::Color(0, 100, 158))
			body.move(xOffset, yOffset);
	}
	

	up = false;
	right = false;
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