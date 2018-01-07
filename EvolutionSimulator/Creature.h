#pragma once
#include <string>
#include <random>

#include "SFML/Graphics.hpp"


class Creature {
public:
	Creature(sf::Image& map);
	~Creature();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime, sf::Image& map);

	void displayStats();
	bool isTouchingMouse(sf::Vector2i mousePosition);

	sf::Vector2f getPosition();

	std::string FEATURE_LIST[10] = {
		"offense" ,
		"defense",
		"speed",
		"camouflage",
		"reproductionRate",
		"lifeSpan",
		"metabolism",
		"intelligence",
		"teamwork",
		"eyesight"
	};

	float currentEnergy;

	// true by default, if the creature is a swimmer, 30% chance it can't walk
	bool canWalk = true;
	// false by default, if creature is spawned on water OR rolls a 30% chance, it can swim
	bool canSwim = false;

	// can the creature eat plants?
	bool herbivore = false;
	// can the creature eat meat?
	bool carnivore = false;

	short int features[10];
private:
	float xOffset;
	float yOffset;

	bool selected = false;

	// DIAGONAL MOTION, CURRENTLY DISABLED
	// bool up = false;
	// bool right = false;

	float myDeltaTime = 0.0f;

	void allocateStats(int skillPoints = 500);

	sf::Texture bodyTexture;
	sf::Sprite body;
};

